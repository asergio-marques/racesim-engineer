#ifndef PRESENTER_INCLUDE_ICOMP_FACADE_H_
#define PRESENTER_INCLUDE_ICOMP_FACADE_H_



class QString;

namespace NetCom {

    class IFacade;

}

namespace Processor {

    class IFacade;

}

namespace Settings {

    class IStore;

}

namespace Presenter {

    class ICompFacade {

        public:
        ICompFacade() = default;
        virtual ~ICompFacade() = default;
        virtual void setProcessor(Processor::IFacade* processor) = 0;
        virtual void setSettingsStore(Settings::IStore* settings) = 0;
        virtual void setNetCom(NetCom::IFacade* netCom) = 0;

    };

}

#endif // PRESENTER_INCLUDE_ICOMP_FACADE_H_