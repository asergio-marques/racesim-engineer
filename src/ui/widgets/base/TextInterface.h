#ifndef USERINTERFACE_WIDGET_INCLUDE_TEXT_INTERFACE_H_
#define USERINTERFACE_WIDGET_INCLUDE_TEXT_INTERFACE_H_

#include <QFont>
#include "base/ID.h"
#include "base/Interface.h"

class QLabel;
class QWidget;



namespace UserInterface {

    namespace Widget {

        enum class FontThickness {

            Regular     = 0,
            Bold        = 5,
            ExtraBold   = 6

        };

        class TextInterface : public UserInterface::Widget::Interface {

            Q_OBJECT

            public:
                TextInterface(UserInterface::Widget::ID id, QWidget* parent = 0);
                virtual ~TextInterface() = default;

                // Operations
                virtual void Move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override;
                virtual void SetFontSize(const uint16_t size);
                virtual void SetFontThickness(const UserInterface::Widget::FontThickness thickness);

                // Getters
                virtual const int16_t Width() const override;
                virtual const int16_t Height() const override;
                virtual const int16_t X() const override;
                virtual const int16_t Y() const override;

            protected:
                QLabel* m_text;

                virtual void SetText(const QString& text);
                virtual void SetText(const std::string& text);
                virtual void SetText(const char* text);

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_TEXT_INTERFACE_H_