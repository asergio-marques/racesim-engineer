#include "multiplayer_session/timing/TimeInfoContainer.h"

#include <QLabel>
#include <QWidget>
#include <QWidget>
#include "styles/Standings.h"



UserInterface::Widget::TimeInfoContainer::TimeInfoContainer(const UserInterface::Widget::TimeInfoContainer::Type type, QWidget* parent) : 
    QWidget(parent),
    m_type(UserInterface::Widget::TimeInfoContainer::Type::InvalidUnknown),
    m_label(nullptr),
    m_time(nullptr),
    m_backgrounds() {

    m_type = type;

    switch (type) {

        case UserInterface::Widget::TimeInfoContainer::Type::PersonalBestTime:
            m_label = new QLabel(this);
            m_label->setText("BEST");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::LastLapTime:
            m_label = new QLabel(this);
            m_label->setText("LAST");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::RelativeToFront:
            m_label = new QLabel(this);
            m_label->setText("GAP");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::RelativeToLeader:
            m_label = new QLabel(this);
            m_label->setText("INT");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::DeltaRelativeToFront:
            m_label = new QLabel(this);
            m_label->setText("ΔFRT");
            break;

        case UserInterface::Widget::TimeInfoContainer::Type::DeltaRelativeToRear:
            m_label = new QLabel(this);
            m_label->setText("ΔBHD");
            break;

        default:
            m_label = new QLabel(this);
            m_label->setText("???");
            break;

    }
    if (m_label) {

        m_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    }
    m_time = new QLabel(this);
    Q_ASSERT(m_time);
    if (m_time) {

        m_time->setText("2:02.456");
        m_time->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    }

    m_label->raise();
    m_time->raise();

}