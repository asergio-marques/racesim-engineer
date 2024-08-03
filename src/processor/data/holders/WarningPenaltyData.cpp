#include "data/holders/WarningPenaltyData.h"

#include <cstdint>
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "detectors/WarningPenalty.h"



// Add relevant detectors to then be called when relevant
void Processor::Data::WarningPenaltyData::installDetector(Processor::Detector::Interface* detector) {

    if (!detector) return;

    switch (detector->GetType()) {

        case Processor::Detector::Type::WarningPenalty:
            m_installedPenWarnDetector = dynamic_cast<Processor::Detector::WarningPenalty*>(detector);
            break;

        default:
            // do nothing
            break;

    }

}



void Processor::Data::WarningPenaltyData::updateWarningPenalties(const int8_t id, const uint8_t totalWarnings,
                const uint8_t trackLimitWarnings, const uint16_t timePenalties,
                const uint8_t stopGoPens, const uint8_t driveThroughPens) {

    const int8_t diffTotalWarns = totalWarnings - m_totalWarns;
    const int8_t diffTrackLimWarns = trackLimitWarnings - m_numTrackLimits;
    const int32_t diffTimePen = timePenalties - m_timePenMS;
    const int8_t diffStopGo = stopGoPens - m_numStopGo;
    const int8_t diffDriveThrough = driveThroughPens - m_numDriveThrough;

    // Only pass information to the detector if there are indeed changes in state
    if ((diffTotalWarns != 0) || (diffTrackLimWarns != 0) || (diffTimePen != 0) ||
            (diffStopGo != 0) || (diffDriveThrough != 0)) {

        if (m_installedPenWarnDetector) {

            m_installedPenWarnDetector->AddWarnPenChange(id, diffTotalWarns,
                diffTrackLimWarns, diffTimePen, diffStopGo, diffDriveThrough);

        }

        // Update information
        if (diffTotalWarns != 0) m_totalWarns = totalWarnings;
        if (diffTrackLimWarns != 0) m_numTrackLimits = trackLimitWarnings;
        if (diffTimePen != 0) m_timePenMS = timePenalties;
        if (diffStopGo != 0) m_numStopGo = stopGoPens;
        if (diffDriveThrough != 0) m_numDriveThrough = driveThroughPens;

    }

}