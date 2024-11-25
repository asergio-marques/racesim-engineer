#ifndef SETTINGS_INCLUDE_ISTORE_H_
#define SETTINGS_INCLUDE_ISTORE_H_

#include <cstdint>
#include <string>
#include "settings/Key.h"



namespace Presenter {

    class ICompFacade;

}

namespace Settings {

    // The main entrypoint for anyone requesting settings info, singleton to avoid mismatch issues
    class IStore {

    public:
        // Constructor
        IStore() = default;

        // Destructor
        virtual ~IStore() = default;

        // Initialize the settings map by reading the config file (if available) or by filling it with the default values
        virtual const bool Init(Presenter::ICompFacade* presenter) = 0;

        // Write the changes to the config file at application close
        virtual const bool Shutdown() = 0;

        // Main entry point for obtaining the value of a given setting
        virtual const int64_t getSettingValue(const Settings::Key& key, bool& ok) const = 0;

        // Main entry point for changing the value of a given setting
        virtual const bool setSettingValue(const Settings::Key& key, const int64_t value) = 0;

    };

}


#endif // SETTINGS_INCLUDE_ISTORE_H_
