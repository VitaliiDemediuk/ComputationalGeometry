#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>

class PointList;

class CustomGraphicsScene : public QGraphicsScene
{
    using Super = QGraphicsScene;
    using This  = CustomGraphicsScene;
public:

    explicit CustomGraphicsScene(PointList& lines);

public slots:
    void reset(std::optional<QPointF> fromPoint);
    void reset();

private:
    using Super::addLine;
    QGraphicsLineItem* addLine(const QPointF& p1, const QPointF& p2, double scale);
    QGraphicsLineItem* addLine(const QLineF& l, double scale);
    std::vector<QLineF> getVisibleSegment(const QPointF& p) const;
    std::optional<QPointF> fFromPoint;
    PointList& points;
};

#endif // CUSTOMGRAPHICSSCENE_H
