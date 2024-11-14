#ifndef PROCESSOR_EXPORTER_INCLUDE_RACE_SESSION_H_
#define PROCESSOR_EXPORTER_INCLUDE_RACE_SESSION_H_

#include <cstdint>
#include <map>
#include <string>
#include "exporters/Interface.h"
#include "exporters/RaceSchema.h"



namespace pugi {

    class xml_node;

}

namespace Processor {

    class IFileIO;

    namespace Data {

        class DriverRecord;
        class SessionRecord;

    }

    namespace Exporter {

        class RaceSession final : public Processor::Exporter::Interface {

            public:
            // Constructor
            RaceSession();

            // Destructor
            virtual ~RaceSession() = default;

            // Passes references to the records for the current session
            virtual void InjectRecords(std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords, Processor::Data::SessionRecord* sessionRecord) override final;

            // Parses the information from the records into a pre-defined XML schema and outputs it with the help of the IFileIO class
            virtual void Export(Processor::IFileIO* fileWriter, std::string path) const override final;

            private:
            // Auxiliary functions to add a new child node with character data
            void addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, const char* value) const;
            void addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, const std::string& value) const;
            void addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, uint8_t value) const;
            void addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, uint16_t value) const;
            void addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, uint32_t value) const;

            // Points to the driver records held in the databank, only valid after InjectRecords is called
            std::map<const uint8_t, Processor::Data::DriverRecord*>* m_driverRecords;

            // Points to the current session's records
            Processor::Data::SessionRecord* m_sessionRecord;

            // Holds the rules for the XML format output, v1
            static Processor::Exporter::RaceSchema::v1 m_schemaV1;

        };

    }

}

#endif // PROCESSOR_EXPORTER_INCLUDE_RACE_SESSION_H_