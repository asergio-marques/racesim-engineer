#include "MenuBar.h"

#include <QAction>
#include <QDialog>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>
#include "ICompFacade.h"
#include "IProcessor.h"
#include "general_use/SettingsDialog.h"



UserInterface::Widgets::MenuBar::MenuBar(Presenter::ICompFacade* presenter, QWidget* parent) :
    QMenuBar(parent),
    m_presenter(presenter),
    m_mainMenu(nullptr),
    m_exportAction(nullptr),
    m_sessionClearAction(nullptr) {

    m_mainMenu = addMenu(QString::fromUtf8("RaceSimEngineer"));
    Q_ASSERT(m_mainMenu);

    // export, needs to be saved so it's toggleable
    m_exportAction = new QAction(QString::fromUtf8("Export race results"));
    Q_ASSERT(m_exportAction);
    m_exportAction->setEnabled(true);
    connect(m_exportAction, &QAction::triggered, this, &UserInterface::Widgets::MenuBar::fileExportRequested);
    m_mainMenu->addAction(m_exportAction);

    // session data clear, needs to be saved so it's toggleable
    m_sessionClearAction = new QAction(QString::fromUtf8("Clear current session data"));
    Q_ASSERT(m_sessionClearAction);
    m_sessionClearAction->setEnabled(true);
    connect(m_sessionClearAction, &QAction::triggered, this, &UserInterface::Widgets::MenuBar::clearCurrentSessionRequested);
    m_mainMenu->addAction(m_sessionClearAction);

    // settings
    QAction* settingsAct = new QAction(QString::fromUtf8("Settings"));
    Q_ASSERT(settingsAct);
    connect(settingsAct, &QAction::triggered, this, &UserInterface::Widgets::MenuBar::settingsRequested);
    m_mainMenu->addAction(settingsAct);

    // about
    QAction* aboutAct = new QAction(QString::fromUtf8("About"));
    Q_ASSERT(aboutAct);
    connect(aboutAct, &QAction::triggered, this, &UserInterface::Widgets::MenuBar::aboutRequested);
    m_mainMenu->addAction(aboutAct);

}



UserInterface::Widgets::MenuBar::~MenuBar() {

}



void UserInterface::Widgets::MenuBar::enableSessionActions(bool enabled) {

    Q_ASSERT(m_exportAction);
    m_exportAction->setEnabled(enabled);

    Q_ASSERT(m_sessionClearAction);
    m_sessionClearAction->setEnabled(enabled);

}



void UserInterface::Widgets::MenuBar::fileExportRequested() {

    QString folderPath = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Choose directory to export race data"));
    bool retval = false;
    if (m_presenter) {

        auto procPresenter = dynamic_cast<Presenter::IProcessor*>(m_presenter);
        if (procPresenter) {

            retval = procPresenter->exportRaceToFolder(folderPath);

        }

    }
    if (!retval) {
        QDialog dialog;
        dialog.setFixedSize(QSize(300, 200));
        dialog.setWindowTitle(QString::fromUtf8("Error saving export!"));
        dialog.exec();
    }

}

void UserInterface::Widgets::MenuBar::clearCurrentSessionRequested() {

    // TODO

}



void UserInterface::Widgets::MenuBar::settingsRequested() {

    UserInterface::Widgets::SettingsDialog settingsDialog(m_presenter, parentWidget());
    settingsDialog.exec();

}



void UserInterface::Widgets::MenuBar::aboutRequested() {

    QDialog aboutDialog;
    aboutDialog.setFixedSize(QSize(540, 320));
    aboutDialog.setWindowTitle(QString::fromUtf8("About RaceSimEngineer"));
    aboutDialog.exec();

}