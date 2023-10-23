#include "widgets/LoadingIcon.h"

#include <QPropertyAnimation>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include "base/elements/ImageElement.h"
#include "base/WidgetId.h"



UserInterface::Widget::LoadingIcon::LoadingIcon(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::ImageElement(id, parent),
    m_rotateImage(new QLabel(parent)), 
    m_rotatePixmap(),
    m_centerPixmap(),
    m_anim(new QPropertyAnimation) {

    if (m_image && m_rotateImage && m_anim) {

        m_rotateImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        bool res = m_centerPixmap.load(":img/icons/logo_loading_center.png");
        res &= m_rotatePixmap.load(":img/icons/logo_loading_rotate.png");
        if (res) {

            m_anim->setTargetObject(m_rotateImage);
            m_anim->setDuration(4000);
            m_anim->setStartValue(0.0f);
            m_anim->setEndValue(360.0f);
            m_anim->setLoopCount(-1);
            connect(m_anim, &QVariantAnimation::valueChanged, this, &UserInterface::Widget::LoadingIcon::onAnimUpdate);

            m_image->setPixmap(m_centerPixmap);
            m_rotateImage->setPixmap(m_rotatePixmap);

            m_anim->start();

        }

    }

}



bool UserInterface::Widget::LoadingIcon::Update() {

    // Never updated?
    return false;

}

void UserInterface::Widget::LoadingIcon::Move(int16_t x, int16_t y) {

    if (m_image && m_rotateImage) {

        int16_t centerDx = (m_rotateImage->width() - m_image->width()) / 2;
        int16_t centerDy = (m_rotateImage->height() - m_image->height()) / 2;

        // TODO figure out a way to solve the startup issue here, the result of the above operations is 0
        // this fixes the issue temporarily, but everything is screwed up if scaling has been performed
        if (centerDx == 0) centerDx = 32;
        if (centerDy == 0) centerDy = 32;

        m_rotateImage->move(x, y);
        m_image->move(x + centerDx, y + centerDy);

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
    t.rotate(value.toReal());
    m_rotateImage->setPixmap(m_rotatePixmap.transformed(t));

}