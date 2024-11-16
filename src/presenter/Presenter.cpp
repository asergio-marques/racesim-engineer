#include "Presenter.h"

#include <iostream>
#include <QString>
#include "IFacade.h"




void Presenter::setProcessor(Processor::IFacade* processor) {

    if (processor) {

        m_processor = processor;

    }

}



bool Presenter::exportRaceToFolder(QString folderPath) {

    if (m_processor) {

        return m_processor->ExportCurrentRaceData(folderPath.toStdString());

    }

    return false;

}