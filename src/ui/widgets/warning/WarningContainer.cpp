#include "warning/WarningContainer.h"

#include <QWidget>
#include "base/ID.h"
#include "base/ImageInterface.h"
#include "base/TextInterface.h"
#include "warning/WarningIcon.h"




UserInterface::Widget::WarningContainer::WarningContainer(const UserInterface::Widget::WarningContainer::Type type, QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::WarningIcon),
    m_icon(new UserInterface::Widget::WarningIcon(parent)),
    m_warningCount(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::WarningIcon, parent)),
    m_currentlyActiveWarnings(0) {

    if (m_icon) {

        m_icon->hide();

        if (type == UserInterface::Widget::WarningContainer::Type::TrackLimits) {

            m_icon->SetTrackLimitType();

        }
        else if (type == UserInterface::Widget::WarningContainer::Type::OtherWarns) {

            m_icon->SetOtherWarningsType();

        }

    }
    if (m_warningCount) {

        m_warningCount->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_warningCount->setAlignment(Qt::AlignCenter);
        m_warningCount->raise();
        m_warningCount->setText("0");
        m_warningCount->hide();

    }

}



void UserInterface::Widget::WarningContainer::addWarning(const int32_t change) {

    if (m_warningCount) {

        m_currentlyActiveWarnings += change;
        m_warningCount->setText(QString::number(m_currentlyActiveWarnings));
        m_warningCount->adjustSize();

    }

    // HACK: this is part of game rules and should be sorted out in the processor!
    if (m_warningCount && m_icon) {
        if (m_currentlyActiveWarnings == 0 || m_currentlyActiveWarnings == 3) {

            m_currentlyActiveWarnings = 0;
            m_warningCount->hide();
            m_icon->hide();

        }
        else {

            m_warningCount->show();
            m_icon->show();

        }

    }

}



void UserInterface::Widget::WarningContainer::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    m_x = centerAlignmentX ? x - std::ceil(width() / 2) : x;
    m_y = centerAlignmentY ? y - std::ceil(height() / 2) : y;

    if (m_icon) {

        m_icon->move(m_x, m_y, false, false);

    }

    if (m_warningCount) {

        // Center the text in the icon
        m_warningCount->move(m_x + (m_width / 2), m_y + (m_height / 2), true, true);

    }

}



void UserInterface::Widget::WarningContainer::scale(const uint8_t percent) {



}



void UserInterface::Widget::WarningContainer::scale(const uint8_t percentX, const uint8_t percentY) {



}



void UserInterface::Widget::WarningContainer::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    m_width = newWidth;
    m_height = newHeight;

    if (m_icon) {

        m_icon->setSize(m_width, m_height, keepAspectRatio);
        m_icon->adjustSize();

    }

}



void UserInterface::Widget::WarningContainer::raise() {

    if (m_icon) m_icon->raise();
    if (m_warningCount) m_warningCount->raise();

}



void UserInterface::Widget::WarningContainer::lower() {

    if (m_icon) m_icon->lower();
    if (m_warningCount) m_warningCount->lower();

}



void UserInterface::Widget::WarningContainer::setTextFontSize(const uint16_t size) {

    if (m_warningCount) {

        m_warningCount->setFontSize(size);
        m_warningCount->adjustSize();

    }

}



const int16_t UserInterface::Widget::WarningContainer::width() const {

    return m_width;

}



const int16_t UserInterface::Widget::WarningContainer::height() const {
    
    return m_height;

}



const int16_t UserInterface::Widget::WarningContainer::x() const {

    return m_x;

}



const int16_t UserInterface::Widget::WarningContainer::y() const {

    return m_y;

}