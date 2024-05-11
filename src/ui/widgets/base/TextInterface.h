#ifndef USERINTERFACE_WIDGET_INCLUDE_TEXT_INTERFACE_H_
#define USERINTERFACE_WIDGET_INCLUDE_TEXT_INTERFACE_H_

#include <QFont>
#include <QLabel>
#include "base/ID.h"
#include "base/Interface.h"


class QWidget;



namespace UserInterface {

    namespace Widget {

        enum class FontThickness {

            Regular     = 0,
            Bold        = 5,
            ExtraBold   = 6

        };

        class TextInterface : public QLabel, public UserInterface::Widget::Interface {

            Q_OBJECT

            public:
                TextInterface(UserInterface::Widget::ID id, QWidget* parent = 0);
                virtual ~TextInterface() = default;

                // Operations
                virtual void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override;
                virtual void setText(const QString& text);
                virtual void setText(const std::string& text);
                virtual void setText(const char* text);
                virtual void setFontSize(const uint16_t size);
                virtual void setFontThickness(const UserInterface::Widget::FontThickness thickness);

                // Getters
                virtual const uint16_t getTextWidth() const;
                virtual const uint16_t getTextHeight() const;

            protected:
                uint16_t m_originalFontSize;

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_TEXT_INTERFACE_H_