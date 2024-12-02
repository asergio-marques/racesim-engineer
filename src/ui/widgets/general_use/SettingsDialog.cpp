#include "SettingsDialog.h"

#include <QCheckBox>
#include <QDialog>
#include <QGridLayout>
#include <QMap>
#include "ICompFacade.h"
#include "ISettings.h"
#include "settings/Key.h"



const uint8_t UserInterface::Widgets::SettingsDialog::EDGE_INDENT = 72;



UserInterface::Widgets::SettingsDialog::SettingsDialog(Presenter::ICompFacade* presenter, QWidget* parent) :
    QDialog(parent),
    m_grid(nullptr),
    m_presenter(presenter),
    m_settingsTrace(),
    m_settingsDescription() {

    setFixedSize(QSize(720, 540));
    setWindowTitle(QString::fromUtf8("Settings"));

    m_grid = new QGridLayout(this);
    Q_ASSERT(m_grid);
    m_grid->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    prepareSettings();
}



void UserInterface::Widgets::SettingsDialog::prepareSettings() {

    Q_ASSERT(m_presenter);
    Presenter::ISettings* settingsPresenter = dynamic_cast<Presenter::ISettings*>(m_presenter);
    if (settingsPresenter) {
        
        // TODO
        /*for (uint8_t i = 0; i < settingsPresenter->numActiveSettings(); ++i) {

            const auto& settingKey = settingsPresenter->activeSettingAtIndex(i);
            const auto& settingDescription = m_settingsDescription.find(settingKey);
        
            if (settingDescription != m_settingsDescription.cend()) {
                // need to check the type of setting innit
                QCheckBox* box = new QCheckBox(settingDescription.value(), this);
                Q_ASSERT(box);
                m_grid->addWidget(box);

            }

        }*/

        QCheckBox* box = new QCheckBox("Export session data at session end?", this);
        Q_ASSERT(box);
        m_grid->addWidget(box);

    }

}