#ifndef NETCOM_INCLUDE_FACADE_H_
#define NETCOM_INCLUDE_FACADE_H_



namespace Packet {

    namespace Game {

        class Broadcaster;

    }
    namespace Internal {

        class Broadcaster;

    }

}

namespace NetCom {

    namespace Listener {
        
        class Director;

    }

    namespace Converter {
    
        class PacketGeneralizer;
    
    }

    namespace Adapter {

        class Interface;

    }

    class Facade {

        public:
            Facade();
            virtual ~Facade();
            void Init();
            Packet::Internal::Broadcaster* exposeBroadcasterInterface() const;

        private:
            NetCom::Listener::Director* m_director;
            NetCom::Converter::PacketGeneralizer* m_packetGeneralizer;
            NetCom::Adapter::Interface* m_gameAdapter;


    };

}

#endif // PROCESSOR_INCLUDE_FACADE_H_