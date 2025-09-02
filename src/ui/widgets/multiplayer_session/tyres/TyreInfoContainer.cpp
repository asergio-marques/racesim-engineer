#include "multiplayer_session/tyres/TyreInfoContainer.h"

#include <cstdint>
#include <QString>
#include <QGridLayout>
#include <QWidget>
#include "base/Container.h"
#include "base/TextInterface.h"
#include "multiplayer_session/tyres/TyreIcon.h"
#include "styles/Standings.h"




UserInterface::Widget::TyreInfoContainer::TyreInfoContainer(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::TyreInfo),
    m_visualCompoundIcon(nullptr),
    m_actualCompoundText(nullptr),
    m_lapsText(nullptr),
    m_numLaps(0),
    m_redone(false) {

    UserInterface::Style::Standings style;

    m_visualCompoundIcon = new UserInterface::Widget::TyreIcon(UserInterface::Widget::ID::TyreInfo, parent);
    Q_ASSERT(m_visualCompoundIcon);
    if (m_visualCompoundIcon) {

        m_visualCompoundIcon->setSize(style.TyreInfoTyreIconMaxXY.m_value,
            style.TyreInfoTyreIconMaxXY.m_value, true);
        m_visualCompoundIcon->setScaledContents(true);
        m_visualCompoundIcon->setKeepAspectRatio(true);
        m_visualCompoundIcon->hide();

    }
    m_actualCompoundText = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::TyreInfo, parent);
    Q_ASSERT(m_actualCompoundText);
    if (m_actualCompoundText) {

        m_actualCompoundText->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_actualCompoundText->setFontSize(style.TyreInfoTyreCompoundTextSize.m_value);
        m_actualCompoundText->setText("?");
        m_actualCompoundText->setScaledContents(true);
        m_actualCompoundText->hide();

    }
    m_lapsText = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::TyreInfo, parent);
    Q_ASSERT(m_lapsText);
    if (m_lapsText) {

        m_actualCompoundText->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_lapsText->setFontSize(style.TyreInfoTyreAgeTextSize.m_value);
        m_lapsText->setText(QString::number(m_numLaps));
        m_lapsText->setScaledContents(true);
        m_lapsText->hide();

    }

}



void UserInterface::Widget::TyreInfoContainer::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    if (m_visualCompoundIcon && m_actualCompoundText && m_lapsText) {

        UserInterface::Style::Standings style;

		m_visualCompoundIcon->move(x, y, centerAlignmentX, centerAlignmentY);

        // center compound text in relation to the compound icon
        const uint16_t baseXCompound = m_visualCompoundIcon->x() + (m_visualCompoundIcon->width() / 2);
        const uint16_t baseY = m_visualCompoundIcon->y() + (m_visualCompoundIcon->height() / 2);
		m_actualCompoundText->move(baseXCompound, baseY, true, true);

		// age text is centered vertically to the icon, and placed to the right of it with a small gap
        const uint16_t baseXAge = m_visualCompoundIcon->x() + m_visualCompoundIcon->width() +
            UserInterface::Style::Standings::TyreInfoIconAgeTextGap.m_value;
        m_lapsText->move(baseXAge, baseY, false, true);

    }

}



void UserInterface::Widget::TyreInfoContainer::scale(const uint8_t percent) {

    // TODO

}



void UserInterface::Widget::TyreInfoContainer::scale(const uint8_t percentX, const uint8_t percentY) {

    // TODO

}



void UserInterface::Widget::TyreInfoContainer::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    // TODO ignoring parameters for the time being, I just want this base working...
    if (m_visualCompoundIcon && m_actualCompoundText && m_lapsText) {

        UserInterface::Style::Standings style;

        m_visualCompoundIcon->setSize(style.TyreInfoTyreIconMaxXY.m_value,
			style.TyreInfoTyreIconMaxXY.m_value, true);
        m_visualCompoundIcon->adjustSize();

        m_actualCompoundText->setFontSize(style.TyreInfoTyreCompoundTextSize.m_value);
        m_actualCompoundText->adjustSize();

        m_lapsText->setFontSize(style.TyreInfoTyreAgeTextSize.m_value);
		m_lapsText->adjustSize();

    }

}



