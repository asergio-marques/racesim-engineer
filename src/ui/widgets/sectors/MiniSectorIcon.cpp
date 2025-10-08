#include "sectors/MiniSectorIcon.h"

#include "Image.h"
#include "PixmapFactory.h"
#include "base/ImageInterface.h"
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




UserInterface::Widget::MiniSectorIcon::MiniSectorIcon(const uint8_t numMinis, QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::SectorInfo, parent),
    m_numMinis(numMinis),
    m_toolTipText() {

    setToolTipDuration(-1);
    calculateIDAndFetch(UserInterface::Widget::StandardImage::NotRunBase);

}



void UserInterface::Widget::MiniSectorIcon::performanceChanged(Lap::Internal::Performance perf, const Lap::Internal::Time& time,
    const uint8_t lapID) {

    if (perf == Lap::Internal::Performance::NotRun) return;

    switch (perf) {

        case Lap::Internal::Performance::CurrentlyRunning:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::RunningOnTrackBase);
            break;

        case Lap::Internal::Performance::CurrentlyRunningPits:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::RunningInPitsBase);
            break;

        case Lap::Internal::Performance::CurrentlyRunningInvalid:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::RunningInvalidBase);
            break;

        case Lap::Internal::Performance::FinishedNormal:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::FinishedNotImprovementBase);
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedPits:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::FinishedInPitsBase);
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedInvalid:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::FinishedInvalidBase);
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedPersonalBest:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::FinishedPersonalBestBase);
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedSessionBest:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::FinishedSessionFastestBase);
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedRetired:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::FinishedRetirementCompleteBase);
            appendTooltipText(time, lapID);
            break;
        
        default:
            // only missing value is NotRun, which is returned from at function entry
            break;

    }

}



void UserInterface::Widget::MiniSectorIcon::reset() {

    calculateIDAndFetch(UserInterface::Widget::StandardImage::NotRunBase);

}



void UserInterface::Widget::MiniSectorIcon::calculateIDAndFetch(UserInterface::Widget::StandardImage baseID) {

    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    const auto basePixmapID = static_cast<uint16_t>(baseID) + m_numMinis;
    Q_ASSERT(instance);
    if (instance) {

        instance->fetchPixmap(static_cast<UserInterface::Widget::StandardImage>(basePixmapID), m_pixmap);

    }

}



void UserInterface::Widget::MiniSectorIcon::appendTooltipText(const Lap::Internal::Time& time, const uint8_t lapID) {

    if (time.valid()) {

        m_toolTipText += "Lap " + QString::number(lapID) + " - " + QString::fromStdString(time.formattedPrint(true)) + "\n";

    }
    else {

        m_toolTipText += "Lap " + QString::number(lapID) + " - N/A\n";

    }

    setToolTip(m_toolTipText);

}