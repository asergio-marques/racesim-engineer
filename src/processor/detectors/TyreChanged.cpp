#include "detectors/TyreChanged.h"

#include "data/internal/TyreData.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"




const Processor::Detector::Type Processor::Detector::TyreChanged::GetType() const {

    return Processor::Detector::Type::TyreChanged;

}