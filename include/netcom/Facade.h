#ifndef NETCOM_INCLUDE_FACADE_H_
#define NETCOM_INCLUDE_FACADE_H_



namespace Packet {

    namespace Game {

        class Broadcaster;

    }

}

namespace Presenter {

    class ICompFacade;

}

namespace NetCom {

    namespace Listener {
        
        class Director;

    }

    namespace Adapter {

        class Interface;

    }

    class Facade {

        public:
            Facade();
            virtual ~Facade();
            void Init(Presenter::ICompFacade* presenter);
            Packet::Game::Broadcaster* exposeBroadcasterInterface() const;

        private:
            NetCom::Listener::Director* m_director;
            NetCom::Adapter::Interface* m_gameAdapter;
            Presenter::ICompFacade* m_presenter;


    };

}

#endif // PROCESSOR_INCLUDE_FACADE_H_