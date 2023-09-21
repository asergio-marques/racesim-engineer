#ifndef NETCOM_LISTENER_INCLUDE_DIRECTOR_H_
#define NETCOM_LISTENER_INCLUDE_DIRECTOR_H_

class QUdpSocket;

namespace F1_23::Listener {

    class Director {
    
        public:
            Director();
            ~Director();

        private:
            QUdpSocket* socket;
    
    };

};

#endif // NETCOM_LISTENER_INCLUDE_DIRECTOR_H_