#include "multiplayer_session/other/RetirementIcon.h"

#include <QGridLayout>
#include <QPixmap>
#include <QWidget>
#include "PixmapFactory.h"
#include "base/TextInterface.h"
#include "data/internal/Participant.h"
#include "multiplayer_session/other/RetirementIconBackground.h"



UserInterface::Widget::RetirementIcon::RetirementIcon(QWidget* parent) : 
    QWidget(parent),
    m_text(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::RetirementIcon, this)),
    m_background(new UserInterface::Widget::RetirementIconBackground(this)) {

    QGridLayout* layout = new QGridLayout(this);

    if (m_text) {

		m_text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_text->setFontThickness(UserInterface::Widget::FontThickness::Bold);
        m_text->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    }

    if (m_background) {

        m_background->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    }

    if (layout) {

        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        layout->addWidget(m_background, 0, 0, 1, 2, Qt::AlignCenter);
		layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 0, 1, 1);
        layout->addWidget(m_text, 0, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
        layout->setColumnStretch(0, 4);
		layout->setColumnMinimumWidth(0, 24);
        layout->setColumnStretch(1, 79);

	}

    setLayout(layout);
}




void UserInterface::Widget::RetirementIcon::activate(const Participant::Internal::Status status) {

    switch (status) {

        case Participant::Internal::Status::Active:
            hide();
            break;

        case Participant::Internal::Status::DNF:
            show();
            m_text->setText("DID NOT FINISH");
            break;

        case Participant::Internal::Status::DSQ:
            show();
            m_text->setText("DISQUALIFIED");
            break;

        default:
            // DO NOTHING
            break;

    }

}