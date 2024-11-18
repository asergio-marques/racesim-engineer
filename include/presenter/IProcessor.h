#ifndef PRESENTER_INCLUDE_IPROCESSOR_H_
#define PRESENTER_INCLUDE_IPROCESSOR_H_

#include <QString>



namespace Presenter {

    class IProcessor {

        public:
        IProcessor() = default;
        virtual ~IProcessor() = default;
        virtual bool exportRaceToFolder(QString folderPath) = 0;

    };

}

#endif // PRESENTER_INCLUDE_IPROCESSOR_H_