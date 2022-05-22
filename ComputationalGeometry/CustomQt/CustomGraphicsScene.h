#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>

class LineList;

class CustomGraphicsScene : public QGraphicsScene
{
    using Super = QGraphicsScene;
    using This  = CustomGraphicsScene;
public:

    explicit CustomGraphicsScene(LineList& lines);

public slots:
    void reset();

private:
    LineList& lines;
};

#endif // CUSTOMGRAPHICSSCENE_H
