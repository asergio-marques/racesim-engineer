#ifndef PRESENTER_INCLUDE_IPRESENTER_H_
#define PRESENTER_INCLUDE_IPRESENTER_H_



class QString;

namespace Processor {

    class IFacade;

}

namespace Processor {

    class IFacade;

}

class IPresenter {

    public:
    IPresenter() = default;
    virtual ~IPresenter() = default;
    virtual void setProcessor(Processor::IFacade* processor) = 0;
    virtual bool exportRaceToFolder(QString folderPath) = 0;

};

#endif // PRESENTER_INCLUDE_IPRESENTER_H_