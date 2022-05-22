#ifndef LINELIST_H
#define LINELIST_H

#include <vector>
#include <limits>

class QRect;
class QLine;

constexpr static int MAX_VALUE = std::numeric_limits<int>::max();
constexpr static int MIN_VALUE = std::numeric_limits<int>::min();

struct Rect {
    int maxX = MIN_VALUE;
    int maxY = MIN_VALUE;
    int minX = MAX_VALUE;
    int minY = MAX_VALUE;

    bool operator==(const Rect&) const noexcept = default;
    bool valid() const noexcept;
    QRect toQRect() const noexcept;

    int width() const noexcept;
    int height() const noexcept;

    double centerX() const noexcept;
    double centerY() const noexcept;
};


class LineList
{

public:
    using LinesList = std::vector<QLine>;
    using Iterator = LinesList::iterator;
    using ConstIterator = LinesList::const_iterator;

    const QLine& at(size_t index) const noexcept;
    const Rect& rect() const noexcept;
    size_t count() const noexcept;

    void add(const QLine& line);
    void add(const LineList& lines);

    // iterators
    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
private:
    void refreshRect() noexcept;
    void refreshRect(const QLine& line) noexcept;
    void refreshRect(const LineList& line) noexcept;

    constexpr static int MAX_VALUE = std::numeric_limits<int>::max();
    constexpr static int MIN_VALUE = std::numeric_limits<int>::min();

    LinesList fLines;
    Rect fRect;
};

#endif // LINELIST_H
