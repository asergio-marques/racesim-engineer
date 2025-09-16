#ifndef PROCESSOR_UTILITIES_ICONFIG_LOADER_H_
#define PROCESSOR_UTILITIES_ICONFIG_LOADER_H_




namespace Processor {

    namespace Utility {

        class IConfigLoader{

            public:
            IConfigLoader() = default;
            virtual ~IConfigLoader() = default;

            virtual bool readConfig() const = 0;

        }

    }

}


#endif // PROCESSOR_UTILITIES_ICONFIG_LOADER_H_