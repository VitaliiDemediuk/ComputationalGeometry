#ifndef LINELIST_H
#define LINELIST_H

#include <vector>
#include <QLine>

constexpr static int MAX_VALUE = std::numeric_limits<int>::max();
constexpr static int MIN_VALUE = std::numeric_limits<int>::min();

struct Rect {
    int maxX = MIN_VALUE;
    int maxY = MIN_VALUE;
    int minX = MAX_VALUE;
    int minY = MAX_VALUE;

    bool operator==(const Rect&) const noexcept = default;
    bool valid() const noexcept;
};


class LineList
{

public:
    using LinesList = std::vector<QLine>;
    using Iterator = LinesList::iterator;
    using ConstIterator = LinesList::const_iterator;

    const QLine& at(size_t index) const noexcept;
    const Rect& rect(size_t index) const noexcept;
    size_t count() const noexcept;

    void add(const QLine& line);

    // iterators
    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
private:
    void refreshRect() noexcept;
    void refreshRect(const QLine& line) noexcept;

    constexpr static int MAX_VALUE = std::numeric_limits<int>::max();
    constexpr static int MIN_VALUE = std::numeric_limits<int>::min();

    LinesList fLines;
    Rect fRect;
};

#endif // LINELIST_H
