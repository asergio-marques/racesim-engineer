#include "Facade.h"

#include <thread>
#include <vector>
#include "data/Databank.h"
#include "detectors/LapFinished.h"
#include "detectors/Overtake.h"
#include "detectors/PenaltyReceived.h"
#include "detectors/ParticipantStatusChanged.h"
#include "detectors/SessionStartDataReady.h"
#include "detectors/TyreChanged.h"
#include "exporters/Interface.h"
#include "exporters/RaceSession.h"
#include "IFacade.h"
#include "ICompFacade.h"
#include "packets/internal/Subscriber.h"



Processor::Facade::Facade() :
    Processor::IFacade::IFacade(),
    m_databank(new Processor::Data::Databank),
    m_detectors(),
    m_presenter(nullptr),
    m_workerThread() {

    if (m_databank) {

        m_detectors.push_back(new Processor::Detector::SessionStartDataReady);
        m_detectors.push_back(new Processor::Detector::LapFinished);
        m_detectors.push_back(new Processor::Detector::Overtake);
        m_detectors.push_back(new Processor::Detector::PenaltyReceived);
        m_detectors.push_back(new Processor::Detector::ParticipantStatusChanged);
        m_detectors.push_back(new Processor::Detector::TyreChanged);

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



void Processor::Facade::OnPacketBundleBroadcast(std::vector<Packet::Internal::Interface*> packets) {

    if (m_databank && !packets.empty()) {

        for (const auto packet : packets) {

            if (packet) {

                m_databank->updateData(packet);
                delete packet;

            }

        }

        packets.clear();

    }

}




void Processor::Facade::Init(Presenter::ICompFacade* presenter) {

    if (presenter) {

        presenter->setProcessor(this);
        m_presenter = presenter;
        m_databank->Init(presenter);

    }

    m_workerThread = std::thread(&Processor::Facade::Exec, this);

}





Packet::Event::Broadcaster* Processor::Facade::exposeBroadcasterInterface() {

    return this;

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

        std::vector<Packet::Event::Interface*> packetsToSend;

        // Get all unsent packets from detectors
        for (auto detector : m_detectors) {

            if (detector) {

                for (auto packet : detector->UnsentPackets()) {

                    packetsToSend.push_back(packet);

                }
                detector->ClearPacketList();

            }

        }

        Broadcast(packetsToSend);

        // Thread runs at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}