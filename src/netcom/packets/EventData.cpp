#include "packets/EventData.h"

#include <cstdint>
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include "data/Event.h"
#include "data/Packet.h"
#include "packets/IPacket.h"
#include "packets/Header.h"
#include "packets/Helper.h"


std::map<std::string, F1_23::Event::Type> F1_23::Packet::EventData::m_eventCodeTable = {

    { std::string("SSTA"), F1_23::Event::Type::SessionStarted },
    { std::string("SEND"), F1_23::Event::Type::SessionEnded },
    { std::string("FTLP"), F1_23::Event::Type::FastestLapSet },
    { std::string("RTMT"), F1_23::Event::Type::CarRetired },
    { std::string("DRSE"), F1_23::Event::Type::DRSEnabled },
    { std::string("DRSD"), F1_23::Event::Type::DRSDisabled },
    { std::string("TMPT"), F1_23::Event::Type::TeammateInPits },
    { std::string("CHQF"), F1_23::Event::Type::ChequeredFlagWaved },
    { std::string("RCWN"), F1_23::Event::Type::RaceWinnerDecided },
    { std::string("PENA"), F1_23::Event::Type::PenaltyIssued },
    { std::string("SPTP"), F1_23::Event::Type::SpeedTrapTriggered },
    { std::string("STLG"), F1_23::Event::Type::StartLightsOn },
    { std::string("LGOT"), F1_23::Event::Type::StartLightsOut },
    { std::string("DTSV"), F1_23::Event::Type::DriveThroughServed },
    { std::string("SGSV"), F1_23::Event::Type::StopGoServed },
    { std::string("FLBK"), F1_23::Event::Type::FlashbackActivated },
    { std::string("BUTN"), F1_23::Event::Type::ButtonStatus },
    { std::string("RDFL"), F1_23::Event::Type::RedFlagWaved },
    { std::string("OVTK"), F1_23::Event::Type::OvertakePerformed }

};



F1_23::Packet::EventData::EventData(char* packetInfo, F1_23::Packet::Helper* helper) :
    F1_23::Packet::IPacket(packetInfo),
    m_eventType(F1_23::Event::Type::InvalidUnknown),
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
    m_overtakeData() {

    if (packetInfo && helper) {
    
        BuildPacket(packetInfo, helper);

    }
    if (helper) {
    
        // It is the responsability of the packet class to delete
        // the helper as it is to be used only for this function
        delete helper;

    }

}



const F1_23::Packet::LengthBytes F1_23::Packet::EventData::GetLength() const {

    return F1_23::Packet::LengthBytes::Event;

}



#ifndef NDEBUG
void F1_23::Packet::EventData::Print() const {
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "\t\tNew packet received!" << std::endl;

    const F1_23::Packet::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "\tPacket info:" << std::endl;
    std::cout << "Event type: " << static_cast<uint16_t>(m_eventType) << std::endl;

    switch (m_eventType) {

        case F1_23::Event::Type::OvertakePerformed:
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



void F1_23::Packet::EventData::BuildPacket(char* packetInfo, F1_23::Packet::Helper* helper) {

    char eventCode[5];
    size_t arrayStatus = static_cast<size_t>(F1_23::Packet::LengthBytes::Header);

    // Get the event code from data packet, then add null terminator for ease of comparison
    helper->getVariableArrayFromByteStream<>(packetInfo, eventCode, 4, arrayStatus);
    eventCode[4] = '\0';

    std::string eventCodeStr(reinterpret_cast<char*>(eventCode));

    auto it = m_eventCodeTable.find(eventCodeStr);
    if (it != m_eventCodeTable.end()) {

        m_eventType = it->second;

    }
    else {

        m_eventType = F1_23::Event::Type::InvalidUnknown;

    }

    switch (m_eventType) {

        case F1_23::Event::Type::InvalidUnknown:
            // TODO error handling
            break;

        case F1_23::Event::Type::FastestLapSet:
            helper->getVariableFromByteStream<>(packetInfo, &m_fastestLapData, arrayStatus);
            break;

        case F1_23::Event::Type::CarRetired:
            helper->getVariableFromByteStream<>(packetInfo, &m_carRetirementData, arrayStatus);
            break;

        case F1_23::Event::Type::TeammateInPits:
            helper->getVariableFromByteStream<>(packetInfo, &m_teammateInPitsData, arrayStatus);
            break;

        case F1_23::Event::Type::RaceWinnerDecided:
            helper->getVariableFromByteStream<>(packetInfo, &m_raceWinnerData, arrayStatus);
            break;

        case F1_23::Event::Type::PenaltyIssued:
            helper->getVariableFromByteStream<>(packetInfo, &m_penaltyData, arrayStatus);
            break;

        case F1_23::Event::Type::SpeedTrapTriggered:
            helper->getVariableFromByteStream<>(packetInfo, &m_speedTrapData, arrayStatus);
            break;

        case F1_23::Event::Type::StartLightsOn:
            helper->getVariableFromByteStream<>(packetInfo, &m_startLightsData, arrayStatus);
            break;

        case F1_23::Event::Type::DriveThroughServed:
            helper->getVariableFromByteStream<>(packetInfo, &m_DTPenaltyServedData, arrayStatus);
            break;

        case F1_23::Event::Type::StopGoServed:
            helper->getVariableFromByteStream<>(packetInfo, &m_stopGoPenaltyServedData, arrayStatus);
            break;

        case F1_23::Event::Type::FlashbackActivated:
            helper->getVariableFromByteStream<>(packetInfo, &m_flashbackData, arrayStatus);
            break;

        case F1_23::Event::Type::ButtonStatus:
            helper->getVariableFromByteStream<>(packetInfo, &m_buttonData, arrayStatus);
            break;

        case F1_23::Event::Type::OvertakePerformed:
            helper->getVariableFromByteStream<>(packetInfo, &m_overtakeData, arrayStatus);
            break;

        default:
            // No handling needed for other event types
            break;
    
    }

}