#include "UDPSocketWin64.h"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <ws2tcpip.h>

NetCom::Listener::UDPSocketWin64::UDPSocketWin64() :
    Listener::SocketBase(),
    m_ipAddress(),
    m_port(),
    m_isBound(false),
    m_WSAInit(false),
    m_isSocketInit(false),
    m_implData(),
    m_socket(INVALID_SOCKET),
    m_datagramBuffer(),
    m_execThread() {

    // Receive implementation details
    int res = WSAStartup(MAKEWORD(2, 2), &m_implData);
    if (res == NO_ERROR) {

        m_WSAInit = true;

    }

}



NetCom::Listener::UDPSocketWin64::~UDPSocketWin64() {

    // Join thread if possible before destructing it
    if (m_execThread.joinable()) {
    
        m_execThread.join();
    
    }

}



bool NetCom::Listener::UDPSocketWin64::Init() {

    // Check if conditions for socket initialization are verified
    if (m_WSAInit && !m_isSocketInit) {
    
        m_socket = socket(AF_INET, SOCK_DGRAM, 0);

        // Check if initialization was successful, return true if so
        // Return false otherwise
        if (m_socket != INVALID_SOCKET) {
    
            m_isSocketInit = true;
            return true;
        
        }

    }

    return false;

}



bool NetCom::Listener::UDPSocketWin64::Bind(const uint16_t port, bool rebind) {

    // If the socket is actually already bound, it can be rebound automatically, just needs previous steps
    if (m_isBound && rebind) {

        // TODO unbind if already bound
        doBind(port);

    }
    // If rebind is not allowed and this is already bound, exit the function without success
    else if (m_isBound && !rebind) {
        
        return false;

    }
    // If not bound already and preconditions are valid, perform the actual binding
    if (m_WSAInit && m_isSocketInit && !m_isBound) {
        
        doBind(port);

    }
    
    return m_isBound;

}



void NetCom::Listener::UDPSocketWin64::Exec() {

    while (m_isBound) {
        
        // Struct to hold the details of the sender (IP, Port)
        sockaddr_in senderDetails;
        int senderDetailsSize = sizeof(senderDetails);

        // Blocking call to receive datagram
        int received = recvfrom(
            m_socket,
            m_datagramBuffer,
            m_datagramBufferSize,
            0,
            (SOCKADDR*)&senderDetails,
            &senderDetailsSize);

        // In case the datagram length is valid and there is a registered function, redirect the received info
        if (received >= 0 && m_regFunc) {

            m_regFunc(m_datagramBuffer, m_datagramBufferSize);

        }

        // Thread is executed at 50Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

    }

}



const std::string NetCom::Listener::UDPSocketWin64::getLocalIPAddress() {

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

        return std::string(ipAddressBuffer);

    }
    else {

        std::cout << "Could not obtain local IP address, error " << WSAGetLastError() << std::endl;
        return std::string("");

    }

}

void NetCom::Listener::UDPSocketWin64::doBind(const uint16_t port) {

    // Get IP address of local machine, quit function if empty string
    m_ipAddress = getLocalIPAddress();
    if (m_ipAddress.empty()) {

        return;

    }
    else {

        std::cout << "Listening at " << m_ipAddress << ":" << port << std::endl;

    }
    m_port = port;

    // Prepare socket details with the user input port and the local IP address
    sockaddr_in bindDetails;
    bindDetails.sin_family = AF_INET;
    bindDetails.sin_port = htons(port);
    bindDetails.sin_addr.s_addr = inet_addr(m_ipAddress.c_str());

    int bindRes = bind(m_socket, (SOCKADDR*) &bindDetails, sizeof(bindDetails));

    // If binding was successful, change the inner state and start the listening thread
    if (bindRes != 0) {

        m_isBound = false;
        std::cout << "Error in binding to socket: " << WSAGetLastError() << std::endl;

    }
    else {

        m_isBound = true;
        m_execThread = std::thread(&Listener::UDPSocketWin64::Exec, this);

    }

}