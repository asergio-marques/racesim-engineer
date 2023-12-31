#ifndef USERINTERFACE_WIDGET_INCLUDE_CONTAINER_H_
#define USERINTERFACE_WIDGET_INCLUDE_CONTAINER_H_

#include <QObject>



namespace UserInterface {

    namespace Widget {

        class Container : public QObject {

            Q_OBJECT

            public:
            Container();
            ~Container() = default;
            virtual const int16_t width() = 0;
            virtual const int16_t height() = 0;
            virtual const int16_t x() = 0;
            virtual const int16_t y() = 0;

        };

    }

}


#endif // USERINTERFACE_WIDGET_INCLUDE_CONTAINER_H_