#include "PointListModel.h"
#include <iostream>

// Custom
#include "PointList.h"

// Qt
#include <QLine>

PointListModel::PointListModel(PointList& points) noexcept
    : points{points} {}

void PointListModel::addPoint(const QPoint& point)
{
    beginResetModel();
    points.add(point);
    endResetModel();
    emit linesChanged();
}

void PointListModel::addPoints(const PointList& newLines)
{
    beginResetModel();
    points.add(newLines);
    endResetModel();
    emit linesChanged();
}

void PointListModel::setPoints(PointList newPoints)
{
    beginResetModel();
    points = std::move(newPoints);
    endResetModel();
    emit linesChanged();
}

int PointListModel::rowCount(const QModelIndex &parent) const
{
    return points.count();
}

int PointListModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant PointListModel::data(const QModelIndex& index, int role) const
{
    const auto row = index.row();
    if (role == Qt::DisplayRole) {
        const auto& point = points.at(row);
        return QString {"(%1, %2)"}
                      .arg(point.x())
                      .arg(point.y());
    }
    return {};
}
