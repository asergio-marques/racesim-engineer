#ifndef USERINTERFACE_BASE_INCLUDE_ISCREEN_H_
#define USERINTERFACE_BASE_INCLUDE_ISCREEN_H_

#include <QWidget>
#include "settings/WindowNumber.h"



namespace UserInterface {

    namespace Base {

        class IPanel;

        class IScreen : public QWidget {

            Q_OBJECT

            public:
                IScreen(QWidget* parent = 0);
                virtual ~IScreen() = default;

                virtual void Initialize() = 0;
                virtual bool Activate() = 0;
                virtual bool Deactivate() = 0;
                // virtual void Update(const InternalInfoPacket* updateInfo) = 0;

            public slots:
                virtual void handleResizeEvent(QResizeEvent* event) { qDebug() << "unspecific resizeevent"; }

        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_ISCREEN_H_