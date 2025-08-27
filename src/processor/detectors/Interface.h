#ifndef PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_
#define PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_

#include <thread>
#include <vector>
#include "detectors/Type.h"



namespace Packet {

    namespace Event {

        class Interface;

    }

}


namespace Processor {

    namespace Data {

        class SessionRecord;

    }

    namespace Detector {

        class Interface {

            public:
            // Default constructor
            Interface() = default;

            // Default destructor
            virtual ~Interface() = default;

            // Starts the worker thread of this detector
            virtual void Init(Processor::Data::SessionRecord* record);

            // Returns the identifying type of this detector
            virtual const Processor::Detector::Type GetType() const = 0;

            // Main execution function to be overridden by all concrete detectors
            // Does nothing by default
            virtual void Exec() {}

            // Exposes the list of vector currently held by the detector so that it may be sent
            virtual const std::vector<Packet::Event::Interface*>& UnsentPackets() const;

            // Cleans up the list of packets
            virtual bool ClearPacketList();

            protected:
            // Holds all the internal packets that are yet to be sent to subscribers
            std::vector<Packet::Event::Interface*> m_packetsToBeProcessed;

            // Main execution thread
            std::thread m_workerThread;

            // Data record for the current session
            Processor::Data::SessionRecord* m_sessionRecord;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_