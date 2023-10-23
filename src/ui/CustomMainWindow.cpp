#include "CustomMainWindow.h"

#include <QMainWindow>
#include <QResizeEvent>
#include <QWidget>
#include "base/IScreen.h"




UserInterface::CustomMainWindow::CustomMainWindow(QWidget* parent) :
    QMainWindow(parent),
    m_screens() {



}

void UserInterface::CustomMainWindow::resizeEvent(QResizeEvent* event) {

    QMainWindow::resizeEvent(event);
    qDebug() << "resize";
    emit onResizeEvent(event);

}

void UserInterface::CustomMainWindow::addScreen(UserInterface::Base::IScreen* newScreen) {
    
    if (newScreen) {
    
        if (m_screens.empty()) {
    
            doAddScreen(newScreen);
            return;

        }

        for (const auto screen : m_screens) {
            
            if (screen == newScreen) {
                
                return;

            }

            doAddScreen(newScreen);

        }

    }

}


void UserInterface::CustomMainWindow::doAddScreen(UserInterface::Base::IScreen* newScreen) {

    m_screens.push_back(newScreen);
    connect(this, &UserInterface::CustomMainWindow::onResizeEvent, newScreen, &UserInterface::Base::IScreen::handleResizeEvent);
    newScreen->Initialize();
    if (!centralWidget()) {

        this->setCentralWidget(newScreen);

    }

}