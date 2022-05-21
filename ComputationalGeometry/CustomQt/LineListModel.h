#ifndef LINELISTMODEL_H
#define LINELISTMODEL_H

#include <QAbstractListModel>

class LineListModel : public QAbstractListModel
{
public:
    LineListModel(std::vector<QLine>& lines);

    // QAbstractItemModel
    int rowCount(const QModelIndex&) const final;
    int columnCount(const QModelIndex&) const final;
    QVariant data(const QModelIndex &index, int role) const final;

public slots:
    void addLine(const QLine& line);
private:
    std::vector<QLine>& lines;
};

#endif // LINELISTMODEL_H
