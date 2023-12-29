#include "CustomMainWindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QResizeEvent>
#include <QTimer>
#include <QWidget>
#include "base/IScreen.h"
#include "base/ScreenType.h"
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
    
        newScreen->hide();

        if (m_screens.empty()) {
    
            doAddScreen(newScreen);
            return;

        }

        for (const auto screen : m_screens) {

            // check if it's the exact same screen object being added twice
            // or if it's a second screen of the same type
            if (screen &&
                (screen == newScreen || screen->Type() == newScreen->Type())) {
                
                return;

            }

        }

        doAddScreen(newScreen);

    }

}



void UserInterface::CustomMainWindow::OnSessionEnd(bool withDelay) {

    // TODO figure a way to make this work so the "result screen" hangs on for 
    // a (configurable?) time at the end before switching to the loading screen
    /*if (withDelay) {
        QTimer::singleShot(5000, this, &UserInterface::CustomMainWindow::doSwitchScreen(UserInterface::Base::ScreenType::Loading));
    }
    else {
        doSwitchScreen(UserInterface::Base::ScreenType::Loading);
    }*/

    if (doSwitchScreen(UserInterface::Base::ScreenType::Loading)) {
        
        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Waiting for Session...");

    }

}



void UserInterface::CustomMainWindow::OnTimeTrialStart() {

    if (doSwitchScreen(UserInterface::Base::ScreenType::TimeTrial)) {

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Time Trial");

    }

}



void UserInterface::CustomMainWindow::OnFreePracticeStart() {

    if (doSwitchScreen(UserInterface::Base::ScreenType::FreePractice)) {

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Practice");

    }

}



void UserInterface::CustomMainWindow::OnQualiStart() {

    if (doSwitchScreen(UserInterface::Base::ScreenType::Qualifying)) {

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Qualifying");

    }

}



void UserInterface::CustomMainWindow::OnRaceStart() {

    if (doSwitchScreen(UserInterface::Base::ScreenType::Race)) {

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Race");

    }

}



void UserInterface::CustomMainWindow::doAddScreen(UserInterface::Base::IScreen* newScreen) {

    newScreen->setParent(this);
    m_screens.push_back(newScreen);
    connect(this, &UserInterface::CustomMainWindow::onResizeEvent, newScreen, &UserInterface::Base::IScreen::handleResizeEvent);
    newScreen->Initialize();

}



bool UserInterface::CustomMainWindow::doSwitchScreen(const UserInterface::Base::ScreenType type) {

    // avoid switching screen to already-present screen by returning early
    if (m_activeScreen && (m_activeScreen->Type() == type)) {

        return false;

    }


    UserInterface::Base::IScreen* screenToBeActivated = nullptr;

    for (const auto screen : m_screens) {

        if (screen &&
            ((screen != m_activeScreen) && (screen->Type() == type))) {

            screenToBeActivated = screen;
            break;

        }

    }

    if (screenToBeActivated) {

        // deactivate current screen if there is one, and retrieve ownership
        if (m_activeScreen) {

            m_activeScreen->hide();
            takeCentralWidget();

        }

        setCentralWidget(screenToBeActivated);
        screenToBeActivated->show();
        m_activeScreen = screenToBeActivated;
        return true;

    }

    return false;

}