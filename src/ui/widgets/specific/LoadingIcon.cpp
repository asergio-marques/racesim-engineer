#include "LoadingIcon.h"

#include <QPropertyAnimation>
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QWidget>
#include <QResizeEvent>
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

        m_rotateWidget->setAlignment(Qt::AlignCenter);
        m_centerWidget->setAlignment(Qt::AlignCenter);

        UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
        Q_ASSERT(instance);
        if (instance) {

            bool res = instance->fetchPixmap(UserInterface::Widget::StandardImage::LoadingLogoRotatingPart, m_rotatePixmap);
            m_rotateWidget->setPixmap(m_rotatePixmap);
            m_rotateWidget->resize(m_rotatePixmap.width(), m_rotatePixmap.height());
            resize(m_rotatePixmap.width(), m_rotatePixmap.height());

            res &= instance->fetchPixmap(UserInterface::Widget::StandardImage::LoadingLogoCenter, m_centerPixmap);
            m_centerWidget->setPixmap(m_centerPixmap);
            m_centerWidget->resize(m_centerPixmap.width(), m_centerPixmap.height());

            m_centerWidget->move(m_rotateWidget->x() + (m_rotateWidget->width() / 2), m_rotateWidget->y() + (m_rotateWidget->height() / 2));

            if (res && m_anim) {

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



void UserInterface::Widget::LoadingIcon::resizeEvent(QResizeEvent* event) {

    QWidget::resizeEvent(event);

    // TODO resolve issue in which a lot successive resizings will cause the center pixmap to fade to 0 (prolly due to integer rounding)
    auto newRotDim = qMin(event->size().width(), event->size().height());
    auto oldRotDim = qMin(m_rotateWidget->width(), m_rotateWidget->height());
    auto scalePercent = (newRotDim * 100) / qMin(m_rotateWidget->width(), m_rotateWidget->height());
    auto oldCenterDim = qMin(m_centerWidget->width(), m_centerWidget->height());
    auto newCenterDim = (qMin(m_centerWidget->width(), m_centerWidget->height()) * scalePercent) / 100;

    // reloading the pixmaps prevents compression artifacts from causing the distortion of the image
    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance) {

        if (m_rotateWidget && instance->fetchPixmap(UserInterface::Widget::StandardImage::LoadingLogoRotatingPart, m_rotatePixmap)) {

            // we use the saved rotation value as to avoid some slight visual bugs
            m_rotatePixmap = m_rotatePixmap.scaled(newRotDim, newRotDim, Qt::KeepAspectRatio);
            m_rotatePixmap = m_rotatePixmap.transformed(QTransform().rotate(m_currentRotation));
            m_rotateWidget->setPixmap(m_rotatePixmap);
            m_rotateWidget->resize(newRotDim, newRotDim);

        }

        if (m_centerWidget && instance->fetchPixmap(UserInterface::Widget::StandardImage::LoadingLogoCenter, m_centerPixmap)) {

            m_centerWidget->setPixmap(m_centerPixmap.scaled(newCenterDim, newCenterDim, Qt::KeepAspectRatio));
            m_centerWidget->resize(newCenterDim, newCenterDim);

        }

        if (m_centerWidget && m_rotateWidget) {

            auto newX = m_rotateWidget->x() + (m_rotateWidget->width() / 2) - (m_centerWidget->width() / 2);
            auto newY = m_rotateWidget->y() + (m_rotateWidget->height() / 2) - (m_centerWidget->height() / 2);
            m_centerWidget->move(newX, newY);
            resize(newRotDim, newRotDim);

        }

    }

}