#include "multiplayer_session/sectors/SectorTimeText.h"

#include "base/TextInterface.h"
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




UserInterface::Widget::SectorTimeText::SectorTimeText(UserInterface::Widget::ID id, QWidget* parent) :
    UserInterface::Widget::TextInterface(id, parent) {



}



void UserInterface::Widget::SectorTimeText::setTextAndColor(const Lap::Internal::Time& time, Lap::Internal::Performance perf) {

    switch (perf) {

        case Lap::Internal::Performance::CurrentlyRunning:
        case Lap::Internal::Performance::CurrentlyRunningPits:
        case Lap::Internal::Performance::CurrentlyRunningInvalid:
            setStyleSheet("QLabel { color : white; font : Manrope }");
            setText("IN SECTOR");
            break;

        case Lap::Internal::Performance::FinishedNormal:
        case Lap::Internal::Performance::FinishedInvalid:
            // show "FinishedNotImprovement" color
            setStyleSheet("QLabel { color : rgb(234, 235, 0); font : Manrope }");
            setText(time.formattedPrint(true));
            break;

        case Lap::Internal::Performance::FinishedPits:
            // show "FinishedInPits" color
            setStyleSheet("QLabel { color : rgb(85, 161, 255); font : Manrope }");
            setText(time.formattedPrint(true));
            break;

        case Lap::Internal::Performance::FinishedPersonalBest:
            // show "FinishedPersonalBest" color
            setStyleSheet("QLabel { color : rgb(37, 183, 39); font : Manrope }");
            setText(time.formattedPrint(true));
            break;

        case Lap::Internal::Performance::FinishedSessionBest:
            // show "FinishedSessionBest" color
            setStyleSheet("QLabel { color : rgb(140, 37, 183); font : Manrope }");
            setText(time.formattedPrint(true));
            break;

        case Lap::Internal::Performance::FinishedRetired:
            // show "FinishedRetirementComplete" color
            setStyleSheet("QLabel { color : rgb(212, 44, 44); font : Manrope }");
            setText("RETIRED");
            break;

        default:
            // only missing value is NotRun, which is returned from at function entry
            break;

    }

}