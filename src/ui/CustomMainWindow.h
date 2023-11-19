#ifndef USERINTERFACE_INCLUDE_CUSTOM_MAIN_WINDOW_H_
#define USERINTERFACE_INCLUDE_CUSTOM_MAIN_WINDOW_H_

#include <QMainWindow>

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

        signals:
            void onResizeEvent(QResizeEvent* event);

        protected:
            virtual void resizeEvent(QResizeEvent* event) override;

        private:
            void doAddScreen(UserInterface::Base::IScreen* newScreen);
            std::list<UserInterface::Base::IScreen*> m_screens;

    };

}


#endif // USERINTERFACE_INCLUDE_CUSTOM_MAIN_WINDOW_H_