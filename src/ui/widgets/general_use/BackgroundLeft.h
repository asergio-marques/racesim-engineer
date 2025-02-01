#ifndef USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_LEFT_H_
#define USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_LEFT_H_

#include <QLabel>

namespace UserInterface {

    namespace Widget {

        class BackgroundLeft final : public QLabel {

            Q_OBJECT

            public:
            BackgroundLeft(QWidget* parent = 0);
            virtual ~BackgroundLeft() = default;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_LEFT_H_