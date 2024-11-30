#include "SettingsDialog.h"

#include <QDialog>




UserInterface::Widgets::SettingsDialog::SettingsDialog(Presenter::ICompFacade* presenter, QWidget* parent) :
    QDialog(parent),
    m_presenter(presenter) {

    setFixedSize(QSize(720, 540));
    setWindowTitle(QString::fromUtf8("Settings"));

}