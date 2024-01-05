#include "base/Container.h"

#include <QObject>



UserInterface::Widget::Container::Container(UserInterface::Widget::ID id) :
    QObject(),
    UserInterface::Widget::Interface(id) {



}