#ifndef USERINTERFACE_INCLUDE_UI_STARTER_H_
#define USERINTERFACE_INCLUDE_UI_STARTER_H_

class QApplication;


namespace UserInterface {

    class UIStarter {

    public:
        UIStarter() = default;
        virtual ~UIStarter() = default;
        void Init(int* argc, char*** argv);
        int Run();

    private:
        QApplication* app;

    };

}

#endif // USERINTERFACE_INCLUDE_UI_STARTER_H_