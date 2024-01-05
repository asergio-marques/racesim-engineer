#ifndef USERINTERFACE_SCREEN_INCLUDE_DUAL_PANEL_INTERFACE_H_
#define USERINTERFACE_SCREEN_INCLUDE_DUAL_PANEL_INTERFACE_H_

#include "screens/Interface.h"
#include "settings/WindowNumber.h"



class QResizeEvent;
class QWidget;

namespace UserInterface {

    namespace Panel {

        class Interface;

    }

    namespace Screen {

        class DualPanelInterface : public Interface {

            Q_OBJECT

            public:
                DualPanelInterface(QWidget* parent = 0);
                virtual ~DualPanelInterface() = default;

                virtual void Initialize() override;

            public slots:
                virtual void handleResizeEvent(QResizeEvent* event) override final;

            protected:
                Settings::WindowNumber m_mode;
                UserInterface::Panel::Interface* m_panelLeft;
                UserInterface::Panel::Interface* m_panelRight;

        };

    }

}

#endif // USERINTERFACE_SCREEN_INCLUDE_DUAL_PANEL_INTERFACE_H_