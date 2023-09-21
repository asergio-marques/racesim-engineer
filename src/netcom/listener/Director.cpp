#include "listener/Director.h"

#include <QUdpSocket>

F1_23::Listener::Director::Director() :
    socket(new QUdpSocket) {
        
}

F1_23::Listener::Director::~Director() {

    delete socket;

}