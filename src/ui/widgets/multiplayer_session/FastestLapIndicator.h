#ifndef USERINTERFACE_WIDGETS_INCLUDE_FASTEST_LAP_INDICATOR_H_
#define USERINTERFACE_WIDGETS_INCLUDE_FASTEST_LAP_INDICATOR_H_

#include <QLabel>
#include <QPixmap>



class QWidget;

namespace UserInterface {

    namespace Widget {

        class FastestLapIndicator : public QLabel {

            public:
            FastestLapIndicator(QWidget* parent = 0);
            ~FastestLapIndicator() = default;
            
            private:
            QPixmap m_pixmap;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_FASTEST_LAP_INDICATOR_H_