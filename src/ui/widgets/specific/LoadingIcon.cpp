#include "LoadingIcon.h"

#include <QPropertyAnimation>
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QWidget>
#include "Image.h"
#include "PixmapFactory.h"
#include <QWidget>



UserInterface::Widget::LoadingIcon::LoadingIcon(QWidget* parent) :
    QWidget(parent),
    m_centerWidget(new QLabel(this)),
    m_rotateWidget(new QLabel(this)),
    m_centerPixmap(),
    m_rotatePixmap(),
    m_currentRotation(0.0f),
    m_anim(new QPropertyAnimation) {

    if (m_centerWidget && m_rotateWidget) {

        UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
        Q_ASSERT(instance);
        if (instance) {

            bool res = instance->fetchPixmap(UserInterface::Widget::StandardImage::LoadingLogoCenter, m_centerPixmap);
            m_centerWidget->setPixmap(m_centerPixmap);
            res &= instance->fetchPixmap(UserInterface::Widget::StandardImage::LoadingLogoRotatingPart, m_rotatePixmap);
            m_rotateWidget->setPixmap(m_rotatePixmap);

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

}



void UserInterface::Widget::LoadingIcon::onAnimUpdate(const QVariant& value) {

    QTransform t;
    // save the current value to be used for scaling in case it is needed
    m_currentRotation = value.toReal();
    t.rotate(m_currentRotation);
    m_rotateWidget->setPixmap(m_rotatePixmap.transformed(t));

}