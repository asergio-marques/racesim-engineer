#include "weather/WeatherGraph.h"

#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include "base/Container.h"
#include "base/ID.h"
#include "weather/WeatherGraph.h"




UserInterface::Widget::WeatherGraph::WeatherGraph(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::WeatherInfo),
    m_chart(nullptr),
    m_chartView(nullptr) {

    // Lower and upper boundary series
    QLineSeries* lowerSeries = new QLineSeries();
    QLineSeries* upperSeries = new QLineSeries();

    for (int i = 0; i <= 10; ++i) {
        qreal x = i;
        qreal y1 = qSin(x / 2.0);
        qreal y2 = y1 + 0.5;
        lowerSeries->append(x, y1);
        upperSeries->append(x, y2);
    }

    // Create area series
    QAreaSeries* areaSeries = new QAreaSeries(upperSeries, lowerSeries);
    areaSeries->setName("Sine Band");
    areaSeries->setColor(QColor(100, 150, 255, 100)); // translucent fill

    // Create chart
    m_chart = new QChart();
    m_chart->addSeries(areaSeries);
    m_chart->setTitle("2D Area Chart with QtCharts");
    m_chart->createDefaultAxes();

    // Optional: customize axes
    QValueAxis* axisX = new QValueAxis();
    axisX->setTitleText("X Axis");
    axisX->setRange(0, 10);
    m_chart->setAxisX(axisX, areaSeries);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Y Axis");
    axisY->setRange(-1.5, 2.0);
    m_chart->setAxisY(axisY, areaSeries);

    // Chart view
    m_chartView = new QChartView(m_chart);
    m_chartView->setParent(parent);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->show();

}



void UserInterface::Widget::WeatherGraph::move(const uint16_t x, const uint16_t y,
    const bool centerAlignmentX, const bool centerAlignmentY) {

    m_x = x;
    m_y = y;
    if (m_chartView) {

        m_chartView->move(m_x, m_y);

    }

}



void UserInterface::Widget::WeatherGraph::scale(const uint8_t percent) {



}



void UserInterface::Widget::WeatherGraph::scale(const uint8_t percentX, const uint8_t percentY) {



}



void UserInterface::Widget::WeatherGraph::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    m_width = newWidth;
    m_height = newHeight;

    if (m_chartView) {

        m_chartView->setFixedSize(m_width, m_height);

    }


}



void UserInterface::Widget::WeatherGraph::raise() {



}



void UserInterface::Widget::WeatherGraph::lower() {



}



const int16_t UserInterface::Widget::WeatherGraph::width() const {

    return m_width;

}



const int16_t UserInterface::Widget::WeatherGraph::height() const {

    return m_height;

}



const int16_t UserInterface::Widget::WeatherGraph::x() const {

    return m_x;

}



const int16_t UserInterface::Widget::WeatherGraph::y() const {

    return m_y;

}