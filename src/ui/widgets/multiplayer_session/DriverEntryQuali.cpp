#include "multiplayer_session/DriverEntryQuali.h"

#include <QList>
#include <QWidget>
#include "base/Container.h"
#include "base/TextInterface.h"
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Penalty.h"
#include "data/internal/Session.h"
#include "multiplayer_session/FastestLapIndicator.h"
#include "multiplayer_session/TeamIcon.h"
#include "multiplayer_session/sectors/SectorInfoArray.h"
#include "multiplayer_session/timing/LapInfoContainer.h"
#include "styles/DriverInfo.h"
#include "styles/General.h"




UserInterface::Widget::DriverEntryQuali::DriverEntryQuali(QWidget* parent) :
    UserInterface::Widget::IDriverEntry(),
    m_position(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::DriverPosition, parent)),
    m_teamIcon(new UserInterface::Widget::TeamIcon(parent)),
    m_driverName(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::DriverName, parent)),
    m_personalBestLap(new UserInterface::Widget::LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type::PersonalBestTime, parent)),
    m_lastLap(new UserInterface::Widget::LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type::LastLapTime, parent)),
    m_sectorArray(new UserInterface::Widget::SectorInfoArray(parent)) {

    if (m_position) {

        m_position->raise();
        m_position->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_position->setAlignment(Qt::AlignCenter);
        m_allWidgets.append(m_position);

    }

    if (m_teamIcon) {

        m_allWidgets.append(m_teamIcon);

    }

    if (m_driverName) {

        m_driverName->setFontThickness(UserInterface::Widget::FontThickness::Regular);
        m_allWidgets.append(m_driverName);

    }

    if (m_lastLap) {

        m_allWidgets.append(m_lastLap);

    }

    if (m_personalBestLap) {

        m_allWidgets.append(m_personalBestLap);

    }
    if (m_sectorArray) {

        m_allWidgets.append(m_sectorArray);

    }

}



void UserInterface::Widget::DriverEntryQuali::init(const Session::Internal::Participant dataPacket, const QList<uint8_t> sectorConfiguration) {

    m_driverIndex = dataPacket.m_index;
    m_currentPosition = dataPacket.m_startPosition;
    m_isPlayer = dataPacket.m_isPlayer;

    if (m_position) {

        m_position->show();
        m_position->setText(QString::number(dataPacket.m_startPosition));

    }
    if (m_teamIcon) {

        m_teamIcon->show();
        m_teamIcon->SetTeam(dataPacket.m_teamID);

    }
    if (m_driverName) {

        m_driverName->show();
        m_driverName->setText(dataPacket.m_shortName);

    }
    if (m_personalBestLap) {

        m_personalBestLap->init();

    }
    if (m_lastLap) {

        m_lastLap->init();

    }
    if (m_sectorArray) {

        m_sectorArray->Init(sectorConfiguration);

    }

    redoLayout();

}



void UserInterface::Widget::DriverEntryQuali::updatePosition(const uint8_t newPosition) {

    m_currentPosition = newPosition;
    if (m_position) {

        m_position->setText(QString::number(newPosition));
        m_position->adjustSize();

    }

}



void UserInterface::Widget::DriverEntryQuali::updateStatus(const Participant::Internal::Status status) {

    // TODO

}



void UserInterface::Widget::DriverEntryQuali::newSessionBestLap(const Lap::Internal::Time newLapTime, const bool isThisDrivers) {

    if (m_personalBestLap && m_lastLap) {

        if (isThisDrivers) {

            m_personalBestLap->changeSessionBestStatus(true);
            m_personalBestLap->updateTime(newLapTime);
            m_lastLap->changeSessionBestStatus(true);
            m_lastLap->updateTime(newLapTime);

        }
        else {

            m_personalBestLap->changeSessionBestStatus(false);
            m_lastLap->changePersonalBestStatus(false);

        }

    }

}



void UserInterface::Widget::DriverEntryQuali::newPersonalBestLap(const Lap::Internal::Time newLapTime) {

    if (m_personalBestLap && m_lastLap) {

        m_personalBestLap->changeSessionBestStatus(false);
        m_personalBestLap->updateTime(newLapTime);

        m_lastLap->changePersonalBestStatus(false);
        m_lastLap->updateTime(newLapTime);

    }

}



void UserInterface::Widget::DriverEntryQuali::newLatestLap(const Lap::Internal::Time newLapTime) {

    if (m_lastLap) {

        m_lastLap->changePersonalBestStatus(false);
        m_lastLap->updateTime(newLapTime);

    }

}



void UserInterface::Widget::DriverEntryQuali::sectorChange(const bool isMinisector, const uint8_t lapID, const uint8_t orderID, const uint8_t parentOrderID,
    const Lap::Internal::Status sectorStatus, const Lap::Internal::Performance sectorPerf, const Lap::Internal::Time sectorTime) {

    if (m_sectorArray) {

        if (isMinisector) {

            m_sectorArray->updateMiniSector(lapID, parentOrderID, orderID, sectorTime, sectorPerf);

        }
        else
        {

            m_sectorArray->updateSector(lapID, orderID, sectorTime, sectorPerf);

        }

    }

}



void UserInterface::Widget::DriverEntryQuali::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    m_x = centerAlignmentX ? x - (width() / 2) : x;
    m_y = centerAlignmentY ? y - (height() / 2) : y;

    redoLayout();

}



