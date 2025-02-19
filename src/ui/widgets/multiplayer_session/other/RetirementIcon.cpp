#include "multiplayer_session/other/RetirementIcon.h"
#include <QWidget>
#include "data/internal/Participant.h"
#include "multiplayer_session/other/RetirementIconBackground.h"
#include "StyleSheetFactory.h"



UserInterface::Widget::RetirementIcon::RetirementIcon(QWidget* parent) : 
    QWidget(parent),
    m_background(new UserInterface::Widget::RetirementIconBackground(this)),
    m_text(new QLabel(this)) {

    if (m_background) {

        m_background->hide();

    }

    if (m_text) {

        UserInterface::StyleSheetFactory* instance = UserInterface::StyleSheetFactory::instance();
        Q_ASSERT(instance);
        if (instance) {

            m_text->setStyleSheet(instance->requestByColorAndThickness(UserInterface::StyleSheetFactory::FontThickness::Bold));

        }

        m_text->hide();
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



void UserInterface::Widget::RetirementIcon::setTextFontSize(const uint16_t size) {

    if (m_text && m_background) {

        uint16_t newY = m_background->y() + (m_background->height() / 2);
        //m_text->setFontSize(size);
        
        QFont font = m_text->font();
        font.setPointSize(size);
        m_text->setFont(font);
        m_text->move(m_text->x(), newY);

    }

}