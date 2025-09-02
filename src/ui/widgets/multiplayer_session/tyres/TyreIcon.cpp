#include "multiplayer_session/tyres/TyreIcon.h"

#include <QWidget>
#include "Image.h"
#include "PixmapFactory.h"
#include "base/ID.h"
#include "base/ImageInterface.h"



UserInterface::Widget::TyreIcon::TyreIcon(UserInterface::Widget::ID id, QWidget* parent) :
    UserInterface::Widget::ImageInterface(id, parent),
    m_isTypeSet(false) {

}



void UserInterface::Widget::TyreIcon::SetType(Tyre::Internal::Visual type) {

    if (!m_isTypeSet) {

        UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
        Q_ASSERT(instance);
        if (instance) {

            bool res = false;

            switch (type) {

                case Tyre::Internal::Visual::Soft:
                    res = instance->fetchPixmap(UserInterface::Widget::StandardImage::SoftTyres, m_pixmap);
                    break;

                case Tyre::Internal::Visual::Medium:
                    res = instance->fetchPixmap(UserInterface::Widget::StandardImage::MediumTyres, m_pixmap);
                    break;

                case Tyre::Internal::Visual::Hard:
                    res = instance->fetchPixmap(UserInterface::Widget::StandardImage::HardTyres, m_pixmap);
                    break;

                case Tyre::Internal::Visual::Intermediate:
                    res = instance->fetchPixmap(UserInterface::Widget::StandardImage::IntermediateTyres, m_pixmap);
                    break;

                case Tyre::Internal::Visual::ExtremeWet:
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