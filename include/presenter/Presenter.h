#ifndef PRESENTER_INCLUDE_PRESENTER_H_
#define PRESENTER_INCLUDE_PRESENTER_H_

#include <QString>
#include "ICompFacade.h"
#include "IProcessor.h"
#include "ISettings.h"
#include "IUserInterface.h"



namespace Processor {

    class IFacade;

}

namespace Presenter {

    class Facade : public ICompFacade, public IProcessor, public ISettings, public IUserInterface {

        public:
        Facade() = default;
        virtual ~Facade() = default;

        // ICompFacade
        virtual void setProcessor(Processor::IFacade* processor) override final;
        virtual void setSettingsStore(Settings::IStore* settings) override final;
        virtual void setNetCom(NetCom::IFacade* netCom) override final;

        // IProcessor
        virtual bool exportRaceToFolder(QString folderPath) override final;

        // ISettings

        // IUserInterface

        private:
        NetCom::IFacade* m_netCom;
        Processor::IFacade* m_processor;
        Settings::IStore* settings;
    };

}

#endif // PRESENTER_INCLUDE_PRESENTER_H_