#ifndef USERINTERFACE_WIDGETS_INCLUDE_PENALTY_FLAG_H_
#define USERINTERFACE_WIDGETS_INCLUDE_PENALTY_FLAG_H_

#include <QLabel>



class QWidget;

namespace UserInterface {

    namespace Widget {

        class PenaltyFlag : public QLabel {

            public:
            PenaltyFlag(QWidget* parent = 0);
            ~PenaltyFlag() = default;

            private:
            QPixmap m_pixmap;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_PENALTY_FLAG_H_