#ifndef PRESENTER_INCLUDE_ISETTINGS_H_
#define PRESENTER_INCLUDE_ISETTINGS_H_

#include <vector>
#include "settings/Key.h"



namespace Presenter {

    class ISettings {

        public:
        ISettings() = default;
        virtual ~ISettings() = default;
        virtual const Settings::Key activeSettingAtIndex(const uint8_t index) const = 0;
        virtual const uint8_t numActiveSettings() const = 0;
        virtual const int64_t getSettingValue(const Settings::Key& key, bool& ok) const = 0;
        virtual const bool setSettingValue(const Settings::Key& key, const int64_t value) = 0;

    };

}

#endif // PRESENTER_INCLUDE_ISETTINGS_H_