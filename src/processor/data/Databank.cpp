#include "data/Databank.h"

#include <cstdint>
#include <filesystem>
#include <future>
#include <map>
#include <thread>
#include "ICompFacade.h"
#include "ISettings.h"
#include "data/DriverRecord.h"
#include "data/RecordCreator.h"
#include "data/SessionRecord.h"
#include "data/internal/Participant.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "exporters/RaceSession.h"
#include "packets/internal/GridPosition.h"
#include "packets/internal/Interface.h"
#include "packets/internal/ParticipantStatus.h"
#include "packets/internal/LapStatus.h"
#include "packets/internal/Standings.h"
#include "packets/internal/PenaltyStatus.h"
#include "packets/internal/SessionParticipants.h"
#include "packets/internal/SessionSettings.h"


#ifndef LINUX
#include <windows.h>
#endif


Processor::Data::Databank::Databank() :
    m_isWorking(false),
    m_presenter(nullptr),
    m_creator(new Processor::Data::RecordCreator),
    m_driverRecords(),
    m_sessionRecord(nullptr),
    m_exporter(nullptr),
    m_activeDetectors() {



}



Processor::Data::Databank::~Databank() {

    for (auto record : m_driverRecords) {

        delete record.second;

    }
    m_driverRecords.clear();
    delete m_sessionRecord;

}



void Processor::Data::Databank::Init(Presenter::ICompFacade* presenter) {

    if (presenter) {

        m_presenter = presenter;

    }

}




void Processor::Data::Databank::updateData(const Packet::Internal::Interface* packet) {

    if (packet) {

        if (m_creator && !m_isWorking) {

            // if the databank is not working, then the existing records should be verified
            // if there are no records, we create them anew
            // if there are records, check against the new data validity and if different, create them anew
            // the SessionStartDataReady detector should detect when all the necessary data is in place
            // to then send the appropriate session start event packet
            switch (packet->packetType()) {

                case Packet::Internal::Type::GridPosition:
                    m_creator->Init(dynamic_cast<const Packet::Internal::GridPosition*>(packet));
                    break;
                case Packet::Internal::Type::SessionSettings:
                    m_creator->Init(dynamic_cast<const Packet::Internal::SessionSettings*>(packet));
                    break;
                case Packet::Internal::Type::SessionParticipants:
                    m_creator->Init(dynamic_cast<const Packet::Internal::SessionParticipants*>(packet));
                    break;
                default:
                    // do nothing
                    break;
            }

        }
        else {

            switch (packet->packetType()) {

                case Packet::Internal::Type::Standings:
                    updateStandings(dynamic_cast<const Packet::Internal::Standings*>(packet));
                    break;

                case Packet::Internal::Type::PenaltyStatus:
                    updatePenalties(dynamic_cast<const Packet::Internal::PenaltyStatus*>(packet));
                    break;

                case Packet::Internal::Type::ParticipantStatus:
                    updateParticipantStatus(dynamic_cast<const Packet::Internal::ParticipantStatus*>(packet));
                    break;

                case Packet::Internal::Type::LapStatus:
                    updateLapStatus(dynamic_cast<const Packet::Internal::LapStatus*>(packet));
                    break;

                default:
                    // do nothing
                    break;

            }

        }

    }

}

void Processor::Data::Databank::installDetector(Processor::Detector::Interface* detector) {

    if (detector) {

        // Search the type of the detector being added to avoid duplicates
        const auto it = m_activeDetectors.find(detector->GetType());
        if (it == m_activeDetectors.cend()) {

            detector->RegisterFunction(std::bind(&Processor::Data::Databank::OnSessionStateChange, this, std::placeholders::_1));

            // Add to vector
            m_activeDetectors.emplace(detector->GetType(), detector);

            // Try to add to the current records
            if (!(m_driverRecords.empty()) && m_sessionRecord) {

                detector->Init(m_sessionRecord);

                for (auto entry : m_driverRecords) {

                    auto record = entry.second;
                    if (record) record->getModifiableState().installDetector(detector);

                }

            }

        }

    }

}



const Processor::Exporter::Interface* Processor::Data::Databank::getExporter() const {

    return m_exporter;

}



void Processor::Data::Databank::markAsFinished() {

    for (auto record : m_driverRecords) {

        record.second->markAsFinished();

    }

    // TODO what would this even be for
    // m_sessionRecord->markAsFinished();

}



void Processor::Data::Databank::triggerAutoExport() {

    // Check if the user has activated the auto export option, and export if so
    if (m_presenter) {

        auto settingsPresenter = dynamic_cast<Presenter::ISettings*>(m_presenter);
        if (settingsPresenter) {

            bool ok = true;
            bool autoExportActive = settingsPresenter->getSettingValue(Settings::Key::AutoExportWhenSessionEnd, ok) > 0;

            if (ok && autoExportActive && m_exporter) {

                std::string folderPath = "";
                #ifndef LINUX
                TCHAR szExeFileName[MAX_PATH];
                GetModuleFileName(NULL, szExeFileName, MAX_PATH);
                folderPath = szExeFileName;
                #elif
                // TODO LINUX
                #endif
                // TODO automatic export default path
                std::filesystem::path path(folderPath);
                path = path.remove_filename();
                if (!path.has_filename()) {
                    // not working, returning 0
                    std::future<bool> ret = std::async(std::launch::async, &Processor::Exporter::Interface::Export, m_exporter, path.string());
                    ret.get();
                }
                // TODO error handling
            }

        }

    }

}



