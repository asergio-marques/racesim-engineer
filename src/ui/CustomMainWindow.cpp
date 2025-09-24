#include "CustomMainWindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QResizeEvent>
#include <QSharedPointer>
#include <QTimer>
#include <QWidget>
#include <QWindow>
#include "ICompFacade.h"
#include "IProcessor.h"
#include "core/Screen.h"
#include "screens/Interface.h"
#include "widgets/general_use/MenuBar.h"



UserInterface::CustomMainWindow::CustomMainWindow(Presenter::ICompFacade* presenter, QWidget* parent) :
    QMainWindow(parent),
    m_menuBar(new UserInterface::Widgets::MenuBar(presenter, this)),
    m_screens(),
    m_activeScreen(nullptr),
    m_presenter(presenter) {

    Q_ASSERT(m_menuBar);
    setMenuBar(m_menuBar);

}



void UserInterface::CustomMainWindow::resizeEvent(QResizeEvent* event) {

    QMainWindow::resizeEvent(event);
    emit onResizeEvent(event->size());

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



void UserInterface::CustomMainWindow::Startup() {

    doSwitchScreen(UserInterface::Screen::Type::Loading, nullptr);
    QCoreApplication::setApplicationName("RaceSimEngineer - Waiting for Session...");

}



void UserInterface::CustomMainWindow::OnSessionEnd() {

    uint8_t count = 30;
    QMessageBox box(this);
    box.setIcon(QMessageBox::Warning);
    box.setWindowTitle("Session has ended");
    box.setText(QString("The current session has been marked as finalized.\n"
        "Please close this dialog to clear the session data and export it.\n"));
    box.setStandardButtons(QMessageBox::Close);
    box.exec();

    if (m_presenter) {

        auto procPresenter = dynamic_cast<Presenter::IProcessor*>(m_presenter);
        if (procPresenter) {

            procPresenter->exportSessionToFolder(".");
            procPresenter->clearSessionData();

        }

    }
    OnSessionDataClear();

}



void UserInterface::CustomMainWindow::OnSessionDataClear() {

    if (doSwitchScreen(UserInterface::Screen::Type::Loading, nullptr)) {

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Waiting for Session...");

    }

}



void UserInterface::CustomMainWindow::OnTimeTrialStart(QSharedPointer<const Packet::Event::Interface> packet) {

    if (doSwitchScreen(UserInterface::Screen::Type::TimeTrial, packet)) {

        Q_ASSERT(m_menuBar);
        m_menuBar->enableSessionActions(true);

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Time Trial");

    }

}



void UserInterface::CustomMainWindow::OnFreePracticeStart(QSharedPointer<const Packet::Event::Interface> packet) {

    if (doSwitchScreen(UserInterface::Screen::Type::FreePractice, packet)) {

        Q_ASSERT(m_menuBar);
        m_menuBar->enableSessionActions(true);

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Practice");

    }

}



void UserInterface::CustomMainWindow::OnQualiStart(QSharedPointer<const Packet::Event::Interface> packet) {

    if (doSwitchScreen(UserInterface::Screen::Type::Qualifying, packet)) {

        Q_ASSERT(m_menuBar);
        m_menuBar->enableSessionActions(true);

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Qualifying");

    }

}



void UserInterface::CustomMainWindow::OnRaceStart(QSharedPointer<const Packet::Event::Interface> packet) {

    if (doSwitchScreen(UserInterface::Screen::Type::Race, packet)) {

        Q_ASSERT(m_menuBar);
        m_menuBar->enableSessionActions(true);

        // TODO: Isn't working for some reason
        QCoreApplication::setApplicationName("RaceSimEngineer - Race");

    }

}



void UserInterface::CustomMainWindow::doAddScreen(UserInterface::Screen::Interface* newScreen) {

    newScreen->setParent(this);
    m_screens.push_back(newScreen);
    connect(this, &UserInterface::CustomMainWindow::onResizeEvent, newScreen, &UserInterface::Screen::Interface::handleResizeEvent);

}



bool UserInterface::CustomMainWindow::doSwitchScreen(const UserInterface::Screen::Type type, QSharedPointer<const Packet::Event::Interface> startInfo) {

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
            m_activeScreen->Deactivate();
            takeCentralWidget();

        }

        setCentralWidget(screenToBeActivated);
        screenToBeActivated->show();
        screenToBeActivated->Activate(startInfo);
        m_activeScreen = screenToBeActivated;
        return true;

    }

    return false;

}