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

    this->SetFontThickness(UserInterface::Widget::FontThickness::Bold);

}



bool UserInterface::Widget::ScreenTitle::Update() {
    
    return true;

}



void UserInterface::Widget::ScreenTitle::SetTitle(UserInterface::Screen::Type type) {

    switch (type) {

        case UserInterface::Screen::Type::Loading:
            this->SetText("Waiting for a session to start...");
            break;

        case UserInterface::Screen::Type::TimeTrial:
            this->SetText("Time Trial");
            break;

        case UserInterface::Screen::Type::FreePractice:
            this->SetText("Practice");
            break;

        case UserInterface::Screen::Type::Qualifying:
            this->SetText("Quali");
            break;

        case UserInterface::Screen::Type::Race:
            this->SetText("Race");
            break;

        default:
            this->SetText("N/A");
            break;

    }

}