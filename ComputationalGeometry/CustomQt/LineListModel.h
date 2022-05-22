#ifndef LINELISTMODEL_H
#define LINELISTMODEL_H

#include <QAbstractListModel>

class LineList;

class LineListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LineListModel(LineList& lines) noexcept;

    // QAbstractItemModel
    int rowCount(const QModelIndex&) const final;
    int columnCount(const QModelIndex&) const final;
    QVariant data(const QModelIndex &index, int role) const final;

signals:
    void lineAdded();

public slots:
    void addLine(const QLine& line);
private:
    LineList& lines;
};

#endif // LINELISTMODEL_H
