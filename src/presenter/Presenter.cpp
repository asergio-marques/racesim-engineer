#include "Presenter.h"

#include <iostream>
#include <thread>
#include <future>
#include <QString>
#include "IFacade.h"




void Presenter::Facade::setProcessor(Processor::IFacade* processor) {

    if (processor) {

        m_processor = processor;

    }

}



void Presenter::Facade::setSettingsStore(Settings::IStore* settings) {



}



void Presenter::Facade::setNetCom(NetCom::IFacade* netCom) {



}



bool Presenter::Facade::exportRaceToFolder(QString folderPath) {

    if (m_processor) {

        std::future<bool> ret = std::async(std::launch::async, &Processor::IFacade::ExportCurrentRaceData, m_processor, folderPath.toStdString());
        return ret.get();

    }

    return false;

}