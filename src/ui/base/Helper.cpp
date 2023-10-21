#include "base/Helper.h"

#include <QtMath>
#include <QPoint>
#include <QPointF>
#include <QRect>



const QRectF UserInterface::Helper::getRotationTranslation(const QRect& originalLoc, const qreal& rot, const bool isRadians) {

    // convert to radians if degrees
    qreal rotRads = rot;
    if (!isRadians) {
        rotRads = (rot * qAtan(1) * 4) / 180;
    }
    QPointF topLeft = getRotatedPoint(originalLoc.topLeft(), originalLoc.center(), rotRads);
    QPointF topRight = getRotatedPoint(originalLoc.topRight(), originalLoc.center(), rotRads);
    QPointF bottomLeft = getRotatedPoint(originalLoc.bottomLeft(), originalLoc.center(), rotRads);
    QPointF bottomRight = getRotatedPoint(originalLoc.bottomRight(), originalLoc.center(), rotRads);

    qreal minX = qMin(qMin(qMin(topLeft.x(), topRight.x()), bottomLeft.x()), bottomRight.x());
    qreal minY = qMin(qMin(qMin(topLeft.y(), topRight.y()), bottomLeft.y()), bottomRight.y());
    qreal maxX = qMax(qMax(qMax(topLeft.x(), topRight.x()), bottomLeft.x()), bottomRight.x());
    qreal maxY = qMax(qMax(qMax(topLeft.y(), topRight.y()), bottomLeft.y()), bottomRight.y());

    return QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
}

const QPointF UserInterface::Helper::getRotatedPoint(const QPoint& originalPoint, const QPoint& center, const qreal& rot) {

    const qreal relativeX = originalPoint.x() - center.x();
    const qreal relativeY = originalPoint.y() - center.y();
    const qreal angleSin = qSin(rot);
    const qreal angleCos = qCos(rot);

    const qreal newRelativeX = (relativeX * angleCos) - (relativeY * angleSin);
    const qreal newRelativeY = (relativeX * angleSin) + (relativeY * angleCos);

    const qreal finalX = center.x() + newRelativeX;
    const qreal finalY = center.y() + newRelativeY;

    return QPointF(finalX, finalY);

}