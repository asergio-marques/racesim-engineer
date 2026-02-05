#include "multiplayer_session/sectors/SectorIcon.h"

#include "Image.h"
#include "PixmapFactory.h"
#include "base/ImageInterface.h"
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




UserInterface::Widget::SectorIcon::SectorIcon(QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::SectorInfo, parent),
    m_toolTipText() {

    setToolTipDuration(-1);
    fetchPixmap(UserInterface::Widget::StandardImage::NotRunBase);

}



void UserInterface::Widget::SectorIcon::performanceChanged(Lap::Internal::Performance perf, const Lap::Internal::Time& time,
    const uint8_t lapID) {

    if (perf == Lap::Internal::Performance::NotRun) return;

    switch (perf) {

        case Lap::Internal::Performance::CurrentlyRunning:
            fetchPixmap(UserInterface::Widget::StandardImage::RunningOnTrackBase);
            break;

        case Lap::Internal::Performance::CurrentlyRunningPits:
            fetchPixmap(UserInterface::Widget::StandardImage::RunningInPitsBase);
            break;

        case Lap::Internal::Performance::CurrentlyRunningInvalid:
            fetchPixmap(UserInterface::Widget::StandardImage::RunningInvalidBase);
            break;

        case Lap::Internal::Performance::FinishedNormal:
            fetchPixmap(UserInterface::Widget::StandardImage::FinishedNotImprovementBase);
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedPits:
            fetchPixmap(UserInterface::Widget::StandardImage::FinishedInPitsBase);
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedInvalid:
            fetchPixmap(UserInterface::Widget::StandardImage::FinishedInvalidBase);
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedPersonalBest:
            fetchPixmap(UserInterface::Widget::StandardImage::FinishedPersonalBestBase);
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedSessionBest:
            fetchPixmap(UserInterface::Widget::StandardImage::FinishedSessionFastestBase);
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedRetired:
            fetchPixmap(UserInterface::Widget::StandardImage::FinishedRetirementCompleteBase);
            appendTooltipText(time, lapID);
            break;
        
        default:
            // only missing value is NotRun, which is returned from at function entry
            break;

    }

}



void UserInterface::Widget::SectorIcon::reset() {

    fetchPixmap(UserInterface::Widget::StandardImage::NotRunBase);

}



void UserInterface::Widget::SectorIcon::fetchPixmap(UserInterface::Widget::StandardImage baseID) {

    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance) {

        instance->fetchPixmap(static_cast<UserInterface::Widget::StandardImage>(static_cast<uint16_t>(baseID)), m_pixmap);

    }

}



void UserInterface::Widget::SectorIcon::appendTooltipText(const Lap::Internal::Time& time, const uint8_t lapID) {

    if (time.valid()) {

        m_toolTipText += "Lap " + QString::number(lapID) + " - " + QString::fromStdString(time.formattedPrint(true)) + "\n";

    }
    else {

        m_toolTipText += "Lap " + QString::number(lapID) + " - N/A\n";

    }

    setToolTip(m_toolTipText);

}