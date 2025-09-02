#ifndef PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_
#define PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_

#include <cstdint>
#include <map>
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

        class DriverRecord;
        class SessionRecord;

    }

    namespace Detector {

        class Interface {

            public:
            // Default constructor
            Interface();

            // Default destructor
            virtual ~Interface() = default;

            // Initializes the session record, initialization of the worker thread is to be done by subclasses 
            virtual void Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) = 0;

            // Returns the identifying type of this detector
            virtual const Processor::Detector::Type GetType() const = 0;

            // Main execution function to be overridden by all concrete detectors
            // Does nothing by default
            virtual void Exec() = 0;

            // Exposes the list of vector currently held by the detector so that it may be sent
            virtual const std::vector<Packet::Event::Interface*>& UnsentPackets() const;

            // Cleans up the list of packets
            virtual bool ClearPacketList();

            protected:
            // Generic implementation of the Init function, to be called by subclasses
            virtual void doInit(Processor::Data::SessionRecord* record, std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords);

            // Holds all the internal packets that are yet to be sent to subscribers
            std::vector<Packet::Event::Interface*> m_packetsToBeProcessed;

            // Main execution thread
            std::thread m_workerThread;

            // Data record for the current session
            Processor::Data::SessionRecord* m_sessionRecord;

            // Map of data records for the current participants in the session
            std::map<const uint8_t, Processor::Data::DriverRecord*>* m_driverRecords;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_