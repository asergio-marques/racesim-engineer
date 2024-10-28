#ifndef PROCESSOR_INCLUDE_FILEIO_H_
#define PROCESSOR_INCLUDE_FILEIO_H_

#include "IFileIO.h"


namespace Processor {

    class FileIO final : public Processor::IFileIO {

        public:
            // Constructor
            FileIO();

            // Destructor
            virtual ~FileIO();

    };

}

#endif // PROCESSOR_INCLUDE_FILEIO_H_