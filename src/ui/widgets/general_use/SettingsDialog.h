#ifndef USERINTERFACE_WIDGETS_INCLUDE_SETTINGS_DIALOG_H_
#define USERINTERFACE_WIDGETS_INCLUDE_SETTINGS_DIALOG_H_

#include <QDialog>
#include <QWidget>



namespace Presenter {

    class ICompFacade;

}

namespace UserInterface {

    namespace Widgets {

        class SettingsDialog final : public QDialog {

            public:
            SettingsDialog(Presenter::ICompFacade* presenter, QWidget* parent = 0);
            ~SettingsDialog() = default;

            private:
            Presenter::ICompFacade* m_presenter;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_SETTINGS_DIALOG_H_