#include "core/StyleFactory.h"

#include <QMap.h>
#include "core/Screen.h"
#include "core/style/Default480p.h"
#include "core/style/FullHD1080p.h"
#include "core/style/QuadHD1440p.h"
#include "core/style/UltraHD4K.h"




UserInterface::StyleFactory::StyleFactory(QObject* parent) :
    QObject(parent) {

    m_styleMap.insert(UserInterface::Screen::Resolution::MinimumDefault, new UserInterface::Style::Default480p);
    m_styleMap.insert(UserInterface::Screen::Resolution::r1080p, new UserInterface::Style::FullHD1080p);
    m_styleMap.insert(UserInterface::Screen::Resolution::r1440p, new UserInterface::Style::QuadHD1440p);
    m_styleMap.insert(UserInterface::Screen::Resolution::r4K, new UserInterface::Style::UltraHD4K);

}



const UserInterface::Style::Interface* const UserInterface::StyleFactory::GetStyle(const UserInterface::Screen::Resolution resolution) const {

    return m_styleMap.value(resolution, new UserInterface::Style::Default480p);

}