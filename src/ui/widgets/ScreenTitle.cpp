#include "widgets/ScreenTitle.h"

#include <QFont>
#include <QFontDatabase>
#include <QLabel>
#include <QString>
#include <QWidget>
#include "base/elements/TextElement.h"
#include "base/ScreenType.h"
#include "base/WidgetId.h"




UserInterface::Widget::ScreenTitle::ScreenTitle(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::TextElement(id, parent) {

    this->SetFontThickness(UserInterface::Base::FontThickness::Bold);

}



bool UserInterface::Widget::ScreenTitle::Update() {
    
    return true;

}



void UserInterface::Widget::ScreenTitle::SetTitle(UserInterface::Base::ScreenType type) {

    switch (type) {

        case UserInterface::Base::ScreenType::Loading:
            this->SetText("Waiting for a session to start...");
            break;

        case UserInterface::Base::ScreenType::TimeTrial:
            this->SetText("Time Trial");
            break;

        case UserInterface::Base::ScreenType::FreePractice:
            this->SetText("Practice");
            break;

        case UserInterface::Base::ScreenType::Qualification:
            this->SetText("Quali");
            break;

        case UserInterface::Base::ScreenType::Race:
            this->SetText("Race");
            break;

        default:
            this->SetText("N/A");
            break;

    }

}