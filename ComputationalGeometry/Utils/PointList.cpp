#include "PointList.h"

// Qt
#include <QPoint>
#include <QRect>

////////// Rect ///////////////////////////////////////////////////////////////

bool Rect::valid() const noexcept
{
    constexpr static Rect defaultRect;
    return (*this) != defaultRect;
}

QRect Rect::toQRect() const noexcept
{
    return {minX, minY, maxX, maxY};
}

int Rect::width() const noexcept
{
    return maxX - minX;
}

int Rect::height() const noexcept
{
    return maxY - minY;
}

double Rect::centerX() const noexcept
{
    return (maxX + minX) / 2.;
}

double Rect::centerY() const noexcept
{
    return (maxY + minY) / 2.;
}

////////// LineList ///////////////////////////////////////////////////////////

const QPoint& PointList::at(size_t index) const noexcept
{
    return fPoints[index];
}

const Rect& PointList::rect() const noexcept
{
    return fRect;
}

size_t PointList::count() const noexcept
{
    return fPoints.size();
}

void PointList::add(const QPoint& point)
{
    fPoints.push_back(point);
    refreshRect(point);
}

void PointList::add(const PointList& points)
{
    const size_t newSize = fPoints.size() + points.fPoints.size();
    if (newSize > fPoints.capacity()) {
        fPoints.reserve(newSize);
    }
    for (const auto& point : points.fPoints) {
        fPoints.push_back(point);
    }
    refreshRect(points);
}

void PointList::refreshRect() noexcept
{
    fRect = Rect{};
    for (const auto& line : fPoints) {
        refreshRect(line);
    }
}

void PointList::refreshRect(const QPoint& point) noexcept
{
    fRect.maxX = std::max(fRect.maxX, point.x());
    fRect.maxY = std::max(fRect.maxY, point.y());
    fRect.minX = std::min(fRect.minX, point.x());
    fRect.minY = std::min(fRect.minY, point.y());
}

void PointList::refreshRect(const PointList& line) noexcept
{
    fRect.maxX = std::max(fRect.maxX, line.fRect.maxX);
    fRect.maxY = std::max(fRect.maxY, line.fRect.maxY);
    fRect.minX = std::min(fRect.minX, line.fRect.minX);
    fRect.minY = std::min(fRect.minY, line.fRect.minY);
}

auto PointList::begin() noexcept -> Iterator
{
    return fPoints.begin();
}

auto PointList::end() noexcept -> Iterator
{
    return fPoints.end();
}

auto PointList::begin() const noexcept -> ConstIterator
{
    return fPoints.cbegin();
}

auto PointList::end() const noexcept -> ConstIterator
{
    return fPoints.cend();
}
