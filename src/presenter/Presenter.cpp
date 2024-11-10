#include "Presenter.h"

#include <iostream>
#include <QString>
#include "IFacade.h"




void Presenter::setProcessor(Processor::IFacade* processor) {

    if (processor) {

        m_processor = processor;

    }

}


void Presenter::exportRaceToFolder(QString folderPath) {

    if (m_processor) {

        m_processor->ExportCurrentRaceData(folderPath.toStdString());

    }

}