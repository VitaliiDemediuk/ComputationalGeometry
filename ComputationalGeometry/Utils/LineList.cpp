#include "LineList.h"

////////// Rect ///////////////////////////////////////////////////////////////

bool Rect::valid() const noexcept
{
    constexpr static Rect defaultRect;
    return (*this) != defaultRect;
}

////////// LineList ///////////////////////////////////////////////////////////

const QLine& LineList::at(size_t index) const noexcept
{
    return fLines[index];
}

const Rect& LineList::rect(size_t index) const noexcept
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
    fRect.minX = std::min(fRect.minX, std::max(line.x1(), line.x2()));
    fRect.minY = std::min(fRect.minY, std::max(line.y1(), line.y2()));
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
