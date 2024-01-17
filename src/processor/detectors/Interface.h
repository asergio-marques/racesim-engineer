#ifndef PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_
#define PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_

#include <thread>
#include <vector>



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

        class Interface {

            public:
            Interface(const Processor::Data::Databank* const dataBank);
            virtual ~Interface();
            virtual void Init();
            virtual void ReceiveNewData(Packet::Internal::Interface* const packet) = 0;
            virtual void Exec() = 0;

            protected:
            const Processor::Data::Databank* const m_data;
            std::vector<const Packet::Internal::Interface*> m_packetsToBeProcessed;
            std::thread m_workerThread;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_