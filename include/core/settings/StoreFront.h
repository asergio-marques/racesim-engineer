#ifndef GENERAL_SETTINGS_INCLUDE_STOREFRONT_H_
#define GENERAL_SETTINGS_INCLUDE_STOREFRONT_H_

#include <map>
#include <string>
#include "settings/Key.h"



class IPresenter;

namespace Processor {

    class IFileIO;

}

namespace Settings {

    // The main entrypoint for anyone requesting settings info, singleton to avoid mismatch issues
    class StoreFront {

    public:
        // Get the one single instance of this class
        static Settings::StoreFront* getInstance();

        // Initialize the settings map by reading the config file (if available) or by filling it with the default values
        const bool Init(IPresenter* presenter);

        // Write the changes to the config file at application close
        const bool Shutdown();

        // Main entry point for obtaining the value of a given setting
        const int64_t getSettingValue(const Settings::Key& key, bool& ok) const;

        // Main entry point for changing the value of a given setting
        const bool setSettingValue(const Settings::Key& key, const int64_t value);

    private:
        // Singleton private constructor, does nothing
        StoreFront();

        virtual ~StoreFront() = default;

        // Specialized function for reading the configuration file once determined it exists
        const bool readConfig();

        // Whether the settings map has been initialized
        bool m_isInit;

        // Singleton pointer
        static Settings::StoreFront* m_p;

        // Map storing all the active configurations
        std::map<Settings::Key, int64_t> m_settingsMap;

    };

}


#endif // GENERAL_SETTINGS_INCLUDE_STOREFRONT_H_
