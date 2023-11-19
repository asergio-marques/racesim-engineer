#include "CustomMainWindow.h"

#include <QMainWindow>
#include <QResizeEvent>
#include <QWidget>
#include "base/IScreen.h"
#include "styles/General.h"




UserInterface::CustomMainWindow::CustomMainWindow(QWidget* parent) :
    QMainWindow(parent),
    m_screens(),
    m_activeScreen(nullptr) {



}

void UserInterface::CustomMainWindow::resizeEvent(QResizeEvent* event) {

    QMainWindow::resizeEvent(event);
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

        m_activeScreen = newScreen;
        this->setCentralWidget(newScreen);

    }

}