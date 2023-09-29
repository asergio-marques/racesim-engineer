#include "settings/ISetting.h"

#include "settings/Key.h"



Settings::ISetting::ISetting(Settings::Key key) :
    m_key(key) {



}

const Settings::Key& Settings::ISetting::getKey() {

    return m_key;

}