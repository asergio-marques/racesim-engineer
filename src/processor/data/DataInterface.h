#ifndef PROCESSOR_DATA_INCLUDE_DATA_INTERFACE_H_
#define PROCESSOR_DATA_INCLUDE_DATA_INTERFACE_H_

#include <cstdint>
#include <map>



namespace Processor {

    namespace Detector {

        class Interface;

    }

    namespace Data {

        class DataInterface {

            public:
            DataInterface() = default;
            virtual ~DataInterface() = default;
            virtual void installDetector(Processor::Detector::Interface* detector) = 0;


        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DATA_INTERFACE_H_