void UserInterface::Widget::DriverEntryQuali::scale(const uint8_t percent) {



}



void UserInterface::Widget::DriverEntryQuali::scale(const uint8_t percentX, const uint8_t percentY) {



}



void UserInterface::Widget::DriverEntryQuali::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    m_width = newWidth;
    m_height = newHeight;

    redoLayout();

}



void UserInterface::Widget::DriverEntryQuali::raise() {

    if (m_position) m_position->raise();
    if (m_teamIcon) m_teamIcon->raise();
    if (m_driverName) m_driverName->raise();
    if (m_personalBestLap) m_driverName->raise();
    if (m_lastLap) m_driverName->raise();

}



void UserInterface::Widget::DriverEntryQuali::lower() {

    if (m_position) m_position->lower();
    if (m_teamIcon) m_teamIcon->lower();
    if (m_driverName) m_driverName->lower();
    if (m_personalBestLap) m_driverName->lower();
    if (m_lastLap) m_driverName->lower();

}



const int16_t UserInterface::Widget::DriverEntryQuali::width() const {

    return m_width;

}



const int16_t UserInterface::Widget::DriverEntryQuali::height() const {

    return m_height;

}



const int16_t UserInterface::Widget::DriverEntryQuali::x() const {

    return m_x;

}

    

const int16_t UserInterface::Widget::DriverEntryQuali::y() const {

    return m_y;

}



void UserInterface::Widget::DriverEntryQuali::redoLayout() {

    uint16_t totalWidth = 0;
    auto rowHeight = UserInterface::Style::RowHeight.GetValue(height());
    uint16_t centerY = y() + (rowHeight / 2);

    const uint16_t calcPadding = UserInterface::Style::PaddingReference.GetValue(width());
    auto warningIconDim = UserInterface::Style::WarningIconSize.GetValue(height());
    uint16_t fastLapCenterX = x() + (rowHeight / 2) + warningIconDim + calcPadding;
    
    // for alignment with race
    totalWidth += warningIconDim + calcPadding;

    if (m_position) {

        m_position->setFontSize(UserInterface::Style::PositionFontSize.GetValue(height()));
        m_position->adjustSize();
        m_position->move(fastLapCenterX, centerY, true, true);

        totalWidth += rowHeight + calcPadding;

    }
    if (m_teamIcon) {

        m_teamIcon->setSize(rowHeight, rowHeight, true);
        m_position->adjustSize();

        // Add the padding! And the width for centering!
        totalWidth += (calcPadding * 3);
        m_teamIcon->move(x() + totalWidth + (rowHeight / 2), centerY, true, true);

        // Add padding again to account for the right padding
        totalWidth += rowHeight + calcPadding;

    }
    if (m_driverName) {

        m_driverName->setFontSize(UserInterface::Style::DriverNameFontSize.GetValue(height()));
        m_driverName->adjustSize();

        const uint16_t calcMaxNameWidth = UserInterface::Style::DriverNameMaximumWidth.GetValue(width());

        // Add the padding, again! And the maximum width for centering!
        totalWidth += calcPadding;
        m_driverName->move(x() + totalWidth + (calcMaxNameWidth / 2), centerY, true, true);

        // Add padding again to account for the right padding
        // Use the maximum width as reference, not the actual width,
        // otherwise everything to the right will be misaligned
        totalWidth += calcMaxNameWidth + calcPadding;

    }
    if (m_personalBestLap && m_lastLap) {

        m_personalBestLap->setSize(UserInterface::Style::LapInfoBackgroundMaxX.GetValue(width()), UserInterface::Style::LapInfoBackgroundMaxY.GetValue(height()), false);
        m_personalBestLap->setTextFontSize(UserInterface::Style::LapInfoLabelFontSize.GetValue(height()));
        m_personalBestLap->adjustSize();

        m_lastLap->setSize(UserInterface::Style::LapInfoBackgroundMaxX.GetValue(width()), UserInterface::Style::LapInfoBackgroundMaxY.GetValue(height()), false);
        m_lastLap->setTextFontSize(UserInterface::Style::LapInfoLabelFontSize.GetValue(height()));
        m_lastLap->adjustSize();

        // Add the padding, again! And the maximum width for centering!
        totalWidth += calcPadding;
        m_personalBestLap->move(x() + totalWidth, y() + (calcPadding / 2), false, false);
        m_lastLap->move(x() + totalWidth, y() + (calcPadding / 2) + m_personalBestLap->height(), false, false);

        // Add padding again to account for the right padding
        totalWidth += m_personalBestLap->width() + calcPadding;

    }
    if (m_sectorArray) {

        // no calc, it's meant to happen "inside"
        m_sectorArray->setSize(width(), height(), false);
        m_sectorArray->adjustSize();

        // Add the padding, again! And the maximum width for centering!
        totalWidth += (calcPadding * 5);
        m_sectorArray->move(x() + totalWidth, y(), false, false);

        // Padding to be added to every tyre container icon as well, so multiply it by the number of icons to be displayed
        totalWidth += ((UserInterface::Style::SectorInfoContainerMaxX.GetValue(width()) + calcPadding)
            * UserInterface::Style::SectorInfoContainerMaxNum);

    }

}