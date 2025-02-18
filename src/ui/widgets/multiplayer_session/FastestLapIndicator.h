#ifndef USERINTERFACE_WIDGETS_INCLUDE_FASTEST_LAP_INDICATOR_H_
#define USERINTERFACE_WIDGETS_INCLUDE_FASTEST_LAP_INDICATOR_H_

#include <QWidget>




namespace UserInterface {

    namespace Widget {

        class FastestLapIndicator : public QWidget {

            public:
            FastestLapIndicator(QWidget* parent = 0);
            ~FastestLapIndicator() = default;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_FASTEST_LAP_INDICATOR_H_