#ifndef PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_
#define PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_

#include <thread>
#include <vector>
#include "detectors/Type.h"
#include "packets/internal/Broadcaster.h"



namespace Packet {

    namespace Internal {

        class Interface;

    }

}


namespace Processor {

    namespace Data {

        class DataInterface;

    }

    namespace Detector {

        class Interface : public Packet::Internal::Broadcaster {

            public:
            Interface(const Processor::Data::DataInterface* const dataBank);
            virtual ~Interface();
            virtual void Init();
            virtual const Processor::Detector::Type GetType() const = 0;
            virtual void Exec() = 0;
            virtual const std::vector<Packet::Internal::Interface*>& UnsentPackets() const;
            virtual bool ClearPacketList();

            protected:
            const Processor::Data::DataInterface* const m_data;
            std::vector<Packet::Internal::Interface*> m_packetsToBeProcessed;
            std::thread m_workerThread;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_