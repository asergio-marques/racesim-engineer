#include "listener/Director.h"

#include <QUdpSocket>

Listener::Director::Director() :
    socket(new QUdpSocket) {
        
}

Listener::Director::~Director() {

    delete socket;

}