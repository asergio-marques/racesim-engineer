#ifndef PROCESSOR_EXPORTER_INCLUDE_RACE_SCHEMA_H_
#define PROCESSOR_EXPORTER_INCLUDE_RACE_SCHEMA_H_



namespace Processor {

    namespace Exporter {

        namespace RaceSchema {

            struct v1 {

                // General session info
                static const constexpr char* versionTag = "schemaVersion";
                static const constexpr char* version = "1";
                static const constexpr char* lapTimeSecTag = "sec";
                static const constexpr char* lapTimeMSecTag = "msec";
                static const constexpr char* trackIdTag = "trackId";
                static const constexpr char* trackNameTag = "trackName";
                static const constexpr char* numLapsTag = "numLaps";
                static const constexpr char* fastestOverallTag = "fastestOverallLap";
                static const constexpr char* completionTag = "completion";
                static const constexpr char* gridPosTag = "gridPosition";
                static const constexpr char* finishPosTag = "finishPosition";

                // Lap data
                static const constexpr char* lapIdTag = "id";
                static const constexpr char* lapTimeTag = "totalLapTime";
                static const constexpr char* sector1TimeTag = "sector1Time";
                static const constexpr char* sector2TimeTag = "sector2Time";
                static const constexpr char* sector3TimeTag = "sector3Time";
                // unused for now
                static const constexpr char* tyreVisualTag = "tyreType";
                static const constexpr char* tyreCompoundTag = "tyreCompound";
                static const constexpr char* energyDeltaTag = "energyDeltaJ";
                static const constexpr char* energyRechargeTag = "energyRechargedJ";
                static const constexpr char* energyAllowanceTag = "energyAllowanceUnusedJ";
                static const constexpr char* fuelDeltaTag = "fuelDeltaKg";
                static const constexpr char* drsActTag = "numDRSAct";
                static const constexpr char* trackCondTag = "trackConditions";
                static const constexpr char* timeDeltaLeaderTag = "deltaLeaderAtEnd";
                static const constexpr char* timeDeltaFrontTag = "deltaFrontAtEnd";
                static const constexpr char* timeDeltaBehindTag = "deltaBehindAtEnd";
                static const constexpr char* lapPosTag = "positionAtEnd";
                static const constexpr char* numTrackLimTag = "trackLimits";
                static const constexpr char* numOtherWarnTag = "otherWarns";
                static const constexpr char* numLapTimePensTag = "timePensLap";
                static const constexpr char* numTotalTimePensTag = "timePensTotal";
                static const constexpr char* numLapDTTag = "driveThroughLap";
                static const constexpr char* numTotalDTTag = "driveThroughTotal";
                static const constexpr char* otherTag = "other";
            };

        };

    }

}


#endif // PROCESSOR_EXPORTER_INCLUDE_RACE_SCHEMA_H_