#include "multiplayer_session/other/RetirementIcon.h"

#include <QHBoxLayout>
#include <QPixmap>
#include "PixmapFactory.h"
#include "base/TextInterface.h"
#include "data/internal/Participant.h"
#include "multiplayer_session/other/RetirementIconBackground.h"



UserInterface::Widget::RetirementIcon::RetirementIcon(QWidget* parent) : 
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::RetirementIcon, parent),
    m_text(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::RetirementIcon, this)) {

    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance &&
        instance->fetchPixmap(UserInterface::Widget::StandardImage::RetirementBox, m_pixmap)) {

        setPixmap(m_pixmap, true);

    }

	QHBoxLayout* layout = new QHBoxLayout(this);

    if (m_text) {

		m_text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_text->setFontThickness(UserInterface::Widget::FontThickness::Bold);
        m_text->setAlignment(Qt::AlignCenter);

    }

    if (layout) {

        layout->setContentsMargins(HORIZONTAL_OFFSET, VERTICAL_OFFSET, 0, VERTICAL_OFFSET);
        layout->setSpacing(0);
        layout->addWidget(m_text);
	}

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