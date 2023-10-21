#ifndef USERINTERFACE_BASE_INCLUDE_HELPER_H_
#define USERINTERFACE_BASE_INCLUDE_HELPER_H_

#include <QPoint>
#include <QPointF>
#include <QRect>

namespace UserInterface {

    class Helper {

        public:
            Helper() = default;
            virtual ~Helper() = default;

            const QRectF getRotationTranslation(const QRect& originalLoc, const qreal& rot, bool isRadians = false);

        private:
            const QPointF getRotatedPoint(const QPoint& originalPoint, const QPoint& center, const qreal& rot);
    };

};

#endif  //  USERINTERFACE_BASE_INCLUDE_HELPER_H_