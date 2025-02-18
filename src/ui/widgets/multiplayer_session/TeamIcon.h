#ifndef USERINTERFACE_WIDGETS_INCLUDE_TEAM_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_TEAM_ICON_H_

#include <QPixmap>
#include <QLabel>
#include "data/internal/Session.h"




namespace UserInterface {

    namespace Widget {

        class TeamIcon : public QLabel {

            public:
            TeamIcon(QWidget* parent = 0);
            ~TeamIcon() = default;
            void SetTeam(const Session::Internal::TeamID& teamID);

            private:
            bool m_isSet;
            QPixmap m_pixmap;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_TEAM_ICON_H_