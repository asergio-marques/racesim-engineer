#ifndef USERINTERFACE_SCREENS_INCLUDE_UI_EXAMPLE_H_
#define USERINTERFACE_SCREENS_INCLUDE_UI_EXAMPLE_H_

#include <QWidget>

class QPixmap;



namespace UserInterface {

    namespace Screen {

        class Example : public QWidget {

        public:
            Example(QWidget* parent = 0);
            virtual ~Example() = default;

        };

    }

}

#endif // USERINTERFACE_SCREENS_INCLUDE_UI_EXAMPLE_H_