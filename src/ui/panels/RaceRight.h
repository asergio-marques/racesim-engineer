#ifndef USERINTERFACE_PANELS_INCLUDE_RACE_RIGHT_H_
#define USERINTERFACE_PANELS_INCLUDE_RACE_RIGHT_H_

#include <QSize>
#include "base/IPanel.h"

class QWidget;



namespace UserInterface {

    namespace Panel {

        class RaceRight final : public UserInterface::Base::IPanel {

            Q_OBJECT

            public:
                RaceRight(QWidget* parent = 0);
                virtual ~RaceRight() = default;
                virtual void ResizePanel(const QSize& newPanelSize) override final;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_RACE_RIGHT_H_