void Processor::Data::Databank::OnSessionStateChange(bool sessionStateChangedTo) {

    m_isWorking = sessionStateChangedTo;

    for (auto detector : m_activeDetectors) {

        if (detector.second) {

            // share the information about a session being officially started or not, to enable the "capture" of information
            detector.second->Enable(sessionStateChangedTo);

        }

    }

    if (m_creator) {

        if (sessionStateChangedTo) {

            // session started, inject records into exporter
            uint8_t playerId = UINT8_MAX;
            if (m_creator->FoundPlayer(playerId)) {

                m_exporter->InjectRecords(m_sessionRecord, m_driverRecords.at(playerId));

            }
            else {

                m_exporter->InjectRecords(m_sessionRecord, &m_driverRecords);

            }

        }
        else {

            // session ended, notify the creator to ready itself for a new session
            m_creator->ClearRecords();

            // TODO ready the exporter once more

        }

    }

    m_isWorking = sessionStateChangedTo;


}



void Processor::Data::Databank::updateStandings(const Packet::Internal::Standings* standingsPacket) {

    if (standingsPacket) {

        // for each standing data on the packet, check if the driver ID
        // matches up with the driver ID of each of the driver records and
        // if we are not overwriting more recent data
        // once it does match, the current position in the state is updated
        // breaking the inner loop then, allows for some optimization so we
        // don't iterate over the two vectors a million times
        //
        // there's probably a better way to do this matching while still avoiding
        // vector index assumptions though
        for (const auto standing : standingsPacket->GetData()) {

            auto entry = m_driverRecords.find(standing.m_driverID);
            if (entry != m_driverRecords.end()) {

                auto driverData = entry->second;

                if (driverData && driverData->updateLastTimestamp(standingsPacket->m_timestamp)) {

                    driverData->getModifiableState().updateCurrentPosition(standing.m_position);


                }

            }

        }

    }

}



void Processor::Data::Databank::updatePenalties(const Packet::Internal::PenaltyStatus* penaltyPacket) {

    if (penaltyPacket) {
        // for each standing data on the packet, check if the driver ID
        // matches up with the driver ID of each of the driver records and
        // if we are not overwriting more recent data
        // once it does match, the current position in the state is updated
        // breaking the inner loop then, allows for some optimization so we
        // don't iterate over the two vectors a million times
        //
        // there's probably a better way to do this matching while still avoiding
        // vector index assumptions though
        for (const auto penaltyData : penaltyPacket->GetData()) {

            auto entry = m_driverRecords.find(penaltyData.m_driverID);
            if (entry != m_driverRecords.end()) {

                auto driverData = entry->second;

                if (driverData && driverData->updateLastTimestamp(penaltyPacket->m_timestamp)) {

                    driverData->getModifiableState().updateWarningPenalties(penaltyData.m_totalWarns,
                        penaltyData.m_numTrackLimits,
                        penaltyData.m_timePenMS,
                        penaltyData.m_numStopGo,
                        penaltyData.m_numDriveThrough);


                }

            }

        }

    }

}



void Processor::Data::Databank::updateParticipantStatus(const Packet::Internal::ParticipantStatus* statusPacket) {

    if (statusPacket) {
        // for each participant data on the packet, check if the driver ID
        // matches up with the driver ID of each of the driver records and
        // if we are not overwriting more recent data
        // once it does match, the current position in the state is updated
        // breaking the inner loop then, allows for some optimization so we
        // don't iterate over the two vectors a million times
        //
        // there's probably a better way to do this matching while still avoiding
        // vector index assumptions though
        for (const auto statusData : statusPacket->GetData()) {

            auto entry = m_driverRecords.find(statusData.m_driverID);
            if (entry != m_driverRecords.end()) {

                auto driverData = entry->second;

                if (driverData && driverData->updateLastTimestamp(statusPacket->m_timestamp)) {

                    driverData->getModifiableState().updateStatus(statusData.m_status);


                }

            }

        }

    }

}



void Processor::Data::Databank::updateLapStatus(const Packet::Internal::LapStatus* lapPacket) {

    if (lapPacket) {

        auto entry = m_driverRecords.find(lapPacket->m_driverID);
        if (entry != m_driverRecords.end()) {

            auto driverData = entry->second;

            if (driverData && driverData->updateLastTimestamp(lapPacket->m_timestamp)) {

                // this is so ugly and uses so many assumptions...
                // initialize
                auto prevLapData = lapPacket->GetData().at(0);
                auto currLapData = lapPacket->GetData().at(0);
                // assume the laps are in order
                if (lapPacket->GetData().size() > 1) {
                    currLapData = lapPacket->GetData().at(1);
                }
                else {
                    // Default it
                    prevLapData = Packet::Internal::LapStatus::Data();
                }

                auto lapEntryCompleted = driverData->getModifiableState().updateLap(currLapData.m_lapID, currLapData.m_type,
                        currLapData.m_status, currLapData.m_time, currLapData.m_sectorTimes,
                        currLapData.m_lapDistanceRun, prevLapData.m_time);

                if (m_sessionRecord && lapEntryCompleted) {

                    bool allDriversComplete =
                        m_sessionRecord->getModifiableState().updateDriverStatus(lapPacket->m_driverID, lapEntryCompleted);

                    if (allDriversComplete) {

                        triggerAutoExport();

                    }

                }

            }

        }

    }

}