#ifndef USERINTERFACE_WIDGETS_INCLUDE_LOADING_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_LOADING_ICON_H_

#include <QPixmap>
#include <QSize>
#include <QWidget>



class QPropertyAnimation;
class QLabel;
class QResizeEvent;

namespace UserInterface {

    namespace Widget {

        class LoadingIcon final : public QWidget {

            public:
            LoadingIcon(QWidget* parent = 0);
            virtual ~LoadingIcon() = default;

            protected:
            QLabel* m_centerWidget;
            QLabel* m_rotateWidget;
            QPixmap m_centerPixmap;
            QPixmap m_rotatePixmap;
            QPropertyAnimation* m_anim;
            qreal m_currentRotation;

            public slots:
            virtual void resizeEvent(QResizeEvent* event) override;

            private slots:
            void onAnimUpdate(const QVariant& value);

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_LOADING_ICON_H_