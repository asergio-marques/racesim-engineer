#include "detectors/Overtake.h"

#include <chrono>
#include <thread>
#include "data/Databank.h"
#include "data/DriverRecord.h"
#include "detectors/Interface.h"
#include "packets/internal/race_types/Overtake.h"



Processor::Detector::Overtake::Overtake() :
    Processor::Detector::Interface() {



}



Processor::Detector::Overtake::~Overtake() {



}



const Processor::Detector::Type Processor::Detector::Overtake::GetType() const {

    return Processor::Detector::Type::Overtake;

}



void Processor::Detector::Overtake::Exec() {

    while (true) {

        for (const auto positionChange : m_positionChanges) {

            if (m_packetsToBeProcessed.empty()) {
                // timestamp can be 0 as the UI isn't supposed to check on this I think maybe perhaps
                Packet::Internal::Overtake* packet = new Packet::Internal::Overtake(0);
                if (packet) {
                    packet->InsertData(positionChange.m_id, positionChange.m_newPosition,
                        (positionChange.m_newPosition < positionChange.m_oldPosition));
                    m_packetsToBeProcessed.push_back(packet);
                }
            }
            else
            {
                // check if position change can be associated with an overtake packet
                for (auto packet : m_packetsToBeProcessed) {
                    auto castPacket = dynamic_cast<Packet::Internal::Overtake*>(packet);
                    if (castPacket) {
                        for (const auto data : castPacket->GetData()) {
                            if (data.m_position == positionChange.m_oldPosition) {

                            }
                        }
                    }
                }
                // if not, create new overtake packet
            }

        }

        m_positionChanges.clear();

        // Thread is executed at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}



void Processor::Detector::Overtake::AddPositionChange(const uint8_t id, const uint8_t oldPosition, const uint8_t newPosition) {

    m_positionChanges.push_back({ id, oldPosition, newPosition });

}