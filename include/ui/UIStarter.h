#ifndef USERINTERFACE_INCLUDE_UI_STARTER_H_
#define USERINTERFACE_INCLUDE_UI_STARTER_H_

class QApplication;
class QWidget;



namespace UserInterface {

    class CustomMainWindow;

    class UIStarter {

    public:
        UIStarter() = default;
        virtual ~UIStarter();
        void Init(int* argc, char*** argv);
        int Run();
        // TODO these functions are to take in session start internal packets,
        // but these are yet to be implemented
        void OnSessionEnd();
        void OnTimeTrialStart();
        void OnFreePracticeStart();
        void OnQualiStart();
        void OnRaceStart();

    private:
        QApplication* m_app;
        UserInterface::CustomMainWindow* m_window;

    };

}

#endif // USERINTERFACE_INCLUDE_UI_STARTER_H_