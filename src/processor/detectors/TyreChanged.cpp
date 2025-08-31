#include "detectors/TyreChanged.h"

#include "data/internal/TyreData.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/TyreChanged.h"




const Processor::Detector::Type Processor::Detector::TyreChanged::GetType() const {

    return Processor::Detector::Type::TyreChanged;

}



void Processor::Detector::TyreChanged::addTyreChangeInfo(const uint8_t driverID, const Tyre::Internal::Data newTyreData) {


    Packet::Event::TyreChanged* packet = new Packet::Event::TyreChanged();
    packet->m_index = driverID;
    packet->m_tyreInfo = newTyreData;
    m_packetsToBeProcessed.push_back(packet);

}