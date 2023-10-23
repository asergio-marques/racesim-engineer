#ifndef USERINTERFACE_BASE_INCLUDE_IPANEL_H_
#define USERINTERFACE_BASE_INCLUDE_IPANEL_H_

#include <map>
#include <QWidget>
#include "base/WidgetId.h"



namespace UserInterface {

    namespace Base {

        class Element;

        class IPanel : public QWidget {

            Q_OBJECT

            public:
                IPanel(QWidget* parent = 0);
                virtual ~IPanel() = default;
                virtual bool UpdateWidget(UserInterface::Base::WidgetId id);

            protected:
                bool RegisterWidget(UserInterface::Base::Element* widget);
                std::map<UserInterface::Base::WidgetId, UserInterface::Base::Element*> m_widgets;

        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_IPANEL_H_