#include "base/Container.h"

#include <QObject>



UserInterface::Widget::Container::Container(UserInterface::Widget::ID id) :
    QObject(),
    UserInterface::Widget::Interface(id) {



}



void UserInterface::Widget::Container::setTextFontSize(const uint16_t size) {

    // empty implementation by default, to be overridden by all containers
    // that possess text elements within

}



void UserInterface::Widget::Container::adjustSize() {

    // empty implementation by default, to be overridden by all containers

}