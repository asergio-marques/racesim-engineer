#ifndef USERINTERFACE_INCLUDE_STYLE_FACTORY_H_
#define USERINTERFACE_INCLUDE_STYLE_FACTORY_H_

#include <QMap>
#include <QObject>
#include "core/Screen.h"



namespace UserInterface {

    namespace Style {

        class Interface;

    }
    class Interface;

    class StyleFactory : public QObject {

        public:
        StyleFactory(QObject* parent = 0);
        ~StyleFactory() = default;
        const UserInterface::Style::Interface* const GetStyle(const UserInterface::Screen::Resolution resolution) const;

        private:
        QMap<Screen::Resolution, UserInterface::Style::Interface*> m_styleMap;
    };

}

#endif // USERINTERFACE_INCLUDE_STYLE_FACTORY_H_