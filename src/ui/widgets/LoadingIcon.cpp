#include "widgets/LoadingIcon.h"

#include <QPropertyAnimation>
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QWidget>
#include "base/elements/ImageElement.h"
#include "base/WidgetId.h"



UserInterface::Widget::LoadingIcon::LoadingIcon(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::ImageElement(id, parent),
    m_rotateImage(new QLabel(parent)),
    m_rotatePixmap(),
    m_originalSizeRotate(QSize(0, 0)),
    m_currentRotation(0.0f),
    m_anim(new QPropertyAnimation) {

    if (m_image && m_rotateImage && m_anim) {

        m_rotateImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        bool res = m_pixmap.load(":img/icons/logo_loading_center.png");
        res &= m_rotatePixmap.load(":img/icons/logo_loading_rotate.png");
        if (res) {

            m_anim->setTargetObject(m_rotateImage);
            m_anim->setDuration(4000);
            m_anim->setStartValue(0.0f);
            m_anim->setEndValue(360.0f);
            m_anim->setLoopCount(-1);
            connect(m_anim, &QVariantAnimation::valueChanged, this, &UserInterface::Widget::LoadingIcon::onAnimUpdate);

            m_image->setPixmap(m_pixmap);
            m_rotateImage->setPixmap(m_rotatePixmap);
            m_originalSize.setWidth(m_pixmap.width());
            m_originalSize.setHeight(m_pixmap.height());
            m_originalSizeRotate.setWidth(m_rotatePixmap.width());
            m_originalSizeRotate.setHeight(m_rotatePixmap.height());

            m_anim->start();

        }

    }

}



bool UserInterface::Widget::LoadingIcon::Update() {

    // Never updated?
    return false;

}

void UserInterface::Widget::LoadingIcon::Move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    if (m_image && m_rotateImage) {

        // calc the offset between the two icons
        int16_t centerDx = (m_rotateImage->width() - m_image->width()) / 2;
        int16_t centerDy = (m_rotateImage->height() - m_image->height()) / 2;

        uint16_t newX = 0;
        uint16_t newY = 0;

        if (centerAlignmentX) newX = x - (m_rotateImage->width() / 2);
        else newX = x;
        if (centerAlignmentY) newY = y - (m_rotateImage->height() / 2);
        else newY = y;

        m_rotateImage->move(newX, newY);
        m_image->move(newX + centerDx, newY + centerDy);

    }

}



void UserInterface::Widget::LoadingIcon::Scale(const uint8_t percent) {

    UserInterface::Base::ImageElement::Scale(percent);

    if (m_rotateImage) {

        QSize newSize;
        int16_t newWidth = (m_originalSizeRotate.width() * percent) / 100;
        int16_t newHeight = (m_originalSizeRotate.height() * percent) / 100;

        // reloading the pixmap prevents compression artifacts from causing the distortion of the image
        // we use the saved rotation value as to avoid some slight visual bugs
        m_rotatePixmap.load(":img/icons/logo_loading_rotate.png");
        m_rotatePixmap = m_rotatePixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio);
        m_rotatePixmap = m_rotatePixmap.transformed(QTransform().rotate(m_currentRotation));
        m_rotateImage->setPixmap(m_rotatePixmap);
        m_rotateImage->setFixedSize(newWidth, newHeight);

    }

}



void UserInterface::Widget::LoadingIcon::Scale(const uint8_t percentX, const uint8_t percentY) {

    UserInterface::Base::ImageElement::Scale(percentX, percentY);

    if (m_rotateImage) {

        QSize newSize;
        int16_t newWidth = (m_originalSizeRotate.width() * percentX) / 100;
        int16_t newHeight = (m_originalSizeRotate.height() * percentY) / 100;
        m_rotateImage->setPixmap(m_rotatePixmap.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio));
        m_rotateImage->setFixedSize(newWidth, newHeight);

    }

}



const int16_t UserInterface::Widget::LoadingIcon::Width() const {

    if (m_rotateImage) {

        return qMax(m_rotateImage->width(), UserInterface::Base::ImageElement::Width());

    }

    return UserInterface::Base::ImageElement::Width();

}



const int16_t UserInterface::Widget::LoadingIcon::Height() const {

    if (m_rotateImage) {

        return qMax(m_rotateImage->height(), UserInterface::Base::ImageElement::Height());

    }

    return UserInterface::Base::ImageElement::Height();

}



void UserInterface::Widget::LoadingIcon::onAnimUpdate(const QVariant& value) {

    QTransform t;
    // save the current value to be used for scaling in case it is needed
    m_currentRotation = value.toReal();
    t.rotate(m_currentRotation);
    m_rotateImage->setPixmap(m_rotatePixmap.transformed(t));

}