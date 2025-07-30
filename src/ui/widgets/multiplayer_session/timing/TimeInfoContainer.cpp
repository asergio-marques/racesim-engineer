#include "multiplayer_session/timing/TimeInfoContainer.h"

#include <QWidget>
#include <QGridLayout>
#include "base/Container.h"
#include "base/ImageInterface.h"
#include "base/TextInterface.h"
#include "styles/Standings.h"



UserInterface::Widget::TimeInfoContainer::TimeInfoContainer(const UserInterface::Widget::TimeInfoContainer::Type type, QWidget* parent) : 
    QWidget(parent),
    m_type(UserInterface::Widget::TimeInfoContainer::Type::InvalidUnknown),
    m_label(nullptr),
    m_time(nullptr),
    m_layout(nullptr) {

	m_layout = new QGridLayout(this);
	Q_ASSERT(m_layout);
    m_type = type;

    switch (type) {

        case UserInterface::Widget::TimeInfoContainer::Type::PersonalBestTime:
            m_label = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::LapTimeInfo, parent);
            m_label->setText("BEST");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::LastLapTime:
            m_label = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::LapTimeInfo, parent);
            m_label->setText("LAST");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::RelativeToFront:
            m_label = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::RelativeTimeInfo, parent);
            m_label->setText("GAP");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::RelativeToLeader:
            m_label = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::RelativeTimeInfo, parent);
            m_label->setText("INT");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::DeltaRelativeToFront:
            m_label = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::GapDeltaInfo, parent);
            m_label->setText("ΔFRT");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::DeltaRelativeToRear:
            m_label = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::GapDeltaInfo, parent);
            m_label->setText("ΔBHD");
            break;

        default:
            m_label = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::InvalidUnknown, parent);
            m_label->setText("???");

    }
    if (m_label) {

        m_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        m_label->raise();

    }
    m_time = new UserInterface::Widget::TextInterface(m_label->GetId(), parent);
    Q_ASSERT(m_time);
    if (m_time) {

        m_time->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_time->setText("2:02.456");
        m_time->raise();

    }

    if (m_label && m_time && m_layout) {

        UserInterface::Style::Standings style;
        m_label->setFontSize(style.LapInfoIconLabelTextSize.m_value);
        m_time->setFontSize(style.LapInfoIconTimeTextSizeRelative.m_value / 100 * style.LapInfoIconLabelTextSize.m_value);
        m_layout->setContentsMargins(0, 0, 0, 0);
        m_layout->setSpacing(0);
        m_layout->addWidget(m_label, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
        m_layout->addWidget(m_time, 0, 1, 1, 1, Qt::AlignRight | Qt::AlignVCenter);

    }

}



void UserInterface::Widget::TimeInfoContainer::setTextFontSize(const uint16_t size) {

    if (m_label) {

        m_label->setFontSize(size);

    }
    if (m_time) {

        UserInterface::Style::Standings style;
        m_time->setFontSize(size * style.LapInfoIconTimeTextSizeRelative.m_value / 100);

    }


}