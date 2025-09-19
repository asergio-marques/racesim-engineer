#include "multiplayer_session/sectors/MiniSectorIcon.h"

#include "Image.h"
#include "PixmapFactory.h"




UserInterface::Widget::MiniSectorIcon::MiniSectorIcon(const uint8_t numMinis, QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::SectorInfo, parent),
    m_numMinis(numMinis),
    m_finished(false) {

    calculateIDAndFetch(UserInterface::Widget::StandardImage::NotRunBase);

}



void UserInterface::Widget::MiniSectorIcon::performanceChanged(Lap::Internal::Performance perf) {

    if (m_finished || perf == Lap::Internal::Performance::NotRun) return;

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
            m_finished = true;
            break;

        case Lap::Internal::Performance::FinishedPits:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::FinishedInPitsBase);
            m_finished = true;
            break;

        case Lap::Internal::Performance::FinishedInvalid:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::FinishedInvalidBase);
            m_finished = true;
            break;

        case Lap::Internal::Performance::FinishedPersonalBest:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::FinishedPersonalBestBase);
            m_finished = true;
            break;

        case Lap::Internal::Performance::FinishedSessionBest:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::FinishedSessionFastestBase);
            m_finished = true;
            break;

        case Lap::Internal::Performance::FinishedRetired:
            calculateIDAndFetch(UserInterface::Widget::StandardImage::FinishedRetirementCompleteBase);
            m_finished = true;
            break;
        
        default:
            // only missing value is NotRun, which is returned from at function entry
            break;

    }

}



void UserInterface::Widget::MiniSectorIcon::reset() {

    calculateIDAndFetch(UserInterface::Widget::StandardImage::NotRunBase);
    m_finished = false;

}



void UserInterface::Widget::MiniSectorIcon::calculateIDAndFetch(UserInterface::Widget::StandardImage baseID) {

    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    uint16_t basePixmapID = static_cast<uint16_t>(baseID) + m_numMinis;
    Q_ASSERT(instance);
    if (instance) {

        instance->fetchPixmap(static_cast<UserInterface::Widget::StandardImage>(basePixmapID), m_pixmap);

    }

}