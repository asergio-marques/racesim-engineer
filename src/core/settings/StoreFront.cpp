#include "settings/Storefront.h"

#include <iostream>
#include <map>
#include <string>
#include "settings/Key.h"
#include "settings/Game.h"



Settings::StoreFront* Settings::StoreFront::m_p = new Settings::StoreFront;



Settings::StoreFront* Settings::StoreFront::getInstance() {

    return m_p;

}



const bool Settings::StoreFront::Init() {

    // TODO read config.xml and store settings
    return true;

}



const bool Settings::StoreFront::Shutdown() {

    // TODO store settings in cache to config.xml
    return true;

}



const int64_t Settings::StoreFront::findIntegerProperty(const Settings::Key& key, bool& ok) const {

    auto it = m_integerMap.find(key);
    if (it == m_integerMap.end()) {

        std::cout << "Property " << static_cast<uint16_t>(key) << " not found." << std::endl;
        ok = false;
        return 0;

    }

    ok = true;
    return it->second;

}



const std::string& Settings::StoreFront::findStringProperty(const Settings::Key& key, bool& ok) const {

    auto it = m_stringMap.find(key);
    if (it == m_stringMap.end()) {

        std::cout << "Property " << static_cast<uint16_t>(key) << " not found." << std::endl;
        ok = false;
        return std::string("");

    }

    ok = true;
    return it->second;

}



Settings::StoreFront::StoreFront() :
    m_integerMap(),
    m_stringMap() {



}