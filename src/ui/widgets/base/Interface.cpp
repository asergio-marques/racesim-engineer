#include "base/Interface.h"

#include <QObject>
#include "base/ID.h"



UserInterface::Widget::Interface::Interface(UserInterface::Widget::ID id) :
    QObject(),
    m_id(id) {



}

const UserInterface::Widget::ID& UserInterface::Widget::Interface::GetId() const {

    return m_id;

}