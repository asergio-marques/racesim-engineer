#include "multiplayer_session/TeamIcon.h"

#include <QMap>
#include <QString>
#include <QWidget>
#include "PixmapFactory.h"
#include <QLabel>
#include "data/internal/Session.h"



UserInterface::Widget::TeamIcon::TeamIcon(QWidget* parent) :
    QLabel(parent),
    m_isSet(false) {



}

void UserInterface::Widget::TeamIcon::SetTeam(const Session::Internal::TeamID& teamID) {

    if (!m_isSet) {

        UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
        Q_ASSERT(instance);
        if (instance && instance->fetchPixmap(instance->convertTeamID(teamID), m_pixmap)) {

            setPixmap(m_pixmap);
            m_isSet = true;

        }

    }

}