#include "Store.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include "Defaults.h"
#include "ICompFacade.h"
#include "IStore.h"
#include "Schema.h"
#include "settings/Game.h"
#include "settings/Key.h"
#include "settings/WindowNumber.h"



Settings::Store::Store() :
    Settings::IStore(),
    m_isInit(false),
    m_settingsMap(),
    m_presenter(nullptr) {

}



const bool Settings::Store::Init(Presenter::ICompFacade* presenter) {

    if (presenter) {

        m_presenter = presenter;
        presenter->setSettingsStore(this);

    }

    // If the config file does not exist already, assign the default values for the map
    if (!std::filesystem::exists("config.xml")) {

        static Settings::Defaults m_defaults;

        m_settingsMap.emplace(Settings::Key::Game, static_cast<int64_t>(m_defaults.gameDefault));
        m_settingsMap.emplace(Settings::Key::WindowNumber, static_cast<int64_t>(m_defaults.windowNumDefault));
        m_settingsMap.emplace(Settings::Key::SocketPort, m_defaults.portDefault);
        m_settingsMap.emplace(Settings::Key::AutoExportWhenSessionEnd, m_defaults.autoExportDefault);

        writeConfig();

        m_isInit = true;
        return m_isInit;
    }

    return readConfig();

}



const bool Settings::Store::Shutdown() {

    std::fstream fs;
    fs.open("config.xml", std::fstream::in | std::fstream::out | std::fstream::trunc);
    // TODO write to xml
    fs.close();

    m_settingsMap.clear();
    m_isInit = false;
    return true;

}



const int64_t Settings::Store::getSettingValue(const Settings::Key& key, bool& ok) const {

    if (m_isInit) {

        auto it = m_settingsMap.find(key);
        if (it == m_settingsMap.end()) {

            std::cout << "Property " << static_cast<uint16_t>(key) << " not found." << std::endl;
            ok = false;
            return 0;

        }

        ok = true;
        return it->second;
    }

    ok = false;
    return 0;

}



const bool Settings::Store::setSettingValue(const Settings::Key& key, const int64_t value) {

    if (m_isInit) {

        auto it = m_settingsMap.find(key);
        if (it == m_settingsMap.end()) {

            std::cout << "Property " << static_cast<uint16_t>(key) << " not found." << std::endl;
            return false;

        }

        // TODO new value validation
        it->second = value;
        return true;
    }

    return false;

}



const bool Settings::Store::readConfig() {

    std::fstream fs;
    fs.open("config.xml", std::fstream::in | std::fstream::out | std::fstream::app);

    m_isInit = true;
    return m_isInit;

}



const bool Settings::Store::writeConfig() {

    return true;

}