#ifndef USERINTERFACE_WIDGETS_INCLUDE_SETTINGS_DIALOG_H_
#define USERINTERFACE_WIDGETS_INCLUDE_SETTINGS_DIALOG_H_

#include <QDialog>
#include <QMap>
#include <QWidget>
#include "settings/Key.h"



class QGridLayout;

namespace Presenter {

    class ICompFacade;

}

namespace UserInterface {

    namespace Widgets {

        class SettingsDialog final : public QDialog {

            public:
            SettingsDialog(Presenter::ICompFacade* presenter, QWidget* parent = nullptr);
            ~SettingsDialog() = default;

            private:
            void prepareSettings();

            QGridLayout* m_grid;

            // pointer to the presenter for reading settings
            Presenter::ICompFacade* m_presenter;

            // indentation to the edges of the dialog
            static const uint8_t EDGE_INDENT;

            // Traces widgets to setting indexes
            QMap<const uint8_t, QWidget*> m_settingsTrace;

            // Lists all settings' description in the UI
            QMap<const Settings::Key, QString> m_settingsDescription;
        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_SETTINGS_DIALOG_H_