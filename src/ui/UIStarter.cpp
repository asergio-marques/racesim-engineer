#include "UIStarter.h"

#include <QApplication>
#include <QGuiApplication>
#include <QFontDatabase>
#include <QMainWindow>
#include <QTimer>
#include "CustomMainWindow.h"
#include "PacketHandler.h"
#include "EventAnnouncer.h"
#include "screens/Loading.h"
#include "screens/TimeTrial.h"
#include "screens/FreePractice.h"
#include "screens/Qualifying.h"
#include "screens/Race.h"



UserInterface::UIStarter::UIStarter() :
    m_app(nullptr),
    m_window(nullptr),
    m_handler(nullptr),
    m_announcer(new UserInterface::EventAnnouncer) {



}



UserInterface::UIStarter::~UIStarter() {

    delete m_window;

}



void UserInterface::UIStarter::Init(int* argc, char*** argv, Presenter::ICompFacade* presenter) {

    m_app = new QApplication(*argc, *argv);
    QCoreApplication::setOrganizationName("Sérgio Marques");
    QCoreApplication::setApplicationName("RaceSimEngineer");
    QCoreApplication::setApplicationVersion("0.0.1 alpha");
    Q_ASSERT(m_app);

    int normal_id = QFontDatabase::addApplicationFont(":/fonts/static/Manrope-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/static/Manrope-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/static/Manrope-ExtraBold.ttf");
    QFont font = QGuiApplication::font();
    font.setFamily(QFontDatabase::applicationFontFamilies(normal_id).at(0));
    font.setStyleStrategy(QFont::StyleStrategy::PreferAntialias);
    QGuiApplication::setFont(font);
    m_window = new UserInterface::CustomMainWindow(presenter);
    m_handler = new UserInterface::PacketHandler;
    if (m_window && m_handler && m_announcer) {

        m_announcer->Init();

        // connect handler signals to main window
        m_handler->connect(m_handler, &UserInterface::PacketHandler::TimeTrialStart,
            m_window, &UserInterface::CustomMainWindow::OnTimeTrialStart);
        m_handler->connect(m_handler, &UserInterface::PacketHandler::PracticeStart,
            m_window, &UserInterface::CustomMainWindow::OnFreePracticeStart);
        m_handler->connect(m_handler, &UserInterface::PacketHandler::QualiStart,
            m_window, &UserInterface::CustomMainWindow::OnQualiStart);
        m_handler->connect(m_handler, &UserInterface::PacketHandler::RaceStart,
            m_window, &UserInterface::CustomMainWindow::OnRaceStart);
        m_handler->connect(m_handler, &UserInterface::PacketHandler::SessionEnd,
            m_window, &UserInterface::CustomMainWindow::OnSessionEnd);

        // connect handler signals to announcer
        m_handler->connect(m_handler, &UserInterface::PacketHandler::LapFinished,
            m_announcer, &UserInterface::EventAnnouncer::AnnounceFinishedLap);
        m_handler->connect(m_handler, &UserInterface::PacketHandler::TyreChanged,
            m_announcer, &UserInterface::EventAnnouncer::AnnounceTyreChanged);

        m_window->setMinimumSize(480, 360);
        m_window->setBaseSize(1920, 1040);
        m_window->addScreen(new UserInterface::Screen::Loading(m_handler, m_window));
        m_window->addScreen(new UserInterface::Screen::TimeTrial(m_handler, m_window));
        m_window->addScreen(new UserInterface::Screen::FreePractice(m_handler, m_window));
        m_window->addScreen(new UserInterface::Screen::Qualifying(m_handler, m_window));
        m_window->addScreen(new UserInterface::Screen::Race(m_handler, m_window));
        
        m_window->Startup();
        m_window->show();

        // delay the showing of the window slightly so it is properly stylized at startup
        QTimer::singleShot(50, m_window, &UserInterface::CustomMainWindow::showMaximized);

    }

}



int UserInterface::UIStarter::Run() {

    if (m_app) {

        return m_app->exec();

    }

    return 0;

}



void UserInterface::UIStarter::OnPacketBundleBroadcast(std::vector<Packet::Event::Interface*> packets) {

    for (auto packet : packets) {

        if (packet && m_handler) {

            m_handler->AcceptPacket(packet);

        }

    }

}