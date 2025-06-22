#include "multiplayer_session/tyres/TyreIcon.h"

#include <QWidget>
#include "Image.h"
#include "PixmapFactory.h"
#include "base/ID.h"
#include "base/ImageInterface.h"



UserInterface::Widget::TyreIcon::TyreIcon(QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::TyreIcon, parent),
    m_isTypeSet(false) {

}



void UserInterface::Widget::TyreIcon::SetType(UserInterface::Widget::TyreIcon::Type type) {

    if (!m_isTypeSet) {

        UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
        Q_ASSERT(instance);
        if (instance) {

            bool res = false;

            switch (type) {

                case UserInterface::Widget::TyreIcon::Type::Soft:
                    res = instance->fetchPixmap(UserInterface::Widget::StandardImage::SoftTyres, m_pixmap);
                    break;

                case UserInterface::Widget::TyreIcon::Type::Medium:
                    res = instance->fetchPixmap(UserInterface::Widget::StandardImage::MediumTyres, m_pixmap);
                    break;

                case UserInterface::Widget::TyreIcon::Type::Hard:
                    res = instance->fetchPixmap(UserInterface::Widget::StandardImage::HardTyres, m_pixmap);
                    break;

                case UserInterface::Widget::TyreIcon::Type::Inter:
                    res = instance->fetchPixmap(UserInterface::Widget::StandardImage::IntermediateTyres, m_pixmap);
                    break;

                case UserInterface::Widget::TyreIcon::Type::Wet:
                    res = instance->fetchPixmap(UserInterface::Widget::StandardImage::WetTyres, m_pixmap);
                    break;

                default:
                    res = instance->fetchPixmap(UserInterface::Widget::StandardImage::UnknownTyres, m_pixmap);

            }

        }

        setPixmap(m_pixmap, true);
        m_isTypeSet = true;

    }

}