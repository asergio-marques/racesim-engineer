#ifndef GENERAL_SETTINGS_INCLUDE_INTERFACE_H_
#define GENERAL_SETTINGS_INCLUDE_INTERFACE_H_

#include "settings/Key.h"
#include "settings/Game.h"



namespace Settings {

    class ISetting;


    // The main entrypoint for anyone requesting settings info
    class Interface {

    public:
        static Settings::Interface* getInstance();
        const bool Init();

        ISetting* getSetting(const Settings::Key key);

    private:
        Interface() = default;
        virtual ~Interface() = default;

        static Settings::Interface* m_p;

    };

}


#endif // GENERAL_SETTINGS_INCLUDE_INTERFACE_H_
