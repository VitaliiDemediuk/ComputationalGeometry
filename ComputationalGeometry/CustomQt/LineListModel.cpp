#include "LineListModel.h"

// Qt
#include <QLine>

LineListModel::LineListModel(std::vector<QLine>& lines)
    : lines{lines} {}

void LineListModel::addLine(const QLine& line)
{
    beginResetModel();
    lines.push_back(line);
    endResetModel();
}

int LineListModel::rowCount(const QModelIndex &parent) const
{
    return lines.size();
}

int LineListModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant LineListModel::data(const QModelIndex& index, int role) const
{
    const auto row = index.row();
    if (role == Qt::DisplayRole) {
        const auto line = lines[row];
        return QString {"(%1, %2) (%3, %4)"}
                      .arg(line.x1())
                      .arg(line.y1())
                      .arg(line.x2())
                      .arg(line.y2());
    }
    return {};
}
