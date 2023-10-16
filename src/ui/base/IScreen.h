#ifndef USERINTERFACE_BASE_INCLUDE_ISCREEN_H_
#define USERINTERFACE_BASE_INCLUDE_ISCREEN_H_

#include <QWidget>
#include "settings/WindowNumber.h"



namespace UserInterface {

    namespace Base {

        class IPanel;

        class IScreen : public QWidget {

            public:
                IScreen(QWidget* parent = 0, UserInterface::Base::IPanel* panelLeft = 0, UserInterface::Base::IPanel* panelRight = 0);
                virtual ~IScreen() = default;

                virtual bool Activate();
                virtual bool Deactivate();
                // virtual void Update(const InternalInfoPacket* updateInfo) = 0;

            protected:
                Settings::WindowNumber m_mode;
                UserInterface::Base::IPanel* m_panelLeft;
                UserInterface::Base::IPanel* m_panelRight;

        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_ISCREEN_H_