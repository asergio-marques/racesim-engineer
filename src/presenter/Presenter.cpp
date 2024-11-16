#include "Presenter.h"

#include <iostream>
#include <thread>
#include <future>
#include <QString>
#include "IFacade.h"




void Presenter::setProcessor(Processor::IFacade* processor) {

    if (processor) {

        m_processor = processor;

    }

}



bool Presenter::exportRaceToFolder(QString folderPath) {

    if (m_processor) {

        std::future<bool> ret = std::async(std::launch::async, &Processor::IFacade::ExportCurrentRaceData, m_processor, folderPath.toStdString());
        return ret.get();

    }

    return false;

}