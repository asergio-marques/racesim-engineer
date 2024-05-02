#include "base/TextInterface.h"

#include <QFont>
#include <QFontMetrics>
#include <QGuiApplication>
#include <QLabel>
#include <QPalette>
#include <QWidget>
#include "base/ID.h"
#include "base/Interface.h"



UserInterface::Widget::TextInterface::TextInterface(UserInterface::Widget::ID id, QWidget* parent) :
    QLabel(parent),
    UserInterface::Widget::Interface(id) {

    setStyleSheet("QLabel { color : white; font : Manrope }");
    update();

}



void UserInterface::Widget::TextInterface::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    uint16_t newX = 0;
    uint16_t newY = 0;

    if (centerAlignmentX) newX = x - (width() / 2);
    else newX = x;
    if (centerAlignmentY) newY = y - (height() / 2);
    else newY = y;
    QLabel::move(newX, newY);

}



void UserInterface::Widget::TextInterface::setText(const QString& text) {

    QLabel::setText(text);
    adjustSize();

}



void UserInterface::Widget::TextInterface::setText(const std::string& text) {

    const QString tempText = QString::fromUtf8(text);
    QLabel::setText(tempText);
    adjustSize();

}



void UserInterface::Widget::TextInterface::setText(const char* text) {

    const QString tempText = QString::fromUtf8(text);
    QLabel::setText(tempText);
    adjustSize();

}


void UserInterface::Widget::TextInterface::setFontSize(const uint16_t size) {


    // TODO fix the issue where the text disappears entirely
    // if it is wider than the window itself
    QFont font = QLabel::font();
    font.setPointSize(size);
    setFont(font);
    adjustSize();

}




void UserInterface::Widget::TextInterface::setFontThickness(const UserInterface::Widget::FontThickness thickness) {

    // TODO figure out a better way to use these fonts than to change the stylesheet everytime
    // using stuff like setBold is not working as intended
    switch (thickness) {

        case UserInterface::Widget::FontThickness::Bold:
            setStyleSheet("QLabel { color : white; font : Manrope Bold }");
            break;

        case UserInterface::Widget::FontThickness::ExtraBold:
            setStyleSheet("QLabel { color : white; font : Manrope ExtraBold }");
            break;

        // also includes the case where Regular is requested
        default:
            setStyleSheet("QLabel { color : white; font : Manrope }");
            break;

    }

}



const uint16_t UserInterface::Widget::TextInterface::getTextWidth() const {

    QFontMetrics fm(font());
    return fm.horizontalAdvance(text());

}



const uint16_t UserInterface::Widget::TextInterface::getTextHeight() const {

    QFontMetrics fm(font());
    return fm.height();

}