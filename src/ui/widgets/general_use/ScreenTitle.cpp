#include "general_use/ScreenTitle.h"

#include <QFont>
#include <QFontDatabase>
#include <QLabel>
#include <QString>
#include <QWidget>
#include "ScreenType.h"
#include "base/TextInterface.h"
#include "base/ID.h"




UserInterface::Widget::ScreenTitle::ScreenTitle(UserInterface::Widget::ID id, QWidget* parent) :
    UserInterface::Widget::TextInterface(id, parent) {

    setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);

}



void UserInterface::Widget::ScreenTitle::setTitle(UserInterface::Screen::Type type) {

    switch (type) {

        case UserInterface::Screen::Type::Loading:
            setText("Waiting for a session to start...");
            break;

        case UserInterface::Screen::Type::TimeTrial:
            setText("Time Trial");
            break;

        case UserInterface::Screen::Type::FreePractice:
            setText("Practice");
            break;

        case UserInterface::Screen::Type::Qualifying:
            setText("Quali");
            break;

        case UserInterface::Screen::Type::Race:
            setText("Race");
            break;

        default:
            setText("N/A");
            break;

    }

}