#include <chrono>
#include <iostream>
#include <thread>
#include "listener/Director.h"
#include "listener/UDPSocketWin64.h"
#include "settings/StoreFront.h"
#include "UIStarter.h"

int main(int argc, char* argv[]) {

    Settings::StoreFront* settingsStore = Settings::StoreFront::getInstance();

    if (settingsStore)
    {
        settingsStore->Init();
    }

    Listener::Director* director = new Listener::Director;
    Listener::UDPSocketWin64* socket = new Listener::UDPSocketWin64;
    director->setSocket(socket);

    UserInterface::UIStarter* starter = new UserInterface::UIStarter;
    starter->Init(&argc, &argv);
    int runResult = starter->Run();

	return 0;

}