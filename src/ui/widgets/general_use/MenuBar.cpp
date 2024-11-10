#include "MenuBar.h"

#include <QAction>
#include <QDialog>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>
#include "IPresenter.h"



UserInterface::Widgets::MenuBar::MenuBar(IPresenter* presenter, QWidget* parent) :
    QMenuBar(parent),
    m_presenter(presenter) {

    QMenu* menu = addMenu(QString::fromUtf8("RaceSimEngineer"));
    Q_ASSERT(menu);

    // export
    QAction* exportAct = new QAction(QString::fromUtf8("Export race results"));
    connect(exportAct, &QAction::triggered, this, &UserInterface::Widgets::MenuBar::fileExportRequested);
    menu->addAction(exportAct);

    // settings
    QAction* settingsAct = new QAction(QString::fromUtf8("Settings"));
    Q_ASSERT(settingsAct);
    connect(settingsAct, &QAction::triggered, this, &UserInterface::Widgets::MenuBar::settingsRequested);
    menu->addAction(settingsAct);

    // about
    QAction* aboutAct = new QAction(QString::fromUtf8("About"));
    Q_ASSERT(aboutAct);
    connect(aboutAct, &QAction::triggered, this, &UserInterface::Widgets::MenuBar::aboutRequested);
    menu->addAction(aboutAct);

}



UserInterface::Widgets::MenuBar::~MenuBar() {

}



void UserInterface::Widgets::MenuBar::fileExportRequested() {

    QString folderPath = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Choose directory to export race data"));
    qDebug() << folderPath;
    if (m_presenter) m_presenter->exportRaceToFolder(folderPath);

}



void UserInterface::Widgets::MenuBar::settingsRequested() {

    QDialog settingsDialog;
    settingsDialog.setFixedSize(QSize(720, 540));
    settingsDialog.setWindowTitle(QString::fromUtf8("Settings"));
    settingsDialog.exec();

}



void UserInterface::Widgets::MenuBar::aboutRequested() {

    QDialog aboutDialog;
    aboutDialog.setFixedSize(QSize(540, 320));
    aboutDialog.setWindowTitle(QString::fromUtf8("About RaceSimEngineer"));
    aboutDialog.exec();

}