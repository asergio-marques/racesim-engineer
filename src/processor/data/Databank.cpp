#include "data/Databank.h"

#include <cstdint>
#include <map>
#include "data/DriverRecord.h"
#include "data/SessionRecord.h"
#include "data/creators/Interface.h"
#include "data/creators/RaceSession.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/internal/Interface.h"
#include "packets/internal/SessionStart.h"
#include "packets/internal/race_types/RaceStandings.h"
#include "packets/internal/race_types/RaceStart.h"



Processor::Data::Databank::~Databank() {

    deleteSessionInformation();

}



void Processor::Data::Databank::updateData(const Packet::Internal::Interface* packet) {

    if (packet) {

        switch (packet->packetType()) {

            case Packet::Internal::Type::SessionStart:
                createSessionInformation(dynamic_cast<const Packet::Internal::SessionStart*>(packet));
                break;

            case Packet::Internal::Type::SessionEnd:
                deleteSessionInformation();
                break;

            case Packet::Internal::Type::Standings:
                updateStandings(dynamic_cast<const Packet::Internal::RaceStandings*>(packet));
                break;

        }

    }

}

void Processor::Data::Databank::installDetector(Processor::Detector::Interface* detector) {

    if (detector) {

        // Search the type of the detector being added to avoid duplicates
        const auto it = m_activeDetectors.find(detector->GetType());
        if (it == m_activeDetectors.cend()) {
            
            // Add to vector
            m_activeDetectors.emplace(detector->GetType(), detector);

            // Try to add to the current records
            if (!(m_driverRecords.empty()) && m_sessionRecord) {
                
                for (auto entry : m_driverRecords) {
                    
                    auto record = entry.second;
                    if (record) record->getModifiableState().installDetector(detector);

                }

            }

        }

    }

}

void Processor::Data::Databank::createSessionInformation(const Packet::Internal::SessionStart* sessionStartPacket) {

    if (sessionStartPacket) {

        Processor::Data::Creator::Interface* creator = nullptr;

        switch (sessionStartPacket->m_sessionType) {

            case Session::Internal::Type::TimeTrial:
                // TODO implement
                break;

            case Session::Internal::Type::FreePractice:
                // TODO implement
                break;

            case Session::Internal::Type::Qualifying:
                // TODO implement
                break;
            
            case Session::Internal::Type::Race:
                creator = new Processor::Data::Creator::RaceSession(dynamic_cast<const Packet::Internal::RaceStart*>(sessionStartPacket));
                break;

            default:
                // TODO implement
                break;

        }
        if (creator) {

            m_driverRecords = creator->createDriverRecords();
            m_sessionRecord = creator->createSessionRecord();

            for (auto detectorEntry : m_activeDetectors) {

                auto detector = detectorEntry.second;

                for (auto driverEntry : m_driverRecords) {

                    auto record = driverEntry.second;
                    if (record) record->getModifiableState().installDetector(detector);

                }

            }

        }

    }

}



void Processor::Data::Databank::deleteSessionInformation() {

    for (auto record : m_driverRecords) {

        delete record.second;

    }
    m_driverRecords.clear();
    delete m_sessionRecord;

}



void Processor::Data::Databank::updateStandings(const Packet::Internal::RaceStandings* standingsPacket) {

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