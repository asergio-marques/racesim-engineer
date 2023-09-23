#include <chrono>
#include <iostream>
#include <thread>
#include "packets/F1_23/EventData.h"
#include "packets/Helper.h"
#include "listener/Director.h"
#include "listener/UDPSocketWin64.h"

int main(int argc, char* argv[]) {

	std::cout << "RaceSim Engineer online." << std::endl;

    Listener::Director* director = new Listener::Director;
    Listener::UDPSocketWin64* socket = new Listener::UDPSocketWin64;
    director->setSocket(socket);

    while (true) {
    
        std::this_thread::sleep_for(std::chrono::seconds(500));
    
    }

	return 0;

}