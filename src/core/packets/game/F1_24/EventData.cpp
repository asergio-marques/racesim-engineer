#include "packets/game/F1_24/EventData.h"

#include <cstdint>
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include "data/game/F1_24/Event.h"
#include "data/game/F1_24/Packet.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_24/Interface.h"
#include "packets/game/F1_24/Header.h"



std::map<std::string, Event::F1_24::Type> Packet::Game::F1_24::EventData::m_eventCodeTable = {

    { std::string("SSTA"), Event::F1_24::Type::SessionStarted },
    { std::string("SEND"), Event::F1_24::Type::SessionEnded },
    { std::string("FTLP"), Event::F1_24::Type::FastestLapSet },
    { std::string("RTMT"), Event::F1_24::Type::CarRetired },
    { std::string("DRSE"), Event::F1_24::Type::DRSEnabled },
    { std::string("DRSD"), Event::F1_24::Type::DRSDisabled },
    { std::string("TMPT"), Event::F1_24::Type::TeammateInPits },
    { std::string("CHQF"), Event::F1_24::Type::ChequeredFlagWaved },
    { std::string("RCWN"), Event::F1_24::Type::RaceWinnerDecided },
    { std::string("PENA"), Event::F1_24::Type::PenaltyIssued },
    { std::string("SPTP"), Event::F1_24::Type::SpeedTrapTriggered },
    { std::string("STLG"), Event::F1_24::Type::StartLightsOn },
    { std::string("LGOT"), Event::F1_24::Type::StartLightsOut },
    { std::string("DTSV"), Event::F1_24::Type::DriveThroughServed },
    { std::string("SGSV"), Event::F1_24::Type::StopGoServed },
    { std::string("FLBK"), Event::F1_24::Type::FlashbackActivated },
    { std::string("BUTN"), Event::F1_24::Type::ButtonStatus },
    { std::string("RDFL"), Event::F1_24::Type::RedFlagWaved },
    { std::string("OVTK"), Event::F1_24::Type::OvertakePerformed },
    { std::string("SCAR"), Event::F1_24::Type::SafetyCarActivated },
    { std::string("COLL"), Event::F1_24::Type::CollisionOccurred }

};



Packet::Game::F1_24::EventData::EventData(const char* packetInfo, const Packet::Game::F1_24::Header* header, Packet::Game::Helper* helper) :
    Packet::Game::F1_24::Interface(),
    m_eventType(Event::F1_24::Type::InvalidUnknown),
    m_fastestLapData(),
    m_carRetirementData(),
    m_teammateInPitsData(),
    m_raceWinnerData(),
    m_penaltyData(),
    m_speedTrapData(),
    m_startLightsData(),
    m_DTPenaltyServedData(),
    m_stopGoPenaltyServedData(),
    m_flashbackData(),
    m_buttonData(),
    m_overtakeData(),
    m_safetyCarData(),
    m_collisionData() {

    this->SetHeader(header);

    if (packetInfo && helper) {
    
        helper->SetPacketLength(static_cast<size_t>(this->GetLength()));
        BuildPacket(packetInfo, helper);

    }
    if (helper) {
    
        // It is the responsability of the packet class to delete
        // the helper as it is to be used only for this function
        delete helper;

    }

}



const Packet::Game::F1_24::LengthBytes Packet::Game::F1_24::EventData::GetLength() const {

    return Packet::Game::F1_24::LengthBytes::EventData;

}



#ifndef NDEBUG
void Packet::Game::F1_24::EventData::Print() const {
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "\t\tNew packet received!" << std::endl;

    const Packet::Game::F1_24::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "\tPacket info:" << std::endl;
    std::cout << "Event type: " << static_cast<uint16_t>(m_eventType) << std::endl;

    switch (m_eventType) {

        case Event::F1_24::Type::OvertakePerformed:
            std::cout << "Overtaking car index: " << static_cast<uint16_t>(m_overtakeData.m_overtakingCarIndex) << std::endl;
            std::cout << "Overtaken car index: " << static_cast<uint16_t>(m_overtakeData.m_overtakenCarIndex) << std::endl;
            break;

        default:
            // TBD
            break;
    }

    std::cout << "--------------------------------------------" << std::endl;

}
#endif // NDEBUG



void Packet::Game::F1_24::EventData::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {

    char eventCode[5];
    size_t arrayStatus = static_cast<size_t>(Packet::Game::F1_24::LengthBytes::Header);

    // Get the event code from data packet, then add null terminator for ease of comparison
    helper->getVariableArrayFromByteStream<>(packetInfo, eventCode, 4, arrayStatus);
    eventCode[4] = '\0';

    std::string eventCodeStr(reinterpret_cast<char*>(eventCode));

    auto it = m_eventCodeTable.find(eventCodeStr);
    if (it != m_eventCodeTable.end()) {

        m_eventType = it->second;

    }
    else {

        m_eventType = Event::F1_24::Type::InvalidUnknown;

    }

    switch (m_eventType) {

        case Event::F1_24::Type::InvalidUnknown:
            // TODO error handling
            break;

        case Event::F1_24::Type::FastestLapSet:
            helper->getVariableFromByteStream<>(packetInfo, &m_fastestLapData, arrayStatus);
            break;

        case Event::F1_24::Type::CarRetired:
            helper->getVariableFromByteStream<>(packetInfo, &m_carRetirementData, arrayStatus);
            break;

        case Event::F1_24::Type::TeammateInPits:
            helper->getVariableFromByteStream<>(packetInfo, &m_teammateInPitsData, arrayStatus);
            break;

        case Event::F1_24::Type::RaceWinnerDecided:
            helper->getVariableFromByteStream<>(packetInfo, &m_raceWinnerData, arrayStatus);
            break;

        case Event::F1_24::Type::PenaltyIssued:
            helper->getVariableFromByteStream<>(packetInfo, &m_penaltyData, arrayStatus);
            break;

        case Event::F1_24::Type::SpeedTrapTriggered:
            helper->getVariableFromByteStream<>(packetInfo, &m_speedTrapData, arrayStatus);
            break;

        case Event::F1_24::Type::StartLightsOn:
            helper->getVariableFromByteStream<>(packetInfo, &m_startLightsData, arrayStatus);
            break;

        case Event::F1_24::Type::DriveThroughServed:
            helper->getVariableFromByteStream<>(packetInfo, &m_DTPenaltyServedData, arrayStatus);
            break;

        case Event::F1_24::Type::StopGoServed:
            helper->getVariableFromByteStream<>(packetInfo, &m_stopGoPenaltyServedData, arrayStatus);
            break;

        case Event::F1_24::Type::FlashbackActivated:
            helper->getVariableFromByteStream<>(packetInfo, &m_flashbackData, arrayStatus);
            break;

        case Event::F1_24::Type::ButtonStatus:
            helper->getVariableFromByteStream<>(packetInfo, &m_buttonData, arrayStatus);
            break;

        case Event::F1_24::Type::OvertakePerformed:
            helper->getVariableFromByteStream<>(packetInfo, &m_overtakeData, arrayStatus);
            break;

        case Event::F1_24::Type::SafetyCarActivated:
            helper->getVariableFromByteStream<>(packetInfo, &m_safetyCarData, arrayStatus);
            break;

        case Event::F1_24::Type::CollisionOccurred:
            helper->getVariableFromByteStream<>(packetInfo, &m_collisionData, arrayStatus);
            break;

        default:
            // No handling needed for other event types
            break;
    
    }

}