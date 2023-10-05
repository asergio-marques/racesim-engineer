#ifndef USERINTERFACE_INCLUDE_UI_STARTER_H_
#define USERINTERFACE_INCLUDE_UI_STARTER_H_

class QApplication;
class QMainWindow;
class QWidget;



namespace UserInterface {

    namespace Screen {

        class Example;

    }

    class UIStarter {

    public:
        UIStarter() = default;
        virtual ~UIStarter();
        void Init(int* argc, char*** argv);
        int Run();

    private:
        QApplication* m_app;
        QMainWindow* m_window;
        UserInterface::Screen::Example* m_screen;

    };

}

#endif // USERINTERFACE_INCLUDE_UI_STARTER_H_