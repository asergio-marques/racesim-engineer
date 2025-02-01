#ifndef USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_
#define USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_

#include <QLabel>
#include "ScreenType.h"



namespace UserInterface {

    namespace Widget {

        class ScreenTitle final : public QLabel {

            Q_OBJECT

            public:
                ScreenTitle(QWidget* parent = 0);
                virtual ~ScreenTitle() = default;
                void setTitle(UserInterface::Screen::Type type);

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_