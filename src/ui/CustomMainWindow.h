#ifndef USERINTERFACE_INCLUDE_CUSTOM_MAIN_WINDOW_H_
#define USERINTERFACE_INCLUDE_CUSTOM_MAIN_WINDOW_H_

#include <QMainWindow>
#include "base/ScreenType.h"

class QResizeEvent;
class QWidget;



namespace UserInterface {

    namespace Base {
        
        class IScreen;

    }

    class CustomMainWindow : public QMainWindow {

        Q_OBJECT

        public:
            CustomMainWindow(QWidget* parent = 0);
            virtual ~CustomMainWindow() = default;
            void addScreen(UserInterface::Base::IScreen* newScreen);
            // TODO these functions are to take in session start internal packets,
            // but these are yet to be implemented
            void OnSessionEnd();
            void OnTimeTrialStart();
            void OnFreePracticeStart();
            void OnQualiStart();
            void OnRaceStart();

        signals:
            void onResizeEvent(QResizeEvent* event);

        protected:
            virtual void resizeEvent(QResizeEvent* event) override;

        private:
            void doAddScreen(UserInterface::Base::IScreen* newScreen);
            void doSwitchScreen(const UserInterface::Base::ScreenType type);
            std::list<UserInterface::Base::IScreen*> m_screens;
            UserInterface::Base::IScreen* m_activeScreen;

    };

}


#endif // USERINTERFACE_INCLUDE_CUSTOM_MAIN_WINDOW_H_