#ifndef USERINTERFACE_SCREEN_INCLUDE_SINGLE_PANEL_INTERFACE_H_
#define USERINTERFACE_SCREEN_INCLUDE_SINGLE_PANEL_INTERFACE_H_

#include <QWidget>
#include "screens/Interface.h"
#include "settings/WindowNumber.h"



namespace UserInterface {

    namespace Panel {

        class Interface;

    }

    namespace Screen {

        class SinglePanelInterface : public Interface {

            Q_OBJECT

            public:
                SinglePanelInterface(QWidget* parent = 0);
                virtual ~SinglePanelInterface() = default;

                virtual void Initialize() override;

            public slots:
                virtual void handleResizeEvent(QResizeEvent* event) override final;

            protected:
                Settings::WindowNumber m_mode;
                UserInterface::Panel::Interface* m_panel;

        };

    }

}

#endif // USERINTERFACE_SCREEN_INCLUDE_SINGLE_PANEL_INTERFACE_H_