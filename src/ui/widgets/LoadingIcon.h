#ifndef USERINTERFACE_WIDGETS_INCLUDE_LOADING_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_LOADING_ICON_H_

#include <QPixmap>
#include "base/elements/ImageElement.h"
#include "base/WidgetId.h"

class QPropertyAnimation;
class QLabel;



namespace UserInterface {

    namespace Widget {

        class LoadingIcon final : public UserInterface::Base::ImageElement {

            Q_OBJECT

            public:
                LoadingIcon(UserInterface::Base::WidgetId id, QWidget* parent = 0);
                virtual ~LoadingIcon() = default;
                
                // Operations
                bool Update() final;
                void Move(int16_t x, int16_t y) final;

                // Getters
                const int16_t Width() const final;
                const int16_t Height() const final;

            protected:
                QLabel* m_rotateImage;
                QPropertyAnimation* m_anim;
                QPixmap m_rotatePixmap;
                QPixmap m_centerPixmap;

            private slots:
                void onAnimUpdate(const QVariant& value);

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_LOADING_ICON_H_