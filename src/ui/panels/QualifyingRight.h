#ifndef USERINTERFACE_PANELS_INCLUDE_QUALIFYING_RIGHT_H_
#define USERINTERFACE_PANELS_INCLUDE_QUALIFYING_RIGHT_H_

#include <QSize>
#include "base/IPanel.h"

class QWidget;



namespace UserInterface {

    namespace Panel {

        class QualifyingRight final : public UserInterface::Base::IPanel {

            Q_OBJECT

            public:
                QualifyingRight(QWidget* parent = 0);
                virtual ~QualifyingRight() = default;
                virtual void ResizePanel(const QSize& newPanelSize) override final;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_QUALIFYING_RIGHT_H_