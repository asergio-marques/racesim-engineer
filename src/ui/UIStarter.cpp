#include "UIStarter.h"

#include <QApplication>



void UserInterface::UIStarter::Init(int* argc, char*** argv) {

    app = new QApplication(*argc, *argv);

}



int UserInterface::UIStarter::Run() {

    if (app) {

        return app->exec();

    }

    return 0;

}