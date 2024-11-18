#include "Facade.h"

#include <thread>
#include <vector>
#include "data/Databank.h"
#include "detectors/FinishedLap.h"
#include "detectors/Overtake.h"
#include "detectors/WarningPenalty.h"
#include "detectors/DriverStatus.h"
#include "exporters/Interface.h"
#include "exporters/RaceSession.h"
#include "IFacade.h"
#include "ICompFacade.h"
#include "packets/internal/Subscriber.h"



Processor::Facade::Facade() :
    Processor::IFacade::IFacade(),
    m_databank(new Processor::Data::Databank),
    m_detectors(),
    m_workerThread() {

    if (m_databank) {

        m_detectors.push_back(new Processor::Detector::FinishedLap);
        m_detectors.push_back(new Processor::Detector::Overtake);
        m_detectors.push_back(new Processor::Detector::WarningPenalty);
        m_detectors.push_back(new Processor::Detector::DriverStatus);

    }

    for (auto detector : m_detectors) {

        if (detector) {

            m_databank->installDetector(detector);

        }

    }

}



Processor::Facade::~Facade() {

    delete m_databank;

}



void Processor::Facade::OnPacketBroadcast(Packet::Internal::Interface* packet) {

    if (m_databank && packet) {

        m_databank->updateData(packet);

    }

}




void Processor::Facade::Init(Presenter::ICompFacade* presenter) {

    if (presenter) {

        presenter->setProcessor(this);

    }

    m_workerThread = std::thread(&Processor::Facade::Exec, this);

}



bool Processor::Facade::ExportCurrentRaceData(std::string path) {

    if (m_databank && m_databank->getExporter()) {

        const Processor::Exporter::Interface* exporter = m_databank->getExporter();
        return exporter->Export(path);

    }
    else {

        return false;
        // THROW ERROR

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

        for (auto packet : packetsToSend) {

            Broadcast(packet);

        }

        // Thread runs at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}