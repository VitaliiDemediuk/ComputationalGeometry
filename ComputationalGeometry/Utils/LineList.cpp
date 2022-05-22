#include "LineList.h"

// Qt
#include <QLine>
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

const QLine& LineList::at(size_t index) const noexcept
{
    return fLines[index];
}

const Rect& LineList::rect() const noexcept
{
    return fRect;
}

size_t LineList::count() const noexcept
{
    return fLines.size();
}

void LineList::add(const QLine& line)
{
    fLines.push_back(line);
    refreshRect(line);
}

void LineList::refreshRect() noexcept
{
    fRect = Rect{};
    for (const auto& line : fLines) {
        refreshRect(line);
    }
}

void LineList::refreshRect(const QLine& line) noexcept
{
    fRect.maxX = std::max(fRect.maxX, std::max(line.x1(), line.x2()));
    fRect.maxY = std::max(fRect.maxY, std::max(line.y1(), line.y2()));
    fRect.minX = std::min(fRect.minX, std::min(line.x1(), line.x2()));
    fRect.minY = std::min(fRect.minY, std::min(line.y1(), line.y2()));
}

auto LineList::begin() noexcept -> Iterator
{
    return fLines.begin();
}

auto LineList::end() noexcept -> Iterator
{
    return fLines.end();
}

auto LineList::begin() const noexcept -> ConstIterator
{
    return fLines.cbegin();
}

auto LineList::end() const noexcept -> ConstIterator
{
    return fLines.cend();
}
