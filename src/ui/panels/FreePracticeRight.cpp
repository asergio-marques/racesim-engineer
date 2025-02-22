#include "panels/FreePracticeRight.h"

#include <QSize>
#include <QWidget>
#include "panels/Interface.h"
#include "widgets/general_use/BackgroundRight.h"
#include "widgets/general_use/ScreenTitle.h"


UserInterface::Panel::FreePracticeRight::FreePracticeRight(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent) {
        
    m_background = new UserInterface::Widget::BackgroundRight(this);
    Q_ASSERT(m_background);
    if (m_background) {

        m_background->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    }

}



void UserInterface::Panel::FreePracticeRight::ResizePanel(const QSize& newPanelSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newPanelSize);

}