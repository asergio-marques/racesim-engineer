#ifndef USERINTERFACE_WIDGETS_INCLUDE_WEATHER_GRAPH_H_
#define USERINTERFACE_WIDGETS_INCLUDE_WEATHER_GRAPH_H_

#include "base/Container.h"




class QChart;
class QChartView;
class QWidget;

namespace UserInterface {

    namespace Widget {

        class WeatherGraph : public UserInterface::Widget::Container {

            public:
            WeatherGraph(QWidget* parent = 0);
            ~WeatherGraph() = default;
            void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY);
            void scale(const uint8_t percent) override;
            void scale(const uint8_t percentX, const uint8_t percentY) override;
            void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) override;
            void raise() override;
            void lower() override;

            // Getters
            const int16_t width() const override;
            const int16_t height() const override;
            const int16_t x() const override;
            const int16_t y() const override;

            private:
            QChart* m_chart;
            QChartView* m_chartView;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_WEATHER_GRAPH_H_   