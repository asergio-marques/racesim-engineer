#ifndef PRESENTER_INCLUDE_PRESENTER_H_
#define PRESENTER_INCLUDE_PRESENTER_H_

#include <QString>
#include "IPresenter.h"



namespace Processor {

    class IFacade;

}

class Presenter : public IPresenter {

    public:
    Presenter() = default;
    virtual ~Presenter() override = default;
    virtual void setProcessor(Processor::IFacade* processor) override;
    virtual bool exportRaceToFolder(QString folderPath) override;

    private:
    Processor::IFacade* m_processor;
};

#endif // PRESENTER_INCLUDE_PRESENTER_H_