#ifndef SETTINGS_INCLUDE_SCHEMA_H_
#define SETTINGS_INCLUDE_SCHEMA_H_



namespace Settings {

    namespace Schema {

        struct v1 {

            static const constexpr char* versionTag = "schemaVersion";
            static const constexpr char* gameTag = "game";
            static const constexpr char* windowNumTag = "numWindows";
            static const constexpr char* portTag = "port";
            static const constexpr char* autoExportTag = "autoExport";
             
        };

    }

}
#endif // SETTINGS_INCLUDE_SCHEMA_H_