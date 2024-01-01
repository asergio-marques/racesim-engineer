#include "LoadingIcon.h"

#include <QPropertyAnimation>
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QWidget>
#include "base/ImageInterface.h"
#include "base/ID.h"



UserInterface::Widget::LoadingIcon::LoadingIcon(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::LoadingIcon),
    m_centerWidget(new UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::LoadingIcon, parent)),
    m_rotateWidget(new UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::LoadingIcon, parent)),
    m_centerPixmap(),
    m_rotatePixmap(),
    m_currentRotation(0.0f),
    m_anim(new QPropertyAnimation) {

    if (m_centerWidget && m_rotateWidget) {

        bool res = m_centerPixmap.load(":img/icons/LogoLoadingCenter.png");
        if (res) m_centerWidget->setPixmap(m_centerPixmap, true);

        res &= m_rotatePixmap.load(":img/icons/LogoLoadingRotate.png");
        if (res) m_rotateWidget->setPixmap(m_rotatePixmap, true);

        if (res && m_anim) {

            m_rotateWidget->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            m_anim->setTargetObject(m_rotateWidget);
            m_anim->setDuration(4000);
            m_anim->setStartValue(0.0f);
            m_anim->setEndValue(360.0f);
            m_anim->setLoopCount(-1);
            connect(m_anim, &QVariantAnimation::valueChanged, this, &UserInterface::Widget::LoadingIcon::onAnimUpdate);

            m_anim->start();

        }

    }

}



void UserInterface::Widget::LoadingIcon::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    if (!m_centerWidget || !m_rotateWidget) {

        return;

    }

    // calc the offset between the two icons
    int16_t centerDx = (m_rotateWidget->width() - m_centerWidget->width()) / 2;
    int16_t centerDy = (m_rotateWidget->height() - m_centerWidget->height()) / 2;

    uint16_t newX = 0;
    uint16_t newY = 0;

    if (centerAlignmentX) newX = x - (m_rotateWidget->width() / 2);
    else newX = x;
    if (centerAlignmentY) newY = y - (m_rotateWidget->height() / 2);
    else newY = y;

    m_rotateWidget->move(newX, newY, false, false);
    m_centerWidget->move(newX + centerDx, newY + centerDy, false, false);

}



void UserInterface::Widget::LoadingIcon::scale(const uint8_t percent) {

    if (m_centerWidget)
    {
        m_centerWidget->scale(percent);
    }
    if (m_rotateWidget) {

        int16_t newWidth = (m_rotateWidget->originalSize().width() * percent) / 100;
        int16_t newHeight = (m_rotateWidget->originalSize().height() * percent) / 100;

        // reloading the pixmap prevents compression artifacts from causing the distortion of the image
        // we use the saved rotation value as to avoid some slight visual bugs
        m_rotatePixmap.load(":img/icons/LogoLoadingRotate.png");
        m_rotatePixmap = m_rotatePixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio);
        m_rotatePixmap = m_rotatePixmap.transformed(QTransform().rotate(m_currentRotation));
        m_rotateWidget->setPixmap(m_rotatePixmap, false);
        m_rotateWidget->setFixedSize(newWidth, newHeight);

    }

}



void UserInterface::Widget::LoadingIcon::scale(const uint8_t percentX, const uint8_t percentY) {

    if (m_centerWidget)
    {
        m_centerWidget->scale(percentX, percentY);
    }
    if (m_rotateWidget) {

        QSize newSize;
        int16_t newWidth = (m_rotateWidget->originalSize().width() * percentX) / 100;
        int16_t newHeight = (m_rotateWidget->originalSize().height() * percentY) / 100;

        // reloading the pixmap prevents compression artifacts from causing the distortion of the image
        // we use the saved rotation value as to avoid some slight visual bugs
        m_rotatePixmap.load(":img/icons/LogoLoadingRotate.png");
        m_rotatePixmap = m_rotatePixmap.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio);
        m_rotatePixmap = m_rotatePixmap.transformed(QTransform().rotate(m_currentRotation));
        m_rotateWidget->setPixmap(m_rotatePixmap, false);
        m_rotateWidget->setFixedSize(newWidth, newHeight);

    }

}



void UserInterface::Widget::LoadingIcon::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    uint8_t scaleX = newWidth / width();
    uint8_t scaleY = newHeight / height();
    scale(newWidth, newHeight);

}



const int16_t UserInterface::Widget::LoadingIcon::width() const {

    if (m_centerWidget && m_rotateWidget) {

        return qMax(m_centerWidget->width(), m_rotateWidget->width());

    }

    return 0;

}



const int16_t UserInterface::Widget::LoadingIcon::height() const {

    if (m_centerWidget && m_rotateWidget) {

        return qMax(m_centerWidget->height(), m_rotateWidget->height());

    }

    return 0;

}



const int16_t UserInterface::Widget::LoadingIcon::x() const {

    if (m_centerWidget && m_rotateWidget) {

        return qMin(m_centerWidget->height(), m_rotateWidget->height());

    }
    return 0;

}



const int16_t UserInterface::Widget::LoadingIcon::y() const {

    if (m_centerWidget && m_rotateWidget) {

        return qMin(m_centerWidget->height(), m_rotateWidget->height());

    }
    return 0;

}



void UserInterface::Widget::LoadingIcon::onAnimUpdate(const QVariant& value) {

    QTransform t;
    // save the current value to be used for scaling in case it is needed
    m_currentRotation = value.toReal();
    t.rotate(m_currentRotation);
    m_rotateWidget->setPixmap(m_rotatePixmap.transformed(t), false);

}