#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

    using Super = QGraphicsView;
    using This  = CustomGraphicsView;
public:
    explicit CustomGraphicsView(QWidget* parent);
};

#endif // CUSTOMGRAPHICSVIEW_H
