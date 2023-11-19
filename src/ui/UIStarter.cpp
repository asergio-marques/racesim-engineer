#include "UIStarter.h"

#include <QApplication>
#include <QGuiApplication>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMenuBar>
#include <QTimer>
#include "CustomMainWindow.h"
#include "screens/Loading.h"
#include "screens/TimeTrial.h"



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
    m_window = new UserInterface::CustomMainWindow();
    if (m_window) {

        m_window->setMinimumSize(480, 360);
        m_window->setBaseSize(1920, 1040);
        m_window->addScreen(new UserInterface::Screen::Loading);
        m_window->addScreen(new UserInterface::Screen::TimeTrial);
        
        QMenuBar* menuBar = new QMenuBar(m_window);
        if (menuBar) {
            menuBar->addMenu(QString::fromUtf8("Settings"));
            menuBar->addMenu(QString::fromUtf8("About"));
            m_window->setMenuBar(menuBar);
        }
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