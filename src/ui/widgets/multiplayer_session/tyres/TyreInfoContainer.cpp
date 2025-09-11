#include "multiplayer_session/tyres/TyreInfoContainer.h"

#include <cstdint>
#include <QString>
#include <QGridLayout>
#include <QWidget>
#include "base/Container.h"
#include "base/TextInterface.h"
#include "styles/DriverInfo.h"
#include "multiplayer_session/tyres/TyreIcon.h"




UserInterface::Widget::TyreInfoContainer::TyreInfoContainer(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::TyreInfo),
    m_visualCompoundIcon(nullptr),
    m_actualCompoundText(nullptr),
    m_lapsText(nullptr),
    m_numLaps(0),
    m_stintNo(0) {

    m_visualCompoundIcon = new UserInterface::Widget::TyreIcon(UserInterface::Widget::ID::TyreInfo, parent);
    Q_ASSERT(m_visualCompoundIcon);
    if (m_visualCompoundIcon) {
        m_visualCompoundIcon->setScaledContents(true);
        m_visualCompoundIcon->setKeepAspectRatio(true);
        m_visualCompoundIcon->hide();

    }
    m_actualCompoundText = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::TyreInfo, parent);
    Q_ASSERT(m_actualCompoundText);
    if (m_actualCompoundText) {

        m_actualCompoundText->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_actualCompoundText->setText("?");
        m_actualCompoundText->hide();

    }
    m_lapsText = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::TyreInfo, parent);
    Q_ASSERT(m_lapsText);
    if (m_lapsText) {

        m_lapsText->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_lapsText->setText(QString::number(m_numLaps));
        m_lapsText->hide();

    }
    m_stintNoText = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::TyreInfo, parent);
    Q_ASSERT(m_stintNoText);
    if (m_stintNoText) {

        m_stintNoText->setFontThickness(UserInterface::Widget::FontThickness::Bold);
        m_stintNoText->setText(QString::number(m_stintNo));
        m_stintNoText->hide();

    }

}



void UserInterface::Widget::TyreInfoContainer::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    m_x = x;
    m_y = y;

    redoLayout();

}



void UserInterface::Widget::TyreInfoContainer::scale(const uint8_t percent) {

    // TODO

}



void UserInterface::Widget::TyreInfoContainer::scale(const uint8_t percentX, const uint8_t percentY) {

    // TODO

}



void UserInterface::Widget::TyreInfoContainer::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    m_width = newWidth;
    m_height = newHeight;

    redoLayout();

}



void UserInterface::Widget::TyreInfoContainer::raise() {

    // TODO

}



void UserInterface::Widget::TyreInfoContainer::lower() {

    // TODO

}



const int16_t UserInterface::Widget::TyreInfoContainer::width() const {

    return m_width;

}



const int16_t UserInterface::Widget::TyreInfoContainer::height() const {

    return m_height;

}



const int16_t UserInterface::Widget::TyreInfoContainer::x() const {

    return m_x;

}



const int16_t UserInterface::Widget::TyreInfoContainer::y() const {

    return m_y;

}



void UserInterface::Widget::TyreInfoContainer::Init(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t numLapsAtStart, uint8_t stintNo) {

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

        m_actualCompoundText->show();

    }

    if (m_visualCompoundIcon) {

        m_visualCompoundIcon->SetType(visualTyreCompound);
        m_visualCompoundIcon->show();

    }

    m_numLaps = numLapsAtStart;

    if (m_lapsText) {

        m_lapsText->setText(QString::number(m_numLaps));
        m_lapsText->show();

    }

    m_stintNo = stintNo;

    if (m_stintNoText) {

        m_stintNoText->setText(QString::number(m_stintNo));
        m_stintNoText->show();

    }
    
    redoLayout();

}


void UserInterface::Widget::TyreInfoContainer::IncrementLap() {

    ++m_numLaps;
    if (m_lapsText) {

        m_lapsText->setText(QString::number(m_numLaps));

    }

    redoLayout();

}




void UserInterface::Widget::TyreInfoContainer::Show() {

    if (m_visualCompoundIcon && m_actualCompoundText && m_lapsText) {

        m_visualCompoundIcon->setVisible(true);
        m_visualCompoundIcon->raise();

        m_actualCompoundText->setVisible(true);
        m_actualCompoundText->raise();

        m_lapsText->setVisible(true);
        m_lapsText->raise();

        m_stintNoText->setVisible(true);
        m_stintNoText->raise();

    }

    redoLayout();

}




void UserInterface::Widget::TyreInfoContainer::Hide() {

    if (m_visualCompoundIcon && m_actualCompoundText && m_lapsText) {

        m_visualCompoundIcon->setVisible(false);
        m_visualCompoundIcon->lower();

        m_actualCompoundText->setVisible(false);
        m_actualCompoundText->lower();

        m_lapsText->setVisible(false);
        m_lapsText->lower();

        m_stintNoText->setVisible(false);
        m_stintNoText->lower();

    }

}


void UserInterface::Widget::TyreInfoContainer::redoLayout() {

    if (m_visualCompoundIcon && m_actualCompoundText && m_lapsText && m_stintNoText) {

        const uint16_t iconSize = UserInterface::Style::TyreInfoCompoundIconSize.GetValue(height());

        m_visualCompoundIcon->setSize(iconSize, iconSize, true);
        m_visualCompoundIcon->adjustSize();

        m_actualCompoundText->setFontSize(UserInterface::Style::TyreInfoCompoundFontSize.GetValue(height()));
        m_actualCompoundText->adjustSize();

        m_lapsText->setFontSize(UserInterface::Style::TyreInfoAgeFontSize.GetValue(height()));
        m_lapsText->adjustSize();

        m_stintNoText->setFontSize(UserInterface::Style::TyreInfoStintNoFontSize.GetValue(height()));
        m_stintNoText->adjustSize();

        m_visualCompoundIcon->move(x(), y(), false, false);

        // center compound text in relation to the compound icon
        const uint16_t baseXCompound = m_visualCompoundIcon->x() + (m_visualCompoundIcon->width() / 2);
        const uint16_t baseY = m_visualCompoundIcon->y() + (m_visualCompoundIcon->height() / 2);
        m_actualCompoundText->move(baseXCompound, baseY, true, true);

        // try to place stint number more or less in the hole
        QFontMetrics fmstint(m_stintNoText->font());
        const uint16_t stintNoY = y() + height() - UserInterface::Style::TyreInfoStintNoGapFromBottom.GetValue(height()) - fmstint.height();
        const uint16_t baseXStint = x() + (0.85f * m_visualCompoundIcon->width());
        m_stintNoText->move(baseXStint, stintNoY, true, false);

        // age text is centered vertically to the icon, and placed to the right of it with a small gap
        QFontMetrics fmlaps(m_lapsText->font());
        const uint16_t baseXAge = x() + width() - fmlaps.horizontalAdvance(m_lapsText->text());
        m_lapsText->move(baseXAge, baseY, false, true);

    }

}