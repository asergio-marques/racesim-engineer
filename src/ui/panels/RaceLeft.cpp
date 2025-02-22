#include "panels/RaceLeft.h"

#include <QSize>
#include <QWidget>
#include "panels/Interface.h"
#include "core/ScreenType.h"
#include "styles/General.h"
#include "widgets/general_use/BackgroundLeft.h"
#include "widgets/general_use/ScreenTitle.h"


UserInterface::Panel::RaceLeft::RaceLeft(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent),
    m_screenTitle(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundLeft(this);
    Q_ASSERT(m_background);
    if (m_background) {

        m_background->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    }

    m_screenTitle = new UserInterface::Widget::ScreenTitle(this);
    Q_ASSERT(m_screenTitle);
    if (m_screenTitle) {

        m_screenTitle->setTitle(UserInterface::Screen::Type::Race);

    }

}



void UserInterface::Panel::RaceLeft::ResizePanel(const QSize& newPanelSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newPanelSize);

    const uint16_t width = newPanelSize.width();
    const uint16_t height = newPanelSize.height();

    UserInterface::Style::General generalStyle;

    if (m_screenTitle && generalStyle.ScreenTitleFontSize.IsValid()) {

        const uint16_t newFontSize = generalStyle.ScreenTitleFontSize.Interpolate(height);
        QFont font = m_screenTitle->font();
        font.setPointSize(newFontSize);
        m_screenTitle->setFont(font);
        m_screenTitle->move(generalStyle.HorizontalEdgeBorder.Calculate(width), generalStyle.VerticalEdgeBorder.Calculate(height));

    }

}