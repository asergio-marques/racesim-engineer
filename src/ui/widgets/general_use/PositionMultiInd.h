#ifndef USERINTERFACE_WIDGETS_INCLUDE_POSITION_MULTI_IND_H_
#define USERINTERFACE_WIDGETS_INCLUDE_POSITION_MULTI_IND_H_

#include <QWidget>



namespace UserInterface {

    namespace Widget {

        class FastestLapIndicator;
        class TextInterface;
        class WarningContainer;

        class PositionMultiIndicator : public QWidget {

            Q_OBJECT

            public:
            PositionMultiIndicator(QWidget* parent = 0);
            ~PositionMultiIndicator() = default;
            void init(const uint8_t& initPosition);
            void updatePosition(const uint8_t newPosition);
            void updateWarnings(bool isTrackLim, const int32_t change);
            void sessionBestChange(bool gainOrLoss);
            const uint8_t getCurrentPosition() const;

            private:
            UserInterface::Widget::TextInterface* m_position;
            UserInterface::Widget::WarningContainer* m_trackLimWarn;
            UserInterface::Widget::WarningContainer* m_otherWarn;
            UserInterface::Widget::FastestLapIndicator* m_fastestLap;

            uint8_t m_currentPosition;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_POSITION_MULTI_IND_H_