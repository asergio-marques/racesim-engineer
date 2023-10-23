#ifndef USERINTERFACE_BASE_INCLUDE_ISINGLEPANELSCREEN_H_
#define USERINTERFACE_BASE_INCLUDE_ISINGLEPANELSCREEN_H_

#include <QWidget>
#include "base/IScreen.h"
#include "settings/WindowNumber.h"



namespace UserInterface {

    namespace Base {

        class IPanel;

        class ISinglePanelScreen : public IScreen {

            Q_OBJECT

            public:
                ISinglePanelScreen(QWidget* parent = 0);
                virtual ~ISinglePanelScreen() = default;

                virtual void Initialize() override;
                virtual bool Activate() override;
                virtual bool Deactivate() override;

            public slots:
                virtual void handleResizeEvent(QResizeEvent* event) override final;

            protected:
                Settings::WindowNumber m_mode;
                UserInterface::Base::IPanel* m_panel;

        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_ISINGLEPANELSCREEN_H_