#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <WinSock2.h>
#include <ws2tcpip.h>



const std::string getLocalIPAddress();



int main(int argc, char* argv[]) {
    
    WSADATA implData;
    SOCKET mySocket;
    char datagramBuffer[4096];
    const static size_t datagramBufferSize = 4096;

    int res = WSAStartup(MAKEWORD(2, 2), &implData);
    if (res != NO_ERROR) {

        return 1;

    }

    mySocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_HOPOPTS);

    if (mySocket == INVALID_SOCKET || mySocket == SOCKET_ERROR) {

        return 2;

    }

    // Get the IP address of the local machine
    std::string ipAddress = getLocalIPAddress();

    if (ipAddress.empty()) {

        return 3;

    }

    // Hard-coded for the time being
    uint16_t port = 12007;

    sockaddr_in bindDetails;
    bindDetails.sin_family = AF_INET;
    bindDetails.sin_port = htons(port);
    bindDetails.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    int lastError = 0;

    // Send messages every 5 seconds containing the epoch time
    while (true) {
        
        std::string msg("Sending message at ");
        int time = std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1);
        msg = msg.append(std::to_string(time));

        sockaddr_in destDetails;
        destDetails.sin_family = AF_INET;
        destDetails.sin_port = htons(port);
        destDetails.sin_addr.s_addr = inet_addr(ipAddress.c_str());

        int sendRes = sendto(mySocket, msg.c_str(), msg.size(), 0, (sockaddr*)&destDetails, sizeof(destDetails));
        if (sendRes <= 0) {
    
            int error = WSAGetLastError();
            if (error != lastError) {

                std::cout << "Error in sending packet: " << error << std::endl;
                lastError = error;

            }

        }

        std::cout << "Sent packet" << std::endl << "\t" << msg << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(5));
    
    }

    return 0;

}



const std::string getLocalIPAddress() {

    const char* googleDNS = "8.8.8.8";
    int googlePort = 53;
    SOCKET testSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (testSocket < 0) {

        std::cout << "Could not create socket, error " << WSAGetLastError() << std::endl;
        return std::string("");

    }

    // Connect to Google DNS server
    sockaddr_in servInfo;
    servInfo.sin_family = AF_INET;
    servInfo.sin_addr.s_addr = inet_addr(googleDNS);
    servInfo.sin_port = htons(googlePort);

    int connRes = connect(testSocket, (const SOCKADDR*) &servInfo, sizeof(servInfo));
    if (connRes < 0) {

        std::cout << "Could not connect socket, error " << WSAGetLastError() << std::endl;
        return std::string("");

    }

    // Get local machine info
    sockaddr_in localInfo;
    int localInfoSize = sizeof(localInfo);
    int infoRes = getsockname(testSocket, (SOCKADDR*) &localInfo, &localInfoSize);
    if (infoRes < 0) {

        std::cout << "Could not obtain socket connect info, error " << WSAGetLastError() << std::endl;
        return std::string("");

    }

    // Produce local IP address string
    char ipAddressBuffer[20];
    const char* p = inet_ntop(AF_INET, &localInfo.sin_addr, ipAddressBuffer, 20);

    if (p != nullptr) {

        std::cout << "Local IP Address is: " << ipAddressBuffer << std::endl;
        return std::string(ipAddressBuffer);

    }
    else {

        std::cout << "Could not obtain local IP address, error " << WSAGetLastError() << std::endl;
        return std::string("");

    }

}