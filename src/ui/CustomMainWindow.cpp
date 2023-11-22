#include "CustomMainWindow.h"

#include <QMainWindow>
#include <QResizeEvent>
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



void UserInterface::CustomMainWindow::OnSessionEnd() {

    this->doSwitchScreen(UserInterface::Base::ScreenType::Loading);

}



void UserInterface::CustomMainWindow::OnTimeTrialStart() {

    this->doSwitchScreen(UserInterface::Base::ScreenType::TimeTrial);

}



void UserInterface::CustomMainWindow::OnFreePracticeStart() {

    this->doSwitchScreen(UserInterface::Base::ScreenType::FreePractice);

}



void UserInterface::CustomMainWindow::OnQualiStart() {

    this->doSwitchScreen(UserInterface::Base::ScreenType::Qualifying);

}



void UserInterface::CustomMainWindow::OnRaceStart() {

    this->doSwitchScreen(UserInterface::Base::ScreenType::Race);

}



void UserInterface::CustomMainWindow::doAddScreen(UserInterface::Base::IScreen* newScreen) {

    newScreen->setParent(this);
    m_screens.push_back(newScreen);
    connect(this, &UserInterface::CustomMainWindow::onResizeEvent, newScreen, &UserInterface::Base::IScreen::handleResizeEvent);
    newScreen->Initialize();

}



void UserInterface::CustomMainWindow::doSwitchScreen(const UserInterface::Base::ScreenType type) {

    // avoid switching screen to already-present screen by returning early
    if (m_activeScreen && (m_activeScreen->Type() == type)) {

        return;

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
            this->takeCentralWidget();

        }

        this->setCentralWidget(screenToBeActivated);
        screenToBeActivated->show();
        m_activeScreen = screenToBeActivated;

    }

}