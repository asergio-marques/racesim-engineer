#include "multiplayer_session/sectors/SectorTimeText.h"

#include "base/TextInterface.h"
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




UserInterface::Widget::SectorTimeText::SectorTimeText(UserInterface::Widget::ID id, QWidget* parent) :
    UserInterface::Widget::TextInterface(id, parent),
    m_toolTipText() {

    setToolTipDuration(-1);

}



void UserInterface::Widget::SectorTimeText::setTextAndColor(const Lap::Internal::Time& time, Lap::Internal::Performance perf, const uint8_t lapID) {

    switch (perf) {

        case Lap::Internal::Performance::NotRun:
            // clear text
            setText("");
            break;

        case Lap::Internal::Performance::CurrentlyRunning:
        case Lap::Internal::Performance::CurrentlyRunningPits:
        case Lap::Internal::Performance::CurrentlyRunningInvalid:
            m_currentColorString = "color : white";
            setText("IN SECTOR");
            break;

        case Lap::Internal::Performance::FinishedNormal:
        case Lap::Internal::Performance::FinishedInvalid:

            if (time.valid()) {
                // show "FinishedNotImprovement" color
                m_currentColorString = "color : rgb(234, 235, 0)";
                setText(time.formattedPrint(true));

            }
            else {

                m_currentColorString = "color : white";
                setText("N/A");

            }
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedPits:

            if (time.valid()) {

                // show "FinishedInPits" color
                m_currentColorString = "color : rgb(102, 170, 255)";
                setText(time.formattedPrint(true));

            }
            else {

                m_currentColorString = "color : white";
                setText("N/A");

            }
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedPersonalBest:
            if (time.valid()) {

                // show "FinishedPersonalBest" color
                m_currentColorString = "color : rgb(37, 183, 39)";
                setText(time.formattedPrint(true));

            }
            else {

                m_currentColorString = "color : white";
                setText("N/A");

            }
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedSessionBest:
            if (time.valid()) {

                // show "FinishedSessionBest" color
                m_currentColorString = "color : rgb(140, 37, 183)";
                setText(time.formattedPrint(true));

            }
            else {

                m_currentColorString = "color : white";
                setText("N/A");

            }
            appendTooltipText(time, lapID);
            break;

        case Lap::Internal::Performance::FinishedRetired:
            // show "FinishedRetirementComplete" color
            m_currentColorString = "color : rgb(212, 44, 44)";
            setText("RETIRED");
            appendTooltipText(0, lapID);
            break;

        default:
            // only missing value is NotRun, which is returned from at function entry
            break;

    }

    updateFont();

}



void UserInterface::Widget::SectorTimeText::appendTooltipText(const Lap::Internal::Time& time, const uint8_t lapID) {

    if (time.valid()) {

        m_toolTipText += "Lap " + QString::number(lapID) + " - " + QString::fromStdString(time.formattedPrint(true)) + "\n";

    }
    else {

        m_toolTipText += "Lap " + QString::number(lapID) + " - N/A\n";

    }

    setToolTip(m_toolTipText);

}