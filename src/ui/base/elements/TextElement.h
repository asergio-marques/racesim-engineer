#ifndef USERINTERFACE_BASE_INCLUDE_TEXT_ELEMENT_H_
#define USERINTERFACE_BASE_INCLUDE_TEXT_ELEMENT_H_

#include <QFont>
#include "base/WidgetId.h"
#include "base/Element.h"

class QLabel;
class QWidget;



namespace UserInterface {

    namespace Base {

        enum class FontThickness {

            Regular     = 0,
            Bold        = 5,
            ExtraBold   = 6

        };

        class TextElement : public UserInterface::Base::Element {

            Q_OBJECT

            public:
                TextElement(UserInterface::Base::WidgetId id, QWidget* parent = 0);
                virtual ~TextElement() = default;

                // Operations
                virtual bool Activate() override;
                virtual bool Deactivate() override;
                virtual void Move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override;
                virtual void SetFontSize(const uint16_t size);
                virtual void SetFontThickness(const UserInterface::Base::FontThickness thickness);

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

#endif // USERINTERFACE_BASE_INCLUDE_TEXT_ELEMENT_H_