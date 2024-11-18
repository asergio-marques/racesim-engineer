#ifndef SETTINGS_INCLUDE_STORE_H_
#define SETTINGS_INCLUDE_STORE_H_

#include <cstdint>
#include <map>
#include <string>
#include "IStore.h"
#include "settings/Key.h"



namespace Presenter {

    class ICompFacade;

}

namespace Settings {

    // The main entrypoint for anyone requesting settings info, singleton to avoid mismatch issues
    class Store : public IStore {

    public:
        // Constructor
        Store();

        // Destructor
        virtual ~Store() = default;

        // Initialize the settings map by reading the config file (if available) or by filling it with the default values
        const bool Init(Presenter::ICompFacade* presenter) override final;

        // Write the changes to the config file at application close
        const bool Shutdown() override final;

        // Main entry point for obtaining the value of a given setting
        const int64_t getSettingValue(const Settings::Key& key, bool& ok) const override final;

        // Main entry point for changing the value of a given setting
        const bool setSettingValue(const Settings::Key& key, const int64_t value) override final;

    private:
        // Specialized function for reading the configuration file once determined it exists
        const bool readConfig();

        // Whether the settings map has been initialized
        bool m_isInit;

        // Map storing all the active configurations
        std::map<Settings::Key, int64_t> m_settingsMap;

    };

}


#endif // SETTINGS_INCLUDE_STORE_H_
