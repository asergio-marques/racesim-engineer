#include "CustomMainWindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QResizeEvent>
#include <QTimer>
#include <QWidget>
#include "screens/Interface.h"
#include "core/ScreenType.h"
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



void UserInterface::CustomMainWindow::addScreen(UserInterface::Screen::Interface* newScreen) {
    
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
    if (withDelay) {
        QTimer::singleShot(120000, this, [&]() {
            if (doSwitchScreen(UserInterface::Screen::Type::Loading)) {
                QCoreApplication::setApplicationName("RaceSimEngineer - Waiting for Session...");
            };
        });
    }
    else {
        if (doSwitchScreen(UserInterface::Screen::Type::Loading)) {
            // TODO: Isn't working for some reason
            QCoreApplication::setApplicationName("RaceSimEngineer - Waiting for Session...");
        }
    }

}



void UserInterface::CustomMainWindow::OnTimeTrialStart() {

    if (doSwitchScreen(UserInterface::Screen::Type::TimeTrial)) {

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Time Trial");

    }

}



void UserInterface::CustomMainWindow::OnFreePracticeStart() {

    if (doSwitchScreen(UserInterface::Screen::Type::FreePractice)) {

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Practice");

    }

}



void UserInterface::CustomMainWindow::OnQualiStart() {

    if (doSwitchScreen(UserInterface::Screen::Type::Qualifying)) {

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Qualifying");

    }

}



void UserInterface::CustomMainWindow::OnRaceStart() {

    if (doSwitchScreen(UserInterface::Screen::Type::Race)) {

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Race");

    }

}



void UserInterface::CustomMainWindow::doAddScreen(UserInterface::Screen::Interface* newScreen) {

    newScreen->setParent(this);
    m_screens.push_back(newScreen);
    connect(this, &UserInterface::CustomMainWindow::onResizeEvent, newScreen, &UserInterface::Screen::Interface::handleResizeEvent);
    newScreen->Initialize();

}



bool UserInterface::CustomMainWindow::doSwitchScreen(const UserInterface::Screen::Type type) {

    // avoid switching screen to already-present screen by returning early
    if (m_activeScreen && (m_activeScreen->Type() == type)) {

        return false;

    }


    UserInterface::Screen::Interface* screenToBeActivated = nullptr;

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