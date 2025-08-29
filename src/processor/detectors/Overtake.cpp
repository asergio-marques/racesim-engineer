#include "detectors/Overtake.h"

#include <chrono>
#include <cstdint>
#include <thread>
#include <vector>
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/Overtake.h"



const Processor::Detector::Type Processor::Detector::Overtake::GetType() const {

    return Processor::Detector::Type::Overtake;

}



void Processor::Detector::Overtake::Exec() {

    while (m_installedInDriverRecords && m_sessionRecord) {

        // As long as there are position changes to be sent to the UI, they
        // will be added to the list of packets to be sent
        for (const auto positionChange : m_positionChanges) {

            if (m_packetsToBeProcessed.empty()) CreateNewPacket(positionChange);
            else {

                // check if position change can be associated with an overtake packet
                bool alreadyAdded = false;
                for (auto packet : m_packetsToBeProcessed) {

                    auto castPacket = dynamic_cast<Packet::Event::Overtake*>(packet);
                    if (castPacket) {

                        for (const auto data : castPacket->GetData()) {

                            if (data.m_position == positionChange.m_oldPosition) {

                                castPacket->InsertData(positionChange.m_id, positionChange.m_newPosition,
                                    (positionChange.m_newPosition < positionChange.m_oldPosition));
                                alreadyAdded = true;
                                // Break the overtake data loop
                                break;

                            }

                        }
                        
                        // Break the already-existing packet loop
                        if (alreadyAdded) break;

                    }

                }
                // if not, create new overtake packet
                if (!alreadyAdded) CreateNewPacket(positionChange);

            }

        }

        // Once all the changes have been processed into internal overtake packets
        // wipe the list
        m_positionChanges.clear();

        // Thread is executed at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}



void Processor::Detector::Overtake::AddPositionChange(const uint8_t id, const uint8_t oldPosition, const uint8_t newPosition) {

    m_positionChanges.push_back({ id, oldPosition, newPosition });

}



void Processor::Detector::Overtake::CreateNewPacket(const Processor::Detector::Overtake::PositionChange& changeInfo) {

    Packet::Event::Overtake* packet = new Packet::Event::Overtake();
    if (packet) {

        packet->InsertData(changeInfo.m_id, changeInfo.m_newPosition,
            (changeInfo.m_newPosition < changeInfo.m_oldPosition));
        m_packetsToBeProcessed.push_back(packet);

    }

}