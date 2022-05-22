#ifndef LINELISTMODEL_H
#define LINELISTMODEL_H

#include <QAbstractListModel>

class LineList;

class LineListModel : public QAbstractListModel
{
public:
    LineListModel(LineList& lines);

    // QAbstractItemModel
    int rowCount(const QModelIndex&) const final;
    int columnCount(const QModelIndex&) const final;
    QVariant data(const QModelIndex &index, int role) const final;

public slots:
    void addLine(const QLine& line);
private:
    LineList& lines;
};

#endif // LINELISTMODEL_H
