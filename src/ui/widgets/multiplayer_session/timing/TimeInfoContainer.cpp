#include "multiplayer_session/timing/TimeInfoContainer.h"

#include "base/Container.h"
#include "base/TextInterface.h"
#include "TimeInfoContainer.h"



UserInterface::Widget::TimeInfoContainer::TimeInfoContainer(const UserInterface::Widget::TimeInfoContainer::Type type, QWidget* parent) : 
    UserInterface::Widget::Container(UserInterface::Widget::ID::InvalidUnknown),
    m_type(UserInterface::Widget::TimeInfoContainer::Type::InvalidUnknown),
    m_label(nullptr),
    m_time(nullptr) {

    m_type = type;

    switch (type) {

        case UserInterface::Widget::TimeInfoContainer::Type::PersonalBestTime:
            m_id = UserInterface::Widget::ID::LapTimeInfo;
            m_label = new UserInterface::Widget::TextInterface(m_id, parent);
            m_label->setText("BEST");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::LastLapTime:
            m_id = UserInterface::Widget::ID::LapTimeInfo;
            m_label = new UserInterface::Widget::TextInterface(m_id, parent);
            m_label->setText("LAST");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::RelativeToFront:
            m_id = UserInterface::Widget::ID::RelativeTimeInfo;
            m_label = new UserInterface::Widget::TextInterface(m_id, parent);
            m_label->setText("GAP");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::RelativeToLeader:
            m_id = UserInterface::Widget::ID::RelativeTimeInfo;
            m_label = new UserInterface::Widget::TextInterface(m_id, parent);
            m_label->setText("INT");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::DeltaRelativeToFront:
            m_id = UserInterface::Widget::ID::GapDeltaInfo;
            m_label = new UserInterface::Widget::TextInterface(m_id, parent);
            m_label->setText("ΔFRT");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::DeltaRelativeToRear:
            m_id = UserInterface::Widget::ID::GapDeltaInfo;
            m_label = new UserInterface::Widget::TextInterface(m_id, parent);
            m_label->setText("ΔBHD");
            break;

        default:
            m_id = UserInterface::Widget::ID::InvalidUnknown;
            m_label = new UserInterface::Widget::TextInterface(m_id, parent);
            m_label->setText("???");
            break;

    }

    m_time = new UserInterface::Widget::TextInterface(m_id, parent);
    m_time->setText("-.---");
    m_time->setAlignment(Qt::AlignRight);

}
