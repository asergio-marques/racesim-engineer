#include "multiplayer_session/penalty/PenaltyIcon.h"
#include "base/TextInterface.h"
#include "multiplayer_session/penalty/PenaltyFlag.h"
#include "multiplayer_session/penalty/PenaltyTextBackground.h"



UserInterface::Widget::PenaltyIcon::PenaltyIcon(QWidget* parent) : 
    UserInterface::Widget::Container(UserInterface::Widget::ID::PenaltyIcon),
    m_flagIcon(nullptr),
    m_textBackground(nullptr),
    m_text(nullptr),
    m_active(false),
    m_timePen(0),
    m_driveThroughs(0),
    m_stopGos(0) {

}



void UserInterface::Widget::PenaltyIcon::addTimePenalty(const int32_t change) {

    m_timePen += change;
    checkDisplayStatus();

}



void UserInterface::Widget::PenaltyIcon::addDriveThrough(const int32_t change) {

    m_driveThroughs += change;
    checkDisplayStatus();

}



void UserInterface::Widget::PenaltyIcon::addStopGo(const int32_t change) {

    m_stopGos += change;
    checkDisplayStatus();

}



void UserInterface::Widget::PenaltyIcon::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    if (m_flagIcon && m_textBackground && m_text) {

        m_flagIcon->move(x, y, centerAlignmentX, centerAlignmentY);

        const uint8_t baseX = m_flagIcon->x() + (m_flagIcon->width() / 2);
        const uint8_t baseY = m_flagIcon->y() + (m_flagIcon->height() / 2);

        m_text->move(baseX, baseY, true, true);

        if (m_text->getTextWidth() > 0) {

            m_textBackground->resize(m_text->getTextWidth() + (HORIZONTAL_OFFSET * 2),
                m_text->getTextHeight() + (VERTICAL_OFFSET * 2));
            m_textBackground->move(baseX, baseY, true, true);

        }
    
    }

}


void UserInterface::Widget::PenaltyIcon::scale(const uint8_t percent) {

    // TODO

}



void UserInterface::Widget::PenaltyIcon::scale(const uint8_t percentX, const uint8_t percentY) {

    // TODO

}



void UserInterface::Widget::PenaltyIcon::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    // TODO

}



const int16_t UserInterface::Widget::PenaltyIcon::width() const {

    if (m_flagIcon) return m_flagIcon->width();
    else return 0;

}



const int16_t UserInterface::Widget::PenaltyIcon::height() const {

    if (m_flagIcon) return m_flagIcon->height();
    else return 0;

}



const int16_t UserInterface::Widget::PenaltyIcon::x() const {

    if (m_flagIcon) return m_flagIcon->x();
    else return 0;

}



const int16_t UserInterface::Widget::PenaltyIcon::y() const {

    if (m_flagIcon) return m_flagIcon->y();
    else return 0;

}



void UserInterface::Widget::PenaltyIcon::checkDisplayStatus() {

    const bool previousActiveStatus = m_active;
    m_active = true;

    if (m_flagIcon && m_textBackground && m_text) {

        // If deactivated now, reset status to default
        if (!m_active && previousActiveStatus) {

            m_text->hide();
            m_textBackground->hide();
            m_flagIcon->hide();

        }
        // If activated now, or if just values updated, set text, resize the background, and display
        else if (m_active) {

            const uint8_t baseX = m_flagIcon->x() + (m_flagIcon->width() / 2);
            const uint8_t baseY = m_flagIcon->y() + (m_flagIcon->height() / 2);

            m_text->setText(generateText());
            m_text->show();
            m_text->move(baseX, baseY, true, true);

            m_flagIcon->show();

            m_textBackground->show();
            m_textBackground->resize(m_text->getTextWidth() + (HORIZONTAL_OFFSET * 2),
                m_text->getTextHeight() + (VERTICAL_OFFSET * 2));
            m_textBackground->move(baseX, baseY, true, true);
            
            // redo the positioning of the internal widgets, easiest way
            move(x(), y(), false, false);

        }

    }

}



const QString UserInterface::Widget::PenaltyIcon::generateText() {

    QString text = "";

    if (m_stopGos != 0) {

        text += QString::number(m_stopGos) + "SG";

    }
    if (m_driveThroughs != 0) {

        if (!text.isEmpty()) text += "+";
        text += QString::number(m_driveThroughs) + "DT";

    }
    if (m_timePen != 0) {

        if (!text.isEmpty()) text += "+";
        const int32_t fractionPart = m_timePen % 1000;
        if (fractionPart > 0) text += QString::number(m_timePen / 1000) + "." + QString::number(fractionPart);
        else text += QString::number(m_timePen / 1000);

    }

    return text;

}