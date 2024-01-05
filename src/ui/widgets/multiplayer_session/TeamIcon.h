#ifndef USERINTERFACE_WIDGETS_INCLUDE_TEAM_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_TEAM_ICON_H_

#include <QMap>
#include <QString>
#include "base/ImageInterface.h"
#include "data/internal/Session.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class TeamIcon : public UserInterface::Widget::ImageInterface {

            public:
            TeamIcon(QWidget* parent = 0);
            ~TeamIcon() = default;
            void SetTeam(const Session::Internal::TeamID& teamID);

            private:
            bool m_isSet;
            static const QMap<Session::Internal::TeamID, QString> m_teamIDFilenameMap;
            static constexpr char m_unknownIDFilename[] = "hello";

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_TEAM_ICON_H_