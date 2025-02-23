#include "panels/Loading.h"

#include <QResizeEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include "panels/Interface.h"
#include "core/ScreenType.h"
#include "core/styles/Loading.h"
#include "widgets/general_use/BackgroundFullScreen.h"
#include "widgets/general_use/ScreenTitle.h"
#include "widgets/specific/LoadingIcon.h"


UserInterface::Panel::Loading::Loading(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent),
    m_loadingIcon(nullptr),
    m_loadingText(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundFullScreen(this);
    Q_ASSERT(m_background);
    if (m_background) {

        m_background->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    }

    m_loadingIcon = new UserInterface::Widget::LoadingIcon(this);
    Q_ASSERT(m_loadingIcon);
    if (m_loadingIcon) {

        m_loadingIcon->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_loadingIcon->setMinimumSize(86, 86);
        m_loadingIcon->setMaximumSize(344, 344);

    }

    m_loadingText = new UserInterface::Widget::ScreenTitle(this);
    Q_ASSERT(m_loadingText);
    if (m_loadingText) {

        m_loadingText->setTitle(UserInterface::Screen::Type::Loading);
        m_loadingText->setAlignment(Qt::AlignCenter);

    }
    QGridLayout* layout = new QGridLayout(this);
    // center the loading icon
    QVBoxLayout* vlayout = new QVBoxLayout;
    vlayout->addWidget(m_loadingIcon);
    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addStretch();
    hlayout->addLayout(vlayout);
    hlayout->addStretch();
    layout->addLayout(hlayout, 2, 1);

    // center the loading text
    vlayout = new QVBoxLayout;
    vlayout->addWidget(m_loadingText);
    hlayout = new QHBoxLayout;
    hlayout->addStretch();
    hlayout->addLayout(vlayout);
    hlayout->addStretch();
    layout->addLayout(hlayout, 3, 1);

    // add spacers
    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 0);
    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 1);
    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 2);

    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 1, 0);
    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 1, 1);
    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 1, 2);

    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 0);
    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 2);

    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 0);
    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 2);

    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 4, 0);
    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 4, 1);
    layout->addItem(new QSpacerItem(64, 64, QSizePolicy::Expanding, QSizePolicy::Expanding), 4, 2);

    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);

}