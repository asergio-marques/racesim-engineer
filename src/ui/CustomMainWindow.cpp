#include "CustomMainWindow.h"

#include <QAction>
#include <QApplication>
#include <QDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
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
    QMenuBar* menuBar = new QMenuBar(this);
    Q_ASSERT(menuBar);
    if (menuBar) {
        QMenu* menu = menuBar->addMenu(QString::fromUtf8("RaceSimEngineer"));
        Q_ASSERT(menu);

        // export
        QAction* exportAct = new QAction(QString::fromUtf8("Export race results"));
        connect(exportAct, &QAction::triggered, this, [&](bool checked) {
            QString folderPath = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Choose directory to export race data"));
            
            });
        menu->addAction(exportAct);

        // settings
        QAction* settingsAct = new QAction(QString::fromUtf8("Settings"));
        Q_ASSERT(settingsAct);
        connect(settingsAct, &QAction::triggered, this, [&](bool checked) {
            QDialog settingsDialog;
            settingsDialog.setFixedSize(QSize(720, 540));
            settingsDialog.setWindowTitle(QString::fromUtf8("Settings"));
            settingsDialog.exec();
            });

        menu->addAction(settingsAct);
        // about
        QAction* aboutAct = new QAction(QString::fromUtf8("About"));
        Q_ASSERT(aboutAct);
        connect(aboutAct, &QAction::triggered, this, [&](bool checked) {
            QDialog aboutDialog;
            aboutDialog.setFixedSize(QSize(540, 320));
            aboutDialog.setWindowTitle(QString::fromUtf8("About RaceSimEngineer"));
            aboutDialog.exec();
            });
        menu->addAction(aboutAct);


        setMenuBar(menuBar);
    }
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