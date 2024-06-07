#include "multiplayer_session/TeamIcon.h"

#include <QMap>
#include <QString>
#include <QWidget>
#include "base/ID.h"
#include "base/ImageInterface.h"
#include "data/internal/Session.h"



const QMap<Session::Internal::TeamID, QString> UserInterface::Widget::TeamIcon::m_teamIDFilenameMap = {

    { Session::Internal::TeamID::AlfaRomeo,     ":img/teams/AlfaRomeoLogo.png" },
    { Session::Internal::TeamID::AlphaTauri,    ":img/teams/AlphaTauriLogo.png" },
    { Session::Internal::TeamID::Alpine,        ":img/teams/AlpineLogo.png" },
    { Session::Internal::TeamID::AstonMartin,   ":img/teams/AstonMartinLogo.png" },
    { Session::Internal::TeamID::Ferrari,       ":img/teams/FerrariLogo.png" },
    { Session::Internal::TeamID::Haas,          ":img/teams/HaasLogo.png" },
    { Session::Internal::TeamID::McLaren,       ":img/teams/McLarenLogo.png" },
    { Session::Internal::TeamID::Mercedes,      ":img/teams/MercedesLogo.png" },
    { Session::Internal::TeamID::RedBull,       ":img/teams/RedBullLogo.png" },
    { Session::Internal::TeamID::Williams,      ":img/teams/WilliamsLogo.png" },
    { Session::Internal::TeamID::KickSauber,    ":img/teams/KickLogo.png" },
    { Session::Internal::TeamID::VCARB,         ":img/teams/VCARBLogo.png" }

};



UserInterface::Widget::TeamIcon::TeamIcon(QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::DriverTeamIcon, parent),
    m_isSet(false) {



}

void UserInterface::Widget::TeamIcon::SetTeam(const Session::Internal::TeamID& teamID) {

    if (!m_isSet) {

        bool res = false;
        
        auto it = m_teamIDFilenameMap.find(teamID);
        if (it != m_teamIDFilenameMap.end()) {
            auto value = it.value();
            res = m_pixmap.load(value);
        }
        else res = m_pixmap.load(m_unknownIDFilename);

        if (res) {

            setPixmap(m_pixmap, true);
            m_isSet = true;

        }

    }


}