#ifndef USERINTERFACE_WIDGETS_INCLUDE_PENALTY_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_PENALTY_ICON_H_

#include <QWidget>



namespace UserInterface {

    namespace Widget {

        class PenaltyFlag;
        class PenaltyTextBackground;
        class TextInterface;

        class PenaltyIcon : public QWidget {

            public:
            PenaltyIcon(QWidget* parent = 0);
            ~PenaltyIcon() = default;
            void addTimePenalty(const int32_t change);
            void addDriveThrough(const int32_t change);
            void addStopGo(const int32_t change);

            private:
            void checkDisplayStatus();
            const QString generateText();

            UserInterface::Widget::PenaltyFlag* m_flagIcon;
            UserInterface::Widget::PenaltyTextBackground* m_textBackground;
            UserInterface::Widget::TextInterface* m_text;

            // Whether this icon is active and being displayed
            bool m_active;

            // Total amount of time penalties to be served, in milliseconds
            uint32_t m_timePen;

            // Total number of drive-through penalties to be served
            uint32_t m_driveThroughs;

            // Total amount of stop-go penalties to be served
            uint32_t m_stopGos;

            static constexpr uint8_t HORIZONTAL_OFFSET = 3;
            static constexpr uint8_t VERTICAL_OFFSET = 3;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_PENALTY_ICON_H_