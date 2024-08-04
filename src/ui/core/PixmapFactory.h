#ifndef USERINTERFACE_INCLUDE_PIXMAP_FACTORY_H_
#define USERINTERFACE_INCLUDE_PIXMAP_FACTORY_H_

#include <QMap>
#include <QPixmap>
#include <QString>
#include "Image.h"
#include "data/internal/Session.h"



namespace UserInterface {

    // Implemented as singleton
    class PixmapFactory {

        public:
        // Pointer to unique instance
        static UserInterface::PixmapFactory* instance();

        // Returns the pixmap requested, centralized form of pixmap fetching
        // If the pixmap cannot be loaded from a given file, a simple icon containing a question mark will be returned
        // NOTE: There's probably more performant ways to do this than to straight-out copy a QPixmap...
        void fetchPixmap(UserInterface::Widget::StandardImage request, QPixmap& pixmap) const;
        UserInterface::Widget::StandardImage convertTeamID(Session::Internal::TeamID request) const;

        private:
        // Private constructor to guarantee single instantiation
        PixmapFactory();

        // Destructor
        virtual ~PixmapFactory() = default;

        bool internalFetching(UserInterface::Widget::StandardImage request, QPixmap& pixmap) const;

        void constructConverterMap();
        void constructTeamIconMap();

        QMap<UserInterface::Widget::StandardImage, QString> m_converterMap;
        QMap<Session::Internal::TeamID, UserInterface::Widget::StandardImage> m_teamIconMap;

        static UserInterface::PixmapFactory* m_instance;

    };

}

#endif // USERINTERFACE_INCLUDE_PIXMAP_FACTORY_H_