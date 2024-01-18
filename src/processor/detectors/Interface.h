#ifndef PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_
#define PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_

#include <thread>
#include <vector>
#include "packets/internal/Broadcaster.h"



namespace Packet {

    namespace Internal {

        class Interface;

    }

}


namespace Processor {

    namespace Data {

        class Databank;

    }

    namespace Detector {

        class Interface : public Packet::Internal::Broadcaster {

            public:
            Interface(const Processor::Data::Databank* const dataBank);
            virtual ~Interface();
            virtual void Init();
            virtual void ReceiveNewData(Packet::Internal::Interface* const packet) = 0;
            virtual void Exec() = 0;
            virtual const std::vector<Packet::Internal::Interface*>& UnsentPackets() const;
            virtual bool ClearPacketList();

            protected:
            const Processor::Data::Databank* const m_data;
            std::vector<Packet::Internal::Interface*> m_packetsToBeProcessed;
            std::thread m_workerThread;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_