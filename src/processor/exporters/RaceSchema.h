#ifndef PROCESSOR_EXPORTER_INCLUDE_RACE_SCHEMA_H_
#define PROCESSOR_EXPORTER_INCLUDE_RACE_SCHEMA_H_


namespace Processor {

    namespace Exporter {

        namespace RaceSchema {

            struct v1 {

                // General session info
                static constexpr char* versionTag = "schemaVersion";
                static constexpr char* version = "1";
                static constexpr char* lapTimeSecTag = "sec";
                static constexpr char* lapTimeMSecTag = "msec";
                static constexpr char* trackIdTag = "trackId";
                static constexpr char* trackNameTag = "trackName";
                static constexpr char* numLapsTag = "numLaps";
                static constexpr char* fastestOverallTag = "fastestOverallLap";
                static constexpr char* completionTag = "completion";
                static constexpr char* gridPosTag = "gridPosition";
                static constexpr char* finishPosTag = "finishPosition";

                // Lap data
                static constexpr char* lapIdTag = "id";
                static constexpr char* lapTimeTag = "totalLapTime";
                static constexpr char* sector1TimeTag = "sector1Time";
                static constexpr char* sector2TimeTag = "sector2Time";
                static constexpr char* sector3TimeTag = "sector3Time";
                // unused for now
                static constexpr char* tyreVisualTag = "tyreType";
                static constexpr char* tyreCompoundTag = "tyreCompound";
                static constexpr char* energyDeltaTag = "energyDeltaJ";
                static constexpr char* energyRechargeTag = "energyRechargedJ";
                static constexpr char* energyAllowanceTag = "energyAllowanceUnusedJ";
                static constexpr char* fuelDeltaTag = "fuelDeltaKg";
                static constexpr char* drsActTag = "numDRSAct";
                static constexpr char* trackCondTag = "trackConditions";
                static constexpr char* timeDeltaLeaderTag = "deltaLeaderAtEnd";
                static constexpr char* timeDeltaFrontTag = "deltaFrontAtEnd";
                static constexpr char* timeDeltaBehindTag = "deltaBehindAtEnd";
                static constexpr char* lapPosTag = "positionAtEnd";
                static constexpr char* numTrackLimTag = "trackLimits";
                static constexpr char* numOtherWarnTag = "otherWarns";
                static constexpr char* numLapTimePensTag = "timePensLap";
                static constexpr char* numTotalTimePensTag = "timePensTotal";
                static constexpr char* numLapDTTag = "driveThroughLap";
                static constexpr char* numTotalDTTag = "driveThroughTotal";
                static constexpr char* otherTag = "other";
            };

        };

    }

}


#endif // PROCESSOR_EXPORTER_INCLUDE_RACE_SCHEMA_H_