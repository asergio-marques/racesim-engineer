#ifndef USERINTERFACE_WIDGETS_INCLUDE_MENU_BAR_H_
#define USERINTERFACE_WIDGETS_INCLUDE_MENU_BAR_H_

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>



namespace Presenter {

    class ICompFacade;

}

namespace UserInterface {

    namespace Widgets {

        class MenuBar final : public QMenuBar {

            Q_OBJECT

            public:
            MenuBar(Presenter::ICompFacade* presenter, QWidget* parent = 0);
            ~MenuBar();
            void enableSessionActions(bool enabled);

            protected:
            void fileExportRequested();
            void clearCurrentSessionRequested();
            void settingsRequested();
            void aboutRequested();

            private:
            Presenter::ICompFacade* const m_presenter;
            QMenu* m_mainMenu;
            QAction* m_exportAction;
            QAction* m_sessionClearAction;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_MENU_BAR_H_