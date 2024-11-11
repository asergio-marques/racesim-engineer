#include "UIStarter.h"

#include <QApplication>
#include <QGuiApplication>
#include <QFontDatabase>
#include <QMainWindow>
#include <QTimer>
#include "CustomMainWindow.h"
#include "PacketHandler.h"
#include "screens/Loading.h"
#include "screens/TimeTrial.h"
#include "screens/FreePractice.h"
#include "screens/Qualifying.h"
#include "screens/Race.h"



UserInterface::UIStarter::UIStarter() :
    m_app(nullptr),
    m_window(nullptr),
    m_handler(new UserInterface::PacketHandler) {



}



UserInterface::UIStarter::~UIStarter() {

    delete m_window;

}



void UserInterface::UIStarter::Init(int* argc, char*** argv, IPresenter* presenter) {

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
    if (m_window && m_handler) {

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



void UserInterface::UIStarter::OnPacketBroadcast(Packet::Internal::Interface* packet) {

    if (packet && m_handler) {

        m_handler->AcceptPacket(packet);

    }

}