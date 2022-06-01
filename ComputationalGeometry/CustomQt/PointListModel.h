#ifndef LINELISTMODEL_H
#define LINELISTMODEL_H

#include <QAbstractListModel>

class PointList;

class PointListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PointListModel(PointList& points) noexcept;

    void setPoints(PointList points);

    // QAbstractItemModel
    int rowCount(const QModelIndex&) const final;
    int columnCount(const QModelIndex&) const final;
    QVariant data(const QModelIndex &index, int role) const final;

signals:
    void linesChanged();

public slots:
    void addPoint(const QPoint& point);
    void addPoints(const PointList& point);

private:
    PointList& points;
};

#endif // LINELISTMODEL_H
