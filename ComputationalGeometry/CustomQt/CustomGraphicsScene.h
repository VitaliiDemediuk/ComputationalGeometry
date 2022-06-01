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
    void reset();

private:
    using Super::addLine;
    void addLine(const QPoint& p1, const QPoint& p2, double scale);
    PointList& points;
};

#endif // CUSTOMGRAPHICSSCENE_H
