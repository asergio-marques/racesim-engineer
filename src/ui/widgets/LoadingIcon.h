#ifndef USERINTERFACE_WIDGETS_INCLUDE_LOADING_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_LOADING_ICON_H_

#include <QPixmap>
#include <QSize>
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
                bool Update() override final;
                void Move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override final;
                virtual void Scale(const uint8_t percent) override final;
                virtual void Scale(const uint8_t percentX, const uint8_t percentY) override final;

                // Getters
                const int16_t Width() const override;
                const int16_t Height() const override;

            protected:
                QLabel* m_rotateImage;
                QPixmap m_rotatePixmap;
                QSize m_originalSizeRotate;
                QPropertyAnimation* m_anim;
                qreal m_currentRotation;

            private slots:
                void onAnimUpdate(const QVariant& value);

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_LOADING_ICON_H_