#ifndef USERINTERFACE_STYLE_INCLUDE_DRIVER_INFO_H_
#define USERINTERFACE_STYLE_INCLUDE_DRIVER_INFO_H_

#include <cstdint>
#include <math.h>
#include "styles/Value.h"




namespace UserInterface {

    namespace Style {

        // references:
        // 92.5% of 424px (half of minimum width 848px) = 392px
        // 92.5% of 1920px (half of supported maximum width 3860px) = 1776px
        static inline const float_t StandingsWidthRelative = 0.925f;

        // references:
        // 92.5% of 480px = 444px (~22px per entry for 20 total)
        // 92.5% of 2160px = 1998px (~100px per entry for 20 total)
        // TODO references should be 22 total not 20!
        static inline const float_t StandingsHeightRelative = 0.925f;

        static inline const Value RowHeight = {
            Value::Type::Absolute,
            18,     // m_minValue
            22,     // m_minValuePoint
            88,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value WarningIconSize = {
            Value::Type::Absolute,
            8,     // m_minValue
            22,     // m_minValuePoint
            38,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value WarningNumFontSize = {
            Value::Type::Absolute,
            6,     // m_minValue
            22,     // m_minValuePoint
            32,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value PositionFontSize = {
            Value::Type::Absolute,
            14,     // m_minValue
            22,     // m_minValuePoint
            72,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value DriverNameMaximumWidth = {
            Value::Type::Absolute,
            44,     // m_minValue
            392,    // m_minValuePoint
            188,    // m_maxValue
            1776    // m_maxValuePoint
        };

        static inline const Value DriverNameFontSize = {
            Value::Type::Absolute,
            12,     // m_minValue
            22,     // m_minValuePoint
            60,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value LapInfoLabelFontSize = {
            Value::Type::Absolute,
            4,      // m_minValue
            22,     // m_minValuePoint
            20,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const uint8_t LapInfoTimeRelativeOfLabelFontSize = 125;

        static inline const Value LapInfoBackgroundMaxX = {
            Value::Type::Absolute,
            66,     // m_minValue
            392,    // m_minValuePoint
            198,    // m_maxValue
            1776    // m_maxValuePoint
        };

        static inline const Value LapInfoBackgroundMaxY = {
            Value::Type::Absolute,
            8,     // m_minValue
            22,     // m_minValuePoint
            38,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const uint8_t TyreInfoContainerMaxNum = 3;

        static inline const Value TyreInfoContainerMaxX = {
            Value::Type::Absolute,
            40,     // m_minValue
            392,    // m_minValuePoint
            200,    // m_maxValue
            1776    // m_maxValuePoint
        };

        static inline const Value TyreInfoCompoundFontSize = {
            Value::Type::Absolute,
            8,      // m_minValue
            22,     // m_minValuePoint
            34,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value TyreInfoAgeFontSize = {
            Value::Type::Absolute,
            11,     // m_minValue
            22,     // m_minValuePoint
            54,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value TyreInfoStintNoFontSize = {
            Value::Type::Absolute,
            4,      // m_minValue
            22,     // m_minValuePoint
            20,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value TyreInfoStintNoGapFromBottom = {
            Value::Type::Absolute,
            2,      // m_minValue
            22,     // m_minValuePoint
            12,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value PenaltyIconMaxX = {
            Value::Type::Absolute,
            36,     // m_minValue
            392,    // m_minValuePoint
            152,    // m_maxValue
            1776    // m_maxValuePoint
        };

        static inline const Value PenaltyIconFontSize = {
            Value::Type::Absolute,
            8,      // m_minValue
            22,     // m_minValuePoint
            34,     // m_maxValue
            100     // m_maxValuePoint
        };

        // TODO it might be necessary to support more than 3 sectors with other games (e.g. iRacing)
        static inline const uint8_t SectorInfoContainerMaxNum = 3;

        static inline const Value SectorInfoContainerMaxX = {
            Value::Type::Absolute,
            44,     // m_minValue
            392,    // m_minValuePoint
            216,    // m_maxValue
            1776    // m_maxValuePoint
        };

        static inline const Value SectorTimeStatusFontSize = {
            Value::Type::Absolute,
            6,      // m_minValue
            22,     // m_minValuePoint
            30,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const uint8_t MiniSectorIconSpacingX = 2;

    }

}


#endif // USERINTERFACE_STYLE_INCLUDE_DRIVER_INFO_H_