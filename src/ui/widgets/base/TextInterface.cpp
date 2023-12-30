#include "base/TextInterface.h"

#include <QGuiApplication>
#include <QLabel>
#include <QPalette>
#include <QWidget>
#include "base/ID.h"
#include "base/Interface.h"



UserInterface::Widget::TextInterface::TextInterface(UserInterface::Widget::ID id, QWidget* parent) :
    UserInterface::Widget::Interface(id),
    m_text(new QLabel(parent)) {

    if (m_text) {

        m_text->setStyleSheet("QLabel { color : white; font : Manrope }");
        m_text->update();

    }

}



void UserInterface::Widget::TextInterface::Move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    if (m_text) {

        uint16_t newX = 0;
        uint16_t newY = 0;

        if (centerAlignmentX) newX = x - (m_text->width() / 2);
        else newX = x;
        if (centerAlignmentY) newY = y - (m_text->height() / 2);
        else newY = y;
        m_text->move(newX, newY);

    }

}


void UserInterface::Widget::TextInterface::SetFontSize(const uint16_t size) {

    // TODO fix the issue where the text disappears entirely
    // if it is wider than the window itself
    if (m_text) {

        QFont font = m_text->font();
        font.setPointSize(size);
        m_text->setFont(font);
        m_text->adjustSize();

    }

}

void UserInterface::Widget::TextInterface::SetFontThickness(const UserInterface::Widget::FontThickness thickness) {

    if (m_text) {

        // TODO figure out a better way to use these fonts than to change the stylesheet everytime
        // using stuff like setBold is not working as intended
        switch (thickness) {

            case UserInterface::Widget::FontThickness::Bold:
                m_text->setStyleSheet("QLabel { color : white; font : Manrope Bold }");
                break;

            case UserInterface::Widget::FontThickness::ExtraBold:
                m_text->setStyleSheet("QLabel { color : white; font : Manrope ExtraBold }");
                break;

            // also includes the case where Regular is requested
            default:
                m_text->setStyleSheet("QLabel { color : white; font : Manrope }");
                break;

        }

    }    

}


const int16_t UserInterface::Widget::TextInterface::Width() const {

    if (m_text) {

        return m_text->width();

    }
    return 0;

}



const int16_t UserInterface::Widget::TextInterface::Height() const {

    if (m_text) {

        return m_text->height();

    }
    return 0;

}



const int16_t UserInterface::Widget::TextInterface::X() const {

    if (m_text) {

        return m_text->x();

    }

    return 0;

}



const int16_t UserInterface::Widget::TextInterface::Y() const {

    if (m_text) {
    
        return m_text->y();

    }

    return 0;

}



void UserInterface::Widget::TextInterface::SetText(const QString& text) {

    if (m_text) {

        m_text->setText(text);

    }

}



void UserInterface::Widget::TextInterface::SetText(const std::string& text) {

    if (m_text) {

        const QString tempText = QString::fromUtf8(text);
        this->SetText(tempText);

    }

}



void UserInterface::Widget::TextInterface::SetText(const char* text) {

    if (m_text) {

        const QString tempText = QString::fromUtf8(text);
        this->SetText(tempText);

    }

}