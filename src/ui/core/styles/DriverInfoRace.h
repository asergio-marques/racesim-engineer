#ifndef USERINTERFACE_STYLE_INCLUDE_DRIVER_INFO_RACE_H_
#define USERINTERFACE_STYLE_INCLUDE_DRIVER_INFO_RACE_H_

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

        static inline const Value PositionFontSize = {
            Value::Type::Absolute,
            14,     // m_minValue
            22,     // m_minValuePoint
            72,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value FastestLapIconSize = {
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

        static inline const Value TeamIconSize = {
            Value::Type::Absolute,
            18,     // m_minValue
            22,     // m_minValuePoint
            88,     // m_maxValue
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

        static inline const Value TyreInfoCompoundIconSize = {
            Value::Type::Absolute,
            18,     // m_minValue
            22,     // m_minValuePoint
            88,     // m_maxValue
            100     // m_maxValuePoint
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
            46,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value PenaltyIconMaxX = {
            Value::Type::Absolute,
            44,     // m_minValue
            392,    // m_minValuePoint
            176,    // m_maxValue
            1776    // m_maxValuePoint
        };

        static inline const Value PenaltyIconMaxY = {
            Value::Type::Absolute,
            20,     // m_minValue
            22,     // m_minValuePoint
            88,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value PenaltyIconFontSize = {
            Value::Type::Absolute,
            8,      // m_minValue
            22,     // m_minValuePoint
            34,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value RetirementIconMaxX = {
            Value::Type::Absolute,
            224,    // m_minValue
            392,    // m_minValuePoint
            1126,   // m_maxValue
            1776    // m_maxValuePoint
        };

        static inline const Value RetirementIconMaxY = {
            Value::Type::Absolute,
            20,     // m_minValue
            22,     // m_minValuePoint
            92,     // m_maxValue
            100     // m_maxValuePoint
        };

        static inline const Value RetirementFontSize = {
            Value::Type::Absolute,
            10,     // m_minValue
            22,     // m_minValuePoint
            42,     // m_maxValue
            100     // m_maxValuePoint
        };

    }

}


#endif // USERINTERFACE_STYLE_INCLUDE_DRIVER_INFO_RACE_H_