#ifndef PROCESSOR_INCLUDE_FACADE_H_
#define PROCESSOR_INCLUDE_FACADE_H_

#include <thread>
#include <vector>
#include "IFacade.h"


class IPresenter;

namespace Processor {

    namespace Data {

        class Databank;

    }

    namespace Detector {

        class Interface;

    }

    class Facade final : public Processor::IFacade {

        public:
            // Constructor, initializes the detectors and starts the execution thread for all
            Facade();

            // Destructor
            virtual ~Facade();

            // Implements the internal packet subscriber handling function
            virtual void OnPacketBroadcast(Packet::Internal::Interface* packet) override final;

            // Initializes needed member variables and starts component
            virtual void Init(Processor::IFileIO* fileIO, IPresenter* presenter) override final;

            // Trigger function for the export of the current dataset
            virtual void ExportCurrentRaceData(std::string path) override final;

        private:
            // Main handler object for all driver and session data
            Processor::Data::Databank* const m_databank;

            // Main handler object for all reading and writing of the persistence files
            Processor::IFileIO* m_fileIO;

            // Holder for all detectors that will have access to the databank
            std::vector<Processor::Detector::Interface*> m_detectors;

            // Main execution thread
            std::thread m_workerThread;

            // Main execution loop function
            void Exec();

    };

}

#endif // PROCESSOR_INCLUDE_FACADE_H_