#include "data/Databank.h"

#include "data/DriverRecord.h"
#include "data/SessionRecord.h"
#include "data/creators/Interface.h"
#include "data/creators/RaceSession.h"
#include "packets/internal/Interface.h"
#include "packets/internal/SessionStart.h"
#include "packets/internal/race_types/RaceStart.h"



Processor::Data::Databank::Databank() :
    m_driverRecords(),
    m_sessionRecord(nullptr) {



}



Processor::Data::Databank::~Databank() {

    for (auto record : m_driverRecords) {

        delete record;

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
                

        }

    }

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