#include "StyleSheetFactory.h"

#include <QString>



UserInterface::StyleSheetFactory* UserInterface::StyleSheetFactory::m_instance = new UserInterface::StyleSheetFactory;

UserInterface::StyleSheetFactory* UserInterface::StyleSheetFactory::instance() {

    return m_instance;

}




QString UserInterface::StyleSheetFactory::requestByColorAndThickness(UserInterface::StyleSheetFactory::FontThickness boldness,
    UserInterface::StyleSheetFactory::FontColor color) const {

    QString styleString, color, font = "";
    switch (boldness) {

        case Bold:
            font = "Manrope Bold";
            break;

        case ExtraBold:
            font = "Manrope ExtraBold";
            break;

        // also includes the case where Regular is requested
        default:
            font = "Manrope";
            break;

    }
    // no colors aside from white available atm
    color = "white";
    styleString = "QLabel { color : " + color + "; font: " + font + " }";
    return styleString;

}