#ifndef USERINTERFACE_INCLUDE_STYLE_SHEET_FACTORY_H_
#define USERINTERFACE_INCLUDE_STYLE_SHEET_FACTORY_H_

#include <QString>



namespace UserInterface {

    // Implemented as singleton
    class StyleSheetFactory {

        public:

        enum class FontThickness {

            Regular = 0,
            Bold = 5,
            ExtraBold = 6

        };

        enum class FontColor {

            Regular = 0,
            White = 0

        };

        // Pointer to unique instance
        static UserInterface::StyleSheetFactory* instance();

        // Returns the pixmap requested, centralized form of pixmap fetching
        // If the pixmap cannot be loaded from a given file, a simple icon containing a question mark will be returned
        // NOTE: There's probably more performant ways to do this than to straight-out copy a QPixmap...
        QString requestByColorAndThickness(
            UserInterface::StyleSheetFactory::FontThickness boldness = UserInterface::StyleSheetFactory::FontThickness::Regular,
            UserInterface::StyleSheetFactory::FontColor color = UserInterface::StyleSheetFactory::FontColor::Regular) const;

        private:
        // Private constructor to guarantee single instantiation
        StyleSheetFactory() = default;

        // Destructor
        virtual ~StyleSheetFactory() = default;

        static UserInterface::StyleSheetFactory* m_instance;

    };

}

#endif // USERINTERFACE_INCLUDE_STYLE_SHEET_FACTORY_H_