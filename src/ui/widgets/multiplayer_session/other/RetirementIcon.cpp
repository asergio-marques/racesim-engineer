#include "multiplayer_session/other/RetirementIcon.h"
#include <QWidget>
#include "data/internal/Participant.h"
#include "multiplayer_session/other/RetirementIconBackground.h"



UserInterface::Widget::RetirementIcon::RetirementIcon(QWidget* parent) : 
    UserInterface::Widget::Container(UserInterface::Widget::ID::RetirementIcon),
    m_background(new UserInterface::Widget::RetirementIconBackground(parent)),
    m_text(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::RetirementIcon, parent)) {

    if (m_background) {

        m_background->hide();

    }

    if (m_text) {

        m_text->hide();
        m_text->setFontThickness(UserInterface::Widget::FontThickness::Bold);
        m_text->setAlignment(Qt::AlignCenter);

    }

}




void UserInterface::Widget::RetirementIcon::activate(const Participant::Internal::Status status) {

    switch (status) {

        case Participant::Internal::Status::Active:
            m_background->hide();
            m_text->hide();
            break;

        case Participant::Internal::Status::DNF:
            m_background->show();
            m_text->setText("DID NOT FINISH");
            m_text->show();
            break;

        case Participant::Internal::Status::DSQ:
            m_background->show();
            m_text->setText("DISQUALIFIED");
            m_text->show();
            break;

        default:
            // DO NOTHING
            break;

    }

}



void UserInterface::Widget::RetirementIcon::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    if (m_background && m_text) {

        m_background->move(x, y, centerAlignmentX, centerAlignmentY);

        const uint16_t baseY = m_background->y() + (m_background->height() / 2);
        m_text->move(this->x() + HORIZONTAL_OFFSET, baseY, false, true);
    
    }

}


void UserInterface::Widget::RetirementIcon::scale(const uint8_t percent) {

    // TODO

}



void UserInterface::Widget::RetirementIcon::scale(const uint8_t percentX, const uint8_t percentY) {

    // TODO

}



void UserInterface::Widget::RetirementIcon::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    if (m_text && m_background) {

        m_background->setSize(newWidth, newHeight, keepAspectRatio);
        if (m_text->getTextHeight() >= (newHeight - (VERTICAL_OFFSET * 2))) {

            m_text->setFontSize(m_text->font().pointSize() - 4);
            m_text->adjustSize();

        }

    }

}



void UserInterface::Widget::RetirementIcon::raise() {
    
    if (m_background) {
        m_background->raise();
    }
    if (m_text) {
        m_text->raise();
    }

}



void UserInterface::Widget::RetirementIcon::lower() {

    if (m_text) {
        m_text->lower();
    }
    if (m_background) {
        m_background->lower();
    }

}



void UserInterface::Widget::RetirementIcon::setTextFontSize(const uint16_t size) {

    if (m_text && m_background) {

        uint16_t newY = m_background->y() + (m_background->height() / 2);
        m_text->setFontSize(size);
        m_text->move(m_text->x(), newY, false, true);

    }

}



void UserInterface::Widget::RetirementIcon::adjustSize() {

    if (m_background) {

        m_background->adjustSize();

    }
    if (m_text) {

        m_text->adjustSize();

    }

}



const int16_t UserInterface::Widget::RetirementIcon::width() const {

    if (m_background) return m_background->width();
    else return 0;

}



const int16_t UserInterface::Widget::RetirementIcon::height() const {

    if (m_background) return m_background->height();
    else return 0;

}



const int16_t UserInterface::Widget::RetirementIcon::x() const {

    if (m_background) return m_background->x();
    else return 0;

}



const int16_t UserInterface::Widget::RetirementIcon::y() const {

    if (m_background) return m_background->y();
    else return 0;

}