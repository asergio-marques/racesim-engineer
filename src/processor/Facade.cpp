#include "Facade.h"

#include <memory>
#include "data/Databank.h"
#include "detectors/FastestLap.h"
#include "detectors/Overtake.h"
#include "detectors/WarningPenalty.h"
#include "packets/internal/Subscriber.h"



Processor::Facade::Facade() :
    m_databank(new Processor::Data::Databank),
    m_detectors(),
    m_execThread() {

    if (m_databank) {

        m_detectors.push_back(new Processor::Detector::FastestLap);
        m_detectors.push_back(new Processor::Detector::Overtake);
        m_detectors.push_back(new Processor::Detector::WarningPenalty);

    }

    for (auto detector : m_detectors) {

        if (detector) {

            m_databank->installDetector(detector);
            detector->Init();

        }

    }
    m_execThread = std::thread(&Processor::Facade::Exec, this);

}



Processor::Facade::~Facade() {

    delete m_databank;

}



void Processor::Facade::OnPacketBroadcast(Packet::Internal::Interface* packet) {

    if (m_databank && packet) {

        m_databank->UpdateData(packet);

    }

}



void Processor::Facade::Exec() {

    while (true) {

        std::vector<Packet::Internal::Interface*> packetsToSend;

        // Get all unsent packets from detectors
        for (auto detector : m_detectors) {

            if (detector) {

                for (auto packet : detector->UnsentPackets()) {

                    packetsToSend.push_back(packet);

                }
                detector->ClearPacketList();

            }

        }

        if (!packetsToSend.empty())
        {
            int i = 0;
        }

        for (auto packet : packetsToSend) {

            Broadcast(packet);

        }

        // Thread runs at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}