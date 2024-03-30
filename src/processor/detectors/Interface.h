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

    namespace Detector {

        class Interface : public Packet::Internal::Broadcaster {

            public:
            // Default constructor
            Interface() = default;

            // Default destructor
            virtual ~Interface() = default;

            // Starts the worker thread of this detector
            virtual void Init();

            // Returns the identifying type of this detector
            virtual const Processor::Detector::Type GetType() const = 0;

            // Main execution function to be overridden by all concrete detectors
            virtual void Exec() = 0;

            // Exposes the list of vector currently held by the detector so that it may be sent
            virtual const std::vector<Packet::Internal::Interface*>& UnsentPackets() const;

            // Cleans up the list of packets
            virtual bool ClearPacketList();

            protected:
            // Holds all the internal packets that are yet to be sent to subscribers
            std::vector<Packet::Internal::Interface*> m_packetsToBeProcessed;

            // Main execution thread
            std::thread m_workerThread;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_