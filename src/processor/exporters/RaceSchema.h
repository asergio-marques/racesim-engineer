#ifndef PROCESSOR_EXPORTER_INCLUDE_RACE_SCHEMA_H_
#define PROCESSOR_EXPORTER_INCLUDE_RACE_SCHEMA_H_


namespace Processor {

    namespace Exporter {

        namespace RaceSchema {

            struct v1 {

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

            };

        };

    }

}


#endif // PROCESSOR_EXPORTER_INCLUDE_RACE_SCHEMA_H_