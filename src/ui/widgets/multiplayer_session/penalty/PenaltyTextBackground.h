#ifndef USERINTERFACE_WIDGETS_INCLUDE_PENALTY_TEXT_BACKGROUND_H_
#define USERINTERFACE_WIDGETS_INCLUDE_PENALTY_TEXT_BACKGROUND_H_

#include <QLabel>



class QWidget;

namespace UserInterface {

    namespace Widget {

        class PenaltyTextBackground : public QLabel {

            public:
            PenaltyTextBackground(QWidget* parent = 0);
            ~PenaltyTextBackground() = default;

            private:
            QPixmap m_pixmap;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_PENALTY_TEXT_BACKGROUND_H_