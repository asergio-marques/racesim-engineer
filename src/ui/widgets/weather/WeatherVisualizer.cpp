#include "weather/WeatherVisualizer.h"

#include <QWidget>
#include "base/Container.h"
#include "base/ID.h"
#include "weather/WeatherGraph.h"




UserInterface::Widget::WeatherVisualizer::WeatherVisualizer(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::WeatherInfo),
    m_selector(nullptr),
    m_detailsPanel(nullptr),
    m_weatherGraph(nullptr) {

    m_weatherGraph = new UserInterface::Widget::WeatherGraph(parent);
    if (m_weatherGraph) {

        m_weatherGraph->setSize(400, 400, false);
        m_weatherGraph->move(0, 0, false, false);

    }

}



void UserInterface::Widget::WeatherVisualizer::move(const uint16_t x, const uint16_t y,
    const bool centerAlignmentX, const bool centerAlignmentY) {

    m_x = x;
    m_y = y;
    if (m_weatherGraph) {

        m_weatherGraph->move(m_x, m_y, centerAlignmentX, centerAlignmentY);

    }

}



void UserInterface::Widget::WeatherVisualizer::scale(const uint8_t percent) {



}



void UserInterface::Widget::WeatherVisualizer::scale(const uint8_t percentX, const uint8_t percentY) {



}



void UserInterface::Widget::WeatherVisualizer::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    m_width = newWidth;
    m_height = newHeight;

    if (m_weatherGraph) {

        m_weatherGraph->setSize(m_width, m_height, keepAspectRatio);

    }


}



void UserInterface::Widget::WeatherVisualizer::raise() {



}



void UserInterface::Widget::WeatherVisualizer::lower() {



}



const int16_t UserInterface::Widget::WeatherVisualizer::width() const {

    return m_width;

}



const int16_t UserInterface::Widget::WeatherVisualizer::height() const {

    return m_height;

}



const int16_t UserInterface::Widget::WeatherVisualizer::x() const {

    return m_x;

}



const int16_t UserInterface::Widget::WeatherVisualizer::y() const {

    return m_y;

}