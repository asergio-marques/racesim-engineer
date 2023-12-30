#ifndef USERINTERFACE_PANELS_INCLUDE_RACE_RIGHT_H_
#define USERINTERFACE_PANELS_INCLUDE_RACE_RIGHT_H_

#include <QSize>
#include "panels/Interface.h"

class QWidget;



namespace UserInterface {

    namespace Panel {

        class RaceRight final : public UserInterface::Panel::Interface {

            Q_OBJECT

            public:
                RaceRight(QWidget* parent = 0);
                virtual ~RaceRight() = default;
                virtual void ResizePanel(const QSize& newPanelSize) override final;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_RACE_RIGHT_H_