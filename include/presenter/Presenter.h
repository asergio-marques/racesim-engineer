#ifndef PRESENTER_INCLUDE_PRESENTER_H_
#define PRESENTER_INCLUDE_PRESENTER_H_

#include "IPresenter.h"



class Presenter : public IPresenter {

    public:
    Presenter() = default;
    virtual ~Presenter() override = default;

};

#endif // PRESENTER_INCLUDE_PRESENTER_H_