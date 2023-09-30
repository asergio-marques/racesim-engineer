#ifndef GENERAL_SETTINGS_INCLUDE_STOREFRONT_H_
#define GENERAL_SETTINGS_INCLUDE_STOREFRONT_H_

#include <map>
#include <string>
#include "settings/Key.h"
#include "settings/Game.h"



namespace Settings {

    // The main entrypoint for anyone requesting settings info
    class StoreFront {

    public:
        static Settings::StoreFront* getInstance();
        const bool Init();
        const bool Shutdown();
        const int64_t findIntegerProperty(const Settings::Key& key, bool& ok) const;
        const std::string& findStringProperty(const Settings::Key& key, bool& ok) const;

    private:
        StoreFront();
        virtual ~StoreFront() = default;

        static Settings::StoreFront* m_p;
        std::map<Settings::Key, int64_t> m_integerMap;
        std::map<Settings::Key, std::string> m_stringMap;

    };

}


#endif // GENERAL_SETTINGS_INCLUDE_STOREFRONT_H_