void UserInterface::Widget::TyreInfoContainer::raise() {

    // TODO

}



void UserInterface::Widget::TyreInfoContainer::lower() {

    // TODO

}



const int16_t UserInterface::Widget::TyreInfoContainer::width() const {

    if (!m_visualCompoundIcon || !m_actualCompoundText || !m_lapsText) {
        return 0;
    }

	// awful, also ignore the actual compound text since it's "inside" the visual icon
    int16_t xMin = INT16_MAX;
    int16_t xMax = INT16_MIN;
    int16_t lastWidth = INT16_MIN;
    if (m_visualCompoundIcon) {
        xMin = qMin(xMin, m_visualCompoundIcon->x());
        xMax = qMax(xMax, m_visualCompoundIcon->x());
        if (xMax == m_visualCompoundIcon->x()) {
            lastWidth = m_visualCompoundIcon->width();
        }
    }

    if (m_lapsText) {
        xMin = qMin(xMin, m_lapsText->x());
        xMax = qMax(xMax, m_lapsText->x());
        if (xMax == m_lapsText->x()) {
            lastWidth = m_lapsText->width();
        }
    }

    return xMax - xMin + lastWidth;

}



const int16_t UserInterface::Widget::TyreInfoContainer::height() const {

    if (!m_visualCompoundIcon || !m_actualCompoundText || !m_lapsText) {
        return 0;
    }

    // awful, also ignore the actual compound text since it's "inside" the visual icon
    int16_t yMin = INT16_MAX;
    int16_t yMax = INT16_MIN;
    int16_t lastHeight = INT16_MIN;
    if (m_visualCompoundIcon) {
        yMin = qMin(yMin, m_visualCompoundIcon->y());
        yMax = qMax(yMax, m_visualCompoundIcon->y());
        if (yMax == m_visualCompoundIcon->y()) {
            lastHeight = m_visualCompoundIcon->height();
        }
    }

    if (m_lapsText) {
        yMin = qMin(yMin, m_lapsText->y());
        yMax = qMax(yMax, m_lapsText->y());
        if (yMax == m_lapsText->y()) {
            lastHeight = m_lapsText->height();
        }
    }

    return yMax - yMin + lastHeight;

}



const int16_t UserInterface::Widget::TyreInfoContainer::x() const {

    if (!m_visualCompoundIcon || !m_actualCompoundText || !m_lapsText) {
        return 0;
    }
    // this is always meant to be the left-most widget
	return m_actualCompoundText->x();

}



const int16_t UserInterface::Widget::TyreInfoContainer::y() const {

    if (!m_visualCompoundIcon || !m_actualCompoundText || !m_lapsText) {
        return 0;
    }
    // this is always meant to be the top-most widget
    return m_actualCompoundText->y();

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

}


void UserInterface::Widget::TyreInfoContainer::IncrementLap() {

    ++m_numLaps;
    if (m_lapsText) {

        m_lapsText->setText(QString::number(m_numLaps));

    }

}




void UserInterface::Widget::TyreInfoContainer::Show() {

    if (m_visualCompoundIcon && m_actualCompoundText && m_lapsText) {

        m_visualCompoundIcon->setVisible(true);
        m_visualCompoundIcon->raise();

        m_actualCompoundText->setVisible(true);
        m_actualCompoundText->raise();

        m_lapsText->setVisible(true);
        m_lapsText->raise();

    }

}




void UserInterface::Widget::TyreInfoContainer::Hide() {

    if (m_visualCompoundIcon && m_actualCompoundText && m_lapsText) {

        m_visualCompoundIcon->setVisible(false);
        m_visualCompoundIcon->lower();

        m_actualCompoundText->setVisible(false);
        m_actualCompoundText->lower();

        m_lapsText->setVisible(false);
        m_lapsText->lower();


    }

}



void UserInterface::Widget::TyreInfoContainer::RedoneOnce() {

    m_redone = true;

}



bool UserInterface::Widget::TyreInfoContainer::HasBeenRedoneAtLeastOnce() const {

    return m_redone;

}