#include "data/Databank.h"

#include "data/DataInterface.h"
#include "data/DriverRecord.h"
#include "data/SessionRecord.h"
#include "data/creators/Interface.h"
#include "data/creators/RaceSession.h"
#include "packets/internal/Interface.h"
#include "packets/internal/SessionStart.h"
#include "packets/internal/race_types/RaceStart.h"
#include "packets/internal/race_types/RaceStandings.h"



Processor::Data::Databank::Databank() :
    Processor::Data::DataInterface(),
    m_driverRecords(),
    m_sessionRecord(nullptr) {



}



Processor::Data::Databank::~Databank() {

    for (auto record : m_driverRecords) {

        delete record.second;

    }
    m_driverRecords.clear();
    delete m_sessionRecord;

}



void Processor::Data::Databank::UpdateData(const Packet::Internal::Interface* packet) {

    if (packet && m_sessionRecord) {

        switch (packet->packetType()) {

            case Packet::Internal::Type::SessionStart:
                CreateSessionInformation(dynamic_cast<const Packet::Internal::SessionStart*>(packet));
                break;

            case Packet::Internal::Type::Standings:
                UpdateStandings(dynamic_cast<const Packet::Internal::RaceStandings*>(packet));
                

        }

    }

}



const std::map<const uint8_t, Processor::Data::DriverRecord*> Processor::Data::Databank::getDriverRecords() const {

    return m_driverRecords;

}



const Processor::Data::SessionRecord* Processor::Data::Databank::getSessionRecord() const {

    return m_sessionRecord;

}



void Processor::Data::Databank::CreateSessionInformation(const Packet::Internal::SessionStart* sessionStartPacket) {

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

        }

    }

}



void Processor::Data::Databank::UpdateStandings(const Packet::Internal::RaceStandings* standingsPacket) {

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

                if (driverData &&
                    (driverData->getLastTimestamp() <= standingsPacket->m_timestamp)) {

                    driverData->getModifiableState().updateCurrentPosition(standing.m_position);

                }

            }

        }

    }

}