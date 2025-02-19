#include "multiplayer_session/warning/WarningIcon.h"

#include <QWidget>
#include "Image.h"
#include "PixmapFactory.h"
#include <QWidget>



UserInterface::Widget::WarningIcon::WarningIcon(QWidget* parent) :
    QLabel(parent),
    m_isTypeSet(false) {

}



void UserInterface::Widget::WarningIcon::SetTrackLimitType() {

    if (!m_isTypeSet) {

        UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
        Q_ASSERT(instance);
        if (instance &&
            instance->fetchPixmap(UserInterface::Widget::StandardImage::TrackLimitWarning, m_pixmap)) {

            setPixmap(m_pixmap);
            m_isTypeSet = true;

        }

    }

}



void UserInterface::Widget::WarningIcon::SetOtherWarningsType() {


    if (!m_isTypeSet) {

        UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
        Q_ASSERT(instance);
        if (instance &&
            instance->fetchPixmap(UserInterface::Widget::StandardImage::OtherWarning, m_pixmap)) {

            setPixmap(m_pixmap);
            m_isTypeSet = true;

        }

    }

}