#ifndef USERINTERFACE_WIDGETS_INCLUDE_PENALTY_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_PENALTY_ICON_H_

#include "base/Container.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class PenaltyFlag;
        class PenaltyTextBackground;
        class TextInterface;

        class PenaltyIcon : public UserInterface::Widget::Container {

            public:
            PenaltyIcon(QWidget* parent = 0);
            ~PenaltyIcon() = default;
            void addTimePenalty(const int32_t change);
            void addDriveThrough(const int32_t change);
            void addStopGo(const int32_t change);

            private:
            void checkDisplayStatus();

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

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_PENALTY_ICON_H_