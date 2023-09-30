#include <chrono>
#include <iostream>
#include <thread>
#include "listener/Director.h"
#include "listener/UDPSocketWin64.h"
#include "settings/StoreFront.h"
#include "settings/Key.h"

int main(int argc, char* argv[]) {

	std::cout << "RaceSim Engineer online." << std::endl;

    // Instantiate director class and inject socket as a test
    // Then infinite loop while the separate listen thread triggers actions
    Listener::Director* director = new Listener::Director;
    Listener::UDPSocketWin64* socket = new Listener::UDPSocketWin64;
    director->setSocket(socket);
    
    Settings::StoreFront* settingsStore = Settings::StoreFront::getInstance();

    if (settingsStore)
    {
        
    }


    while (true) {
    
        std::this_thread::sleep_for(std::chrono::seconds(500));
    
    }

	return 0;

}