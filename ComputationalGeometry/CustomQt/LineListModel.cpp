#include "LineListModel.h"
#include <iostream>

// Custom
#include "LineList.h"

// Qt
#include <QLine>

LineListModel::LineListModel(LineList& lines) noexcept
    : lines{lines} {}

void LineListModel::addLine(const QLine& line)
{
    beginResetModel();
    lines.add(line);
    endResetModel();
    emit linesChanged();
}

void LineListModel::addLines(const LineList& newLines)
{
    beginResetModel();
    lines.add(newLines);
    endResetModel();
    emit linesChanged();
}

void LineListModel::setLines(LineList newLines)
{
    beginResetModel();
    lines = std::move(newLines);
    endResetModel();
    emit linesChanged();
}

int LineListModel::rowCount(const QModelIndex &parent) const
{
    return lines.count();
}

int LineListModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant LineListModel::data(const QModelIndex& index, int role) const
{
    const auto row = index.row();
    if (role == Qt::DisplayRole) {
        const auto& line = lines.at(row);
        return QString {"(%1, %2) (%3, %4)"}
                      .arg(line.x1())
                      .arg(line.y1())
                      .arg(line.x2())
                      .arg(line.y2());
    }
    return {};
}
