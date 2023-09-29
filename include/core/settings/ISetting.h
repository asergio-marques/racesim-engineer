#ifndef GENERAL_SETTINGS_INCLUDE_ISETTING_H_
#define GENERAL_SETTINGS_INCLUDE_ISETTING_H_

#include "settings/Key.h"



namespace Settings {

    class ISetting {

    public:
        ISetting(Settings::Key key);
        virtual ~ISetting() = default;
        const Settings::Key& getKey();

    private:
        Settings::Key m_key;

    };


}


#endif // GENERAL_SETTINGS_INCLUDE_ISETTING_H_