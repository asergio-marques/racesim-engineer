#ifndef PRESENTER_INCLUDE_PRESENTER_H_
#define PRESENTER_INCLUDE_PRESENTER_H_

#include <cstdint>
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
        void setProcessor(Processor::IFacade* processor) override final;
        void setSettingsStore(Settings::IStore* settings) override final;
        void setNetCom(NetCom::IFacade* netCom) override final;

        // IProcessor
        bool exportRaceToFolder(QString folderPath) override final;

        // ISettings
        const Settings::Key activeSettingAtIndex(const uint8_t index) const override final;
        const uint8_t numActiveSettings() const override final;
        const int64_t getSettingValue(const Settings::Key& key, bool& ok) const override final;
        const bool setSettingValue(const Settings::Key& key, const int64_t value) override final;

        // IUserInterface

        private:
        NetCom::IFacade* m_netCom;
        Processor::IFacade* m_processor;
        Settings::IStore* m_settings;
    };

}

#endif // PRESENTER_INCLUDE_PRESENTER_H_