#ifndef USERINTERFACE_INCLUDE_CUSTOM_MAIN_WINDOW_H_
#define USERINTERFACE_INCLUDE_CUSTOM_MAIN_WINDOW_H_

#include <QList>
#include <QMainWindow>
#include <QSharedPointer>
#include <QPair>
#include "core/Screen.h"
#include "packets/event/Interface.h"




class QResizeEvent;
class QWidget;

namespace Presenter {

    class ICompFacade;

}

namespace UserInterface {

    namespace Screen {
        
        class Interface;

    }

    namespace Widgets {

        class MenuBar;

    }

    class CustomMainWindow : public QMainWindow {

        Q_OBJECT

        public:
            CustomMainWindow(Presenter::ICompFacade* presenter, QWidget* parent = 0);
            virtual ~CustomMainWindow() = default;
            void addScreen(UserInterface::Screen::Interface* newScreen);
            void Startup();
            void OnSessionEnd();
            void OnSessionDataClear();
            void OnTimeTrialStart(QSharedPointer<Packet::Event::Interface> packet);
            void OnFreePracticeStart(QSharedPointer<Packet::Event::Interface> packet);
            void OnQualiStart(QSharedPointer<Packet::Event::Interface> packet);
            void OnRaceStart(QSharedPointer<Packet::Event::Interface> packet);

        signals:
            void onResizeEvent(const QSize newUsefulSize);

        protected:
            virtual void resizeEvent(QResizeEvent* event) override;

        private:
            void doAddScreen(UserInterface::Screen::Interface* newScreen);
            bool doSwitchScreen(const UserInterface::Screen::Type type, QSharedPointer<Packet::Event::Interface> startInfo);
            UserInterface::Widgets::MenuBar* m_menuBar;
            std::list<UserInterface::Screen::Interface*> m_screens;
            UserInterface::Screen::Interface* m_activeScreen;
            Presenter::ICompFacade* const m_presenter;

    };

}


#endif // USERINTERFACE_INCLUDE_CUSTOM_MAIN_WINDOW_H_