#ifndef USERINTERFACE_BASE_INCLUDE_IDUALPANELSCREEN_H_
#define USERINTERFACE_BASE_INCLUDE_IDUALPANELSCREEN_H_

#include "base/IScreen.h"
#include "settings/WindowNumber.h"

class QResizeEvent;
class QWidget;

namespace UserInterface {

    namespace Base {

        class IPanel;

        class IDualPanelScreen : public IScreen {

            Q_OBJECT

            public:
                IDualPanelScreen(QWidget* parent = 0);
                virtual ~IDualPanelScreen() = default;

                virtual void Initialize() override;
                virtual bool Activate() override;
                virtual bool Deactivate() override;

            public slots:
                virtual void handleResizeEvent(QResizeEvent* event) override final;

            protected:
                Settings::WindowNumber m_mode;
                UserInterface::Base::IPanel* m_panelLeft;
                UserInterface::Base::IPanel* m_panelRight;

        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_IDUALPANELSCREEN_H_