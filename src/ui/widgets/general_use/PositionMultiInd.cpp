#include "general_use/PositionMultiInd.h"

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include "base/TextInterface.h"
#include "multiplayer_session/FastestLapIndicator.h"
#include "multiplayer_session/warning/WarningContainer.h"



UserInterface::Widget::PositionMultiIndicator::PositionMultiIndicator(QWidget* parent) :
    QWidget(parent),
    m_position(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::DriverPosition, this)),
    m_fastestLap(new UserInterface::Widget::FastestLapIndicator),
    m_trackLimWarn(new UserInterface::Widget::WarningContainer(UserInterface::Widget::WarningContainer::Type::TrackLimits, this)),
    m_otherWarn(new UserInterface::Widget::WarningContainer(UserInterface::Widget::WarningContainer::Type::OtherWarns, this)),
    m_currentPosition(0) {

    QGridLayout* generalLayout = new QGridLayout(this);
    QHBoxLayout* warnLayout = new QHBoxLayout(this);
    if (generalLayout && warnLayout) {

        if (m_trackLimWarn && m_otherWarn) {

            warnLayout->addWidget(m_trackLimWarn, 1, Qt::AlignCenter);
            warnLayout->addWidget(m_otherWarn, 1, Qt::AlignCenter);
            generalLayout->addLayout(warnLayout, 0, 0, Qt::AlignVCenter | Qt::AlignLeft);

        }
        
        if (m_position) {
        
            m_position->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
            generalLayout->addWidget(m_position, 0, 0, Qt::AlignCenter);
        
        }

        if (m_fastestLap) {

            generalLayout->addWidget(m_fastestLap, 0, 0, Qt::AlignCenter);

        }

    }

}




void UserInterface::Widget::PositionMultiIndicator::init(const uint8_t& initPosition) {

    if (m_fastestLap) {

        // hidden by default
        m_fastestLap->hide();

    }
    if (m_position) {

        m_position->setText(QString::number(initPosition));
        m_position->adjustSize();

    }

    m_currentPosition = initPosition;

}



void UserInterface::Widget::PositionMultiIndicator::updatePosition(const uint8_t newPosition) {

    m_currentPosition = newPosition;
    if (m_position) {

        m_position->setText(QString::number(newPosition));
        m_position->adjustSize();

    }

}



void UserInterface::Widget::PositionMultiIndicator::updateWarnings(bool isTrackLim, const int32_t change) {

    if (isTrackLim && m_trackLimWarn) {

        for (size_t i = 0; i < change; ++i) {

            m_trackLimWarn->addWarning();

        }

    }
    else if (!isTrackLim && m_otherWarn) {

        for (size_t i = 0; i < change; ++i) {

            m_otherWarn->addWarning();

        }

    }

}



void UserInterface::Widget::PositionMultiIndicator::sessionBestChange(bool gainOrLoss) {

    if (gainOrLoss) {

        m_fastestLap->show();

    }
    else {

        m_fastestLap->hide();

    }

}



const uint8_t UserInterface::Widget::PositionMultiIndicator::getCurrentPosition() const {

    return m_currentPosition;

}