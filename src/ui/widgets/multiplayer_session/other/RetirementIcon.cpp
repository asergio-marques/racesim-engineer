#include "multiplayer_session/other/RetirementIcon.h"

#include "base/TextInterface.h"
#include "data/internal/Participant.h"
#include "multiplayer_session/other/RetirementIconBackground.h"



UserInterface::Widget::RetirementIcon::RetirementIcon(QWidget* parent) : 
    QWidget(parent),
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