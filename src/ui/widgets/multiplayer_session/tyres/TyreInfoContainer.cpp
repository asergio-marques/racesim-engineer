#include "multiplayer_session/tyres/TyreInfoContainer.h"

#include <QString>
#include "base/Container.h"
#include "base/TextInterface.h"
#include "multiplayer_session/tyres/TyreIcon.h"



UserInterface::Widget::TyreInfoContainer::TyreInfoContainer(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::TyreInfo),
    m_visualCompoundIcon(nullptr),
    m_actualCompoundText(nullptr),
    m_lapsText(nullptr),
    m_numLaps(0) {

    m_visualCompoundIcon = new UserInterface::Widget::TyreIcon(m_id, parent);
    Q_ASSERT(m_visualCompoundIcon);
    if (m_visualCompoundIcon) {

        m_visualCompoundIcon->hide();

    }
    m_actualCompoundText = new UserInterface::Widget::TextInterface(m_id, parent);
    Q_ASSERT(m_actualCompoundText);
    if (m_actualCompoundText) {

        m_actualCompoundText->setAlignment(Qt::AlignCenter);
        m_actualCompoundText->hide();
        m_actualCompoundText->setText("?");

    }
    m_lapsText = new UserInterface::Widget::TextInterface(m_id, parent);
    Q_ASSERT(m_lapsText);
    if (m_lapsText) {

        m_lapsText->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_lapsText->hide();
        m_lapsText->setText(QString::number(m_numLaps));

    }

}



void UserInterface::Widget::TyreInfoContainer::Init(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t numLapsAtStart) {

    if (m_actualCompoundText) {

        switch (actualTyreCompound) {

            case Tyre::Internal::Actual::F1_C6:
                m_actualCompoundText->setText("C6");
                break;
            case Tyre::Internal::Actual::F1_C5:
                m_actualCompoundText->setText("C5");
                break;
            case Tyre::Internal::Actual::F1_C4:
                m_actualCompoundText->setText("C4");
                break;
            case Tyre::Internal::Actual::F1_C3:
                m_actualCompoundText->setText("C3");
                break;
            case Tyre::Internal::Actual::F1_C2:
                m_actualCompoundText->setText("C2");
                break;
            case Tyre::Internal::Actual::F1_C1:
                m_actualCompoundText->setText("C1");
                break;
            case Tyre::Internal::Actual::F1_C0:
                m_actualCompoundText->setText("C0");
                break;
            case Tyre::Internal::Actual::F1_Intermediate:
            case Tyre::Internal::Actual::F2_Intermediate:
                m_actualCompoundText->setText("I");
                break;
            case Tyre::Internal::Actual::F1_ExtremeWet:
            case Tyre::Internal::Actual::F2_ExtremeWet:
                m_actualCompoundText->setText("W");
                break;
            case Tyre::Internal::Actual::F2_HyperSoft:
                m_actualCompoundText->setText("HS");
                break;
            case Tyre::Internal::Actual::F2_SuperSoft:
                m_actualCompoundText->setText("SS");
                break;
            case Tyre::Internal::Actual::F2_Soft:
                m_actualCompoundText->setText("S");
                break;
            case Tyre::Internal::Actual::F2_Medium:
                m_actualCompoundText->setText("M");
                break;
            case Tyre::Internal::Actual::F2_Hard:
                m_actualCompoundText->setText("H");
                break;
            default:
                m_actualCompoundText->setText("?");

        }

    }

    if (m_visualCompoundIcon) {

        m_visualCompoundIcon->SetType(visualTyreCompound);
        m_visualCompoundIcon->show();
         
    }

    m_numLaps = numLapsAtStart;

    if (m_lapsText) {

        m_lapsText->setText(QString::number(m_numLaps));

    }

}


void UserInterface::Widget::TyreInfoContainer::IncrementLap() {

    ++m_numLaps;
    if (m_lapsText) {

        m_lapsText->setText(QString::number(m_numLaps));

    }

}


void UserInterface::Widget::TyreInfoContainer::scale(const uint8_t percentX, const uint8_t percentY) {

}



void UserInterface::Widget::TyreInfoContainer::scale(const uint8_t percent) {

}



void UserInterface::Widget::TyreInfoContainer::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

}



void UserInterface::Widget::TyreInfoContainer::raise(void) {

}



void UserInterface::Widget::TyreInfoContainer::lower(void) {

}



void UserInterface::Widget::TyreInfoContainer::setTextFontSize(const uint16_t size) {

}



const int16_t UserInterface::Widget::TyreInfoContainer::width(void) const {

    return 0;

}



const int16_t UserInterface::Widget::TyreInfoContainer::height(void) const {

    return 0;

}



const int16_t UserInterface::Widget::TyreInfoContainer::x(void) const {

    return 0;

}



const int16_t UserInterface::Widget::TyreInfoContainer::y(void) const {

    return 0;

}



void UserInterface::Widget::TyreInfoContainer::move(const uint16_t x, const uint16_t y, const bool centerX, const bool centerY) {

}
