#ifndef LINELISTMODEL_H
#define LINELISTMODEL_H

#include <QAbstractListModel>

class LineList;

class LineListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LineListModel(LineList& lines) noexcept;

    void setLines(LineList lines);

    // QAbstractItemModel
    int rowCount(const QModelIndex&) const final;
    int columnCount(const QModelIndex&) const final;
    QVariant data(const QModelIndex &index, int role) const final;

signals:
    void linesChanged();

public slots:
    void addLine(const QLine& line);
    void addLines(const LineList& lines);

private:
    LineList& lines;
};

#endif // LINELISTMODEL_H
