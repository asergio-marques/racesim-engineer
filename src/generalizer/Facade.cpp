#include "Facade.h"
#include "adapters/F1_25.h"




Generalizer::Facade::Facade() :
	m_gameAdapter(new Generalizer::Adapter::F1_25) {

}



Packet::Internal::Broadcaster* Generalizer::Facade::exposeBroadcasterInterface() {

	return this;

}



void Generalizer::Facade::OnPacketBroadcast(std::shared_ptr<Packet::Game::Interface> packet) {

	// TODO Game is always F1 25 right now
	//if (m_presenter->GetGame() == Settings::Game::F1_25) {
	if (m_gameAdapter && packet) {

		std::vector<std::shared_ptr<Packet::Internal::Interface>> internalPackets = m_gameAdapter->ConvertPacket(packet);

		Broadcast(internalPackets);

	}

}