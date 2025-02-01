#ifndef USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_FULL_SCREEN_H_
#define USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_FULL_SCREEN_H_

#include <QLabel>



namespace UserInterface {

    namespace Widget {

        class BackgroundFullScreen final : public QLabel {

            Q_OBJECT

            public:
            BackgroundFullScreen(QWidget* parent = 0);
            virtual ~BackgroundFullScreen() = default;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_FULL_SCREEN_H_