#include "Presenter.h"

#include <cstdint>
#include <future>
#include <iostream>
#include <thread>
#include <QString>
#include "IFacade.h"
#include "IStore.h"




void Presenter::Facade::setProcessor(Processor::IFacade* processor) {

    if (processor) {

        m_processor = processor;

    }

}



void Presenter::Facade::setSettingsStore(Settings::IStore* settings) {

    if (settings) {

        m_settings = settings;

    }

}



void Presenter::Facade::setNetCom(NetCom::IFacade* netCom) {

    if (netCom) {

        m_netCom = netCom;

    }

}



bool Presenter::Facade::exportRaceToFolder(QString folderPath) {

    if (m_processor) {

        std::future<bool> ret = std::async(std::launch::async, &Processor::IFacade::ExportCurrentRaceData, m_processor, folderPath.toStdString());
        return ret.get();

    }

    return false;

}


const int64_t Presenter::Facade::getSettingValue(const Settings::Key& key, bool& ok) const {

    if (m_settings) {

        return m_settings->getSettingValue(key, ok);

    }

    return -1;

}



const bool Presenter::Facade::setSettingValue(const Settings::Key& key, const int64_t value) {

    if (m_settings) {

        return m_settings->setSettingValue(key, value);

    }

    return false;

}