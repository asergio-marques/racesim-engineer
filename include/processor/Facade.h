#ifndef PROCESSOR_INCLUDE_FACADE_H_
#define PROCESSOR_INCLUDE_FACADE_H_

#include <thread>
#include <vector>
#include "IFacade.h"



namespace Presenter {

    class ICompFacade;

}

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
            virtual void OnPacketBundleBroadcast(std::vector<Packet::Internal::Interface*> packets) override final;

            // Initializes needed member variables and starts component
            virtual void Init(Presenter::ICompFacade* presenter) override final;

            // Exposes the event packet output interface
            Packet::Event::Broadcaster* exposeBroadcasterInterface() override final;

            // Trigger function for the export of the current dataset
            virtual bool ExportCurrentRaceData(std::string path) override final;

        private:
            // Main handler object for all driver and session data
            Processor::Data::Databank* const m_databank;

            // Holder for all detectors that will have access to the databank
            std::vector<Processor::Detector::Interface*> m_detectors;

            // General interface for communicating with other modules
            Presenter::ICompFacade* m_presenter;

            // Main execution thread
            std::thread m_workerThread;

            // Main execution loop function
            void Exec();

    };

}

#endif // PROCESSOR_INCLUDE_FACADE_H_