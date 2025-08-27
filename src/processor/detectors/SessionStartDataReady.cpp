#include "detectors/SessionStartDataReady.h"

#include "detectors/Interface.h"
#include "detectors/Type.h"



const Processor::Detector::Type Processor::Detector::SessionStartDataReady::GetType() const {

    return Processor::Detector::Type::SessionStartDataReady;

}