#include "multiplayer_session/timing/TimeInfoContainer.h"

#include "base/Container.h"
#include "base/ImageInterface.h"
#include "base/TextInterface.h"
#include "styles/Standings.h"



UserInterface::Widget::TimeInfoContainer::TimeInfoContainer(const UserInterface::Widget::TimeInfoContainer::Type type, QWidget* parent) : 
    UserInterface::Widget::Container(UserInterface::Widget::ID::InvalidUnknown),
    m_type(UserInterface::Widget::TimeInfoContainer::Type::InvalidUnknown),
    m_label(nullptr),
    m_time(nullptr),
    m_backgrounds() {

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
    if (m_label) {

        m_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    }
    m_time = new UserInterface::Widget::TextInterface(m_id, parent);
    Q_ASSERT(m_time);
    if (m_time) {

        m_time->setText("2:02.456");
        m_time->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    }

    m_label->raise();
    m_time->raise();

}



void UserInterface::Widget::TimeInfoContainer::scale(const uint8_t percentX, const uint8_t percentY) {

    // TODO

}



void UserInterface::Widget::TimeInfoContainer::scale(const uint8_t percent) {

    // TODO

}



void UserInterface::Widget::TimeInfoContainer::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    for (auto* background : m_backgrounds) {

        if (background) {

            background->setSize(newWidth, newHeight, keepAspectRatio);

        }

    }

}



void UserInterface::Widget::TimeInfoContainer::raise(void) {

    // TODO

}



void UserInterface::Widget::TimeInfoContainer::lower(void) {

    // TODO

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



const int16_t UserInterface::Widget::TimeInfoContainer::width(void) const {

    uint16_t widthMax = 0;
    for (const auto* background : m_backgrounds) {

        if (background && (background->width() > widthMax)) {

            widthMax = background->width();

        }

    }
    return widthMax;

}



const int16_t UserInterface::Widget::TimeInfoContainer::height(void) const {

    uint16_t heightMax = 0;
    for (const auto* background : m_backgrounds) {

        if (background && (background->height() > heightMax)) {

            heightMax = background->height();

        }

    }
    return heightMax;

}



const int16_t UserInterface::Widget::TimeInfoContainer::x(void) const {

    uint16_t xMin = UINT16_MAX;
    for (const auto* background : m_backgrounds) {

        if (background && (xMin > background->x())) {

            xMin = background->x();

        }

    }
    return xMin;

}



const int16_t UserInterface::Widget::TimeInfoContainer::y(void) const {

    uint16_t yMin = UINT16_MAX;
    for (const auto* background : m_backgrounds) {

        if (background && (yMin > background->y())) {

            yMin = background->y();

        }

    }
    return yMin;

}



void UserInterface::Widget::TimeInfoContainer::move(const uint16_t x, const uint16_t y, const bool centerX, const bool centerY) {

    uint16_t centerOfY = y;

    for (auto* background : m_backgrounds) {

        if (background) {

            background->move(x, y, centerX, centerY);
            centerOfY = background->y() + (background->height() / 2);

        }

    }

    if (m_label) {

        m_label->move(x + 3, centerOfY, false, true);

    }

    if (m_time) {

        m_time->move(x + width() - m_time->width()  - 3, centerOfY, false, true);

    }

}
