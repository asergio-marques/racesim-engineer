#ifndef USERINTERFACE_SCREEN_INCLUDE_INTERFACE_H_
#define USERINTERFACE_SCREEN_INCLUDE_INTERFACE_H_

#include <QWidget>
#include "core/ScreenType.h"
#include "settings/WindowNumber.h"




namespace UserInterface {

    namespace Panel {

        class Interface;

    }

    namespace Screen {

        class Interface : public QWidget {

            Q_OBJECT

            public:
                Interface(QWidget* parent = 0);
                virtual ~Interface() = default;

                virtual void Initialize() = 0;
                // virtual void Update(const InternalInfoPacket* updateInfo) = 0;
                virtual const UserInterface::Screen::Type Type() const = 0;

            public slots:
                virtual void handleResizeEvent(QResizeEvent* event) = 0;

        };

    }

}

#endif // USERINTERFACE_SCREEN_INCLUDE_INTERFACE_H_