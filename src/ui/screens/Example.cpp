#include "screens/Example.h"

#include <QPalette>
#include <QPixmap>
#include <QString>
#include <QWidget>




UserInterface::Screen::Example::Example(QWidget* parent) :
    QWidget(parent) {

    QPixmap background;

    background.load(":img/background/SingleScreenBG.png");
    background.scaled(QSize(3840, 2160), Qt::KeepAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    this->show();

}