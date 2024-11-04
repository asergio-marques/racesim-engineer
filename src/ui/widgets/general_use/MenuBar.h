#ifndef USERINTERFACE_WIDGETS_INCLUDE_MENU_BAR_H_
#define USERINTERFACE_WIDGETS_INCLUDE_MENU_BAR_H_

#include <QMenuBar>
#include <QWidget>



class IPresenter;

namespace UserInterface {

    namespace Widgets {

        class MenuBar final : public QMenuBar {

            Q_OBJECT

            public:
            MenuBar(IPresenter* presenter, QWidget* parent = 0);
            ~MenuBar();

            protected:
            void fileExportRequested();
            void settingsRequested();
            void aboutRequested();

            private:
            IPresenter* const m_presenter;
        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_MENU_BAR_H_