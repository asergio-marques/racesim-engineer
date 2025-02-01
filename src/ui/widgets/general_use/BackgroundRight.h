#ifndef USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_
#define USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_

#include <QLabel>



namespace UserInterface {

    namespace Widget {

        class BackgroundRight final : public QLabel {

            Q_OBJECT

            public:
            BackgroundRight(QWidget* parent = 0);
            virtual ~BackgroundRight() = default;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_