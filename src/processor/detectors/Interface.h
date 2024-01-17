#ifndef PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_
#define PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_



namespace Processor {

    namespace Data {

        class Databank;

    }

    namespace Detector {

        class Interface {

            public:
            Interface(const Processor::Data::Databank* const dataBank);
            virtual ~Interface();

            protected:
            const Processor::Data::Databank* const m_data;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_INTERFACE_H_