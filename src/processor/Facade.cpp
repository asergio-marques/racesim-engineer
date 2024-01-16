#include "Facade.h"

#include <memory>
#include "data/Databank.h"
#include "packets/game/Subscriber.h"



Processor::Facade::Facade() :
    m_databank(new Processor::Data::Databank) {



}



Processor::Facade::~Facade() {

    delete m_databank;

}



void Processor::Facade::OnPacketBroadcast(Packet::Game::Interface* packet) {

    // TODO do stuff

}