#ifndef PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_
#define PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_

#include <functional>
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

            // Changes the state of the detector, allowing or stopping it from fulfilling its task
            virtual void Enable(bool enabled) { m_enabled = enabled; }

            // Main execution function to be overridden by all concrete detectors
            // Does nothing by default
            virtual void Exec() {}

            // Exposes the list of vector currently held by the detector so that it may be sent
            virtual const std::vector<Packet::Event::Interface*>& UnsentPackets() const;

            // Cleans up the list of packets
            virtual bool ClearPacketList();

            // Registers a function for any sort of special signalling 
            virtual bool RegisterFunction(std::function<void(bool)> f) { return false; };

            // Deregisters a previously registered function
            virtual void DeregisterFunction() {};

            protected:
            // Holds all the internal packets that are yet to be sent to subscribers
            std::vector<Packet::Event::Interface*> m_packetsToBeProcessed;

            // Whether this detector is enabled for work or not
            bool m_enabled = false;

            // Main execution thread
            std::thread m_workerThread;

            // Data record for the current session
            Processor::Data::SessionRecord* m_sessionRecord = nullptr;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_