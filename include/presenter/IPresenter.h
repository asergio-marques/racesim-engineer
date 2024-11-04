#ifndef PRESENTER_INCLUDE_IPRESENTER_H_
#define PRESENTER_INCLUDE_IPRESENTER_H_


#include <QString>

class IPresenter {

    public:
    IPresenter() = default;
    virtual ~IPresenter() = default;
    virtual void exportRaceToFolder(QString folderPath) = 0;

};

#endif // PRESENTER_INCLUDE_IPRESENTER_H_