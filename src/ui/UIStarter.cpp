#include "UIStarter.h"

#include <QApplication>
#include <QGuiApplication>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMenuBar>
#include "screens/Loading.h"



UserInterface::UIStarter::~UIStarter() {

    delete m_window;

}



void UserInterface::UIStarter::Init(int* argc, char*** argv) {

    //Q_INIT_RESOURCE(application);
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationName("Application Example");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    m_app = new QApplication(*argc, *argv);
    Q_ASSERT(m_app);

    int normal_id = QFontDatabase::addApplicationFont(":/fonts/static/Manrope-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/static/Manrope-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/static/Manrope-ExtraBold.ttf");
    QFont font = QGuiApplication::font();
    font.setFamily(QFontDatabase::applicationFontFamilies(normal_id).at(0));
    font.setStyleStrategy(QFont::StyleStrategy::PreferAntialias);
    QGuiApplication::setFont(font);
    m_window = new QMainWindow();
    if (m_window) {

        m_window->setMinimumSize(1366, 768);

        m_screen = new UserInterface::Screen::Loading(m_window);
        if (m_screen) {
            m_screen->Initialize();
            m_window->setCentralWidget(m_screen);
            QMenuBar* menuBar = new QMenuBar(m_window);
            menuBar->addMenu(QString::fromUtf8("Settings"));
            menuBar->addMenu(QString::fromUtf8("About"));
            m_window->setMenuBar(menuBar);
            m_window->show();
        
        }

    }

}



int UserInterface::UIStarter::Run() {

    if (m_app) {

        return m_app->exec();

    }

    return 0;

}