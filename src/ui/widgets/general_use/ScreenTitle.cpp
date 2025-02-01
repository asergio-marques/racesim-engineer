#include "general_use/ScreenTitle.h"

#include <QLabel>
#include <QWidget>
#include "ScreenType.h"
#include "StyleSheetFactory.h"




UserInterface::Widget::ScreenTitle::ScreenTitle(QWidget* parent) :
    QLabel(parent) {

    UserInterface::StyleSheetFactory* instance = UserInterface::StyleSheetFactory::instance();
    Q_ASSERT(instance);
    if (instance) {

        setStyleSheet(instance->requestByColorAndThickness(UserInterface::StyleSheetFactory::FontThickness::ExtraBold));

    }

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