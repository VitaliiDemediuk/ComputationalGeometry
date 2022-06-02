#include "CustomGraphicsScene.h"

// STL
#include <set>
#include <optional>

// Qt
#include <QGraphicsLineItem>

// Custom
#include "PointList.h"
#include "CustomGraphicsView.h"

#include <boost/math/constants/constants.hpp>

CustomGraphicsScene::CustomGraphicsScene(PointList& points)
    : points{points} {}

QGraphicsLineItem* CustomGraphicsScene::addLine(const QLineF& l, double scale)
{
    QLineF scaledLine{l.x1() * scale, l.y1() * scale, l.x2() * scale, l.y2() * scale};
    return addLine(scaledLine);
}

QGraphicsLineItem* CustomGraphicsScene::addLine(const QPointF& p1, const QPointF& p2, double scale)
{
    QLineF scaledLine{p1.x() * scale, p1.y() * scale, p2.x() * scale, p2.y() * scale};
    return addLine(scaledLine);
}

namespace {

double dist(const QPointF& p1, const QPointF& p2)
{
    constexpr static auto sq = [] (const auto& value) { return value * value; };
    return std::sqrt(sq(p1.x()-p2.x()) + sq(p1.y()-p2.y()));
}

double dist(const QPointF& p, const QLineF& l)
{
    constexpr static auto sq = [] (const auto& value) { return value * value; };
    double t = ((p.x()-l.x1())*(l.x2()-l.x1()) + (p.y()-l.y1())*(l.y2()-l.y1())) / (sq(l.x2()-l.x1()) + sq(l.y2()-l.y1()));
    if (t < 0) {
        t = 0;
    } else if (t > 1) {
        t = 1;
    }
    return std::sqrt(sq(l.x1() - p.x() + (l.x2() - l.x1()) * t) + sq(l.y1() - p.y() + (l.y2() - l.y1()) * t));
}

double getPolarAngle(const QPointF& p) noexcept {
    constexpr static double PI = boost::math::constants::pi<double>();
    const auto [x, y] = p;
    if (x == 0) {
        return y > 0 ? PI / 2 :
                       y < 0 ? 3 * PI / 2 : std::numeric_limits<double>::quiet_NaN();
    } else if (x < 0) {
        return std::atan(y/x) + PI;
    } else {
        return y < 0 ? std::atan(y/x) + 2*PI : std::atan(y/x);
    }
}

}

struct PointInfo {
    size_t index{};
    double angle{};

    bool operator<(const PointInfo& other) const noexcept
    {
        return angle < other.angle;
    }
};

struct SegmentIndexes
{
    size_t idx1;
    size_t idx2;
    bool operator==(const SegmentIndexes& other) const noexcept
    {
        return std::tie(idx1, idx2) == std::tie(other.idx1, other.idx2) or
               std::tie(idx2, idx1) == std::tie(other.idx1, other.idx2);
    }
};

struct IndexLineHash {
    bool operator()(const SegmentIndexes& l) const noexcept
    {
        return h(l.idx1) + h(l.idx2);
    }
    std::hash<double> h;
};

namespace {

QLineF cutSeg(const QLineF& l, const QPointF& q, double angle)
{
    const auto ofsSeg = QLineF{l.p1() - q, l.p2() - q};
    struct Line { double a, b, c; };
    constexpr static auto getLine = [] (const QPointF& p1, const QPointF& p2) {
        const double a = p2.y() - p1.y(), b = p1.x() - p2.x();
        return Line{.a = a, .b = b, .c = a*p1.x() + b*p1.y()};
    };
    const auto interPoint = [] (const Line& l1, const Line& l2) -> std::optional<QPointF> {
        const double det = l1.a * l2.b - l2.a * l1.b;
        if (det == 0)
            return std::nullopt;
        return QPointF{(l2.b * l1.c - l1.b * l2.c) / det, (l1.a * l2.c - l2.a * l1.c) / det};
    }(getLine(ofsSeg.p1(), ofsSeg.p2()), getLine({0, 0}, {std::cos(angle), std::sin(angle)}));
    if (!interPoint) {
        return l;
    }
    const auto cutLine = QLineF{getPolarAngle(ofsSeg.p1()) < angle ? interPoint.value() : ofsSeg.p1(),
                                getPolarAngle(ofsSeg.p2()) < angle ? interPoint.value() : ofsSeg.p2()};
    return {cutLine.p1() + q, cutLine.p2() + q};
}

}

struct SegmentIndexesCmp
{
    explicit SegmentIndexesCmp(QPointF q, const PointList& points, const double& angle)
        : q{q}, points{points}, angle{angle} {}

    bool operator()(const SegmentIndexes& l1, const SegmentIndexes& l2) const noexcept
    {
        const auto cutSeg1 = cutSeg({points.at(l1.idx1), points.at(l1.idx2)}, q, angle);
        const auto cutSeg2 = cutSeg({points.at(l2.idx1), points.at(l2.idx2)}, q, angle);
        if (l1.idx1 == l2.idx1) { return dist(q, cutSeg1.p2()) < dist(q, cutSeg2.p2()); }
        if (l1.idx2 == l2.idx1) { return dist(q, cutSeg1.p1()) < dist(q, cutSeg2.p2()); }
        if (l1.idx1 == l2.idx2) { return dist(q, cutSeg1.p2()) < dist(q, cutSeg1.p1()); }
        if (l1.idx2 == l2.idx2) { return dist(q, cutSeg1.p1()) < dist(q, cutSeg2.p1()); }
        return dist(q, cutSeg1) < dist(q, cutSeg2);
    }
private:

    QPointF q;
    const PointList& points;
    const double& angle;
};

std::vector<QLineF> CustomGraphicsScene::getVisibleSegment(const QPointF& q) const
{
    if (points.count() <= 2) {
        return {};
    }

    std::vector<PointInfo> sortedPoints;
    sortedPoints.reserve(points.count());
    for (size_t i = 0; i < points.count(); ++i) {
        const auto& p = points.at(i);
        const auto offsetPoint = static_cast<QPointF>(p) - q;
        sortedPoints.emplace_back(i, getPolarAngle(offsetPoint));
    }
    std::sort(sortedPoints.begin(), sortedPoints.end());


    double angle{0};
    SegmentIndexesCmp cmp{q, points, angle};
    using States = std::multiset<SegmentIndexes, SegmentIndexesCmp>;
    States state(cmp);
    std::unordered_map<SegmentIndexes, std::multiset<SegmentIndexes, SegmentIndexesCmp>::iterator, IndexLineHash> visitedSegment;
    std::vector<QLineF> visibleSegment;
    for (const auto& p : sortedPoints) {
        angle = p.angle;
        const auto beginFirstIt = state.begin();
        const auto processLine = [&] (const SegmentIndexes& l) {
            if (const auto it = visitedSegment.find(l); it != visitedSegment.end()) {
                if (it->second != state.end()) {
                    state.erase(it->second);
                    it->second = state.end();
                } else {
                    return;
                }
            } else {
                visitedSegment[l] = state.emplace(l);
            }
        };
        processLine({p.index, points.nextIndex(p.index)});
        processLine({p.index, points.prevIndex(p.index)});

        if (const auto firstIt = state.begin(); firstIt != state.end() and firstIt != beginFirstIt) {
            visibleSegment.emplace_back(points.at(firstIt->idx1), points.at(firstIt->idx2));
        }
    }
    return visibleSegment;
}

void CustomGraphicsScene::reset()
{
    clear();

    const auto viewList = views();
    assert(viewList.size() == 1);
    CustomGraphicsView* view = qobject_cast<CustomGraphicsView*>(viewList[0]);
    assert(view);

    const auto viewSize = view->size();
    constexpr static int BORDERS = 50;
    const auto minViewSize = std::min(viewSize.width() - BORDERS, viewSize.height() - BORDERS);

    const auto rect = points.rect();
    const auto maxRectSize = std::max(rect.width(), rect.height());

    const double scale = static_cast<double>(minViewSize) / maxRectSize;

    if (const size_t pointsCount = points.count(); pointsCount > 0) {
        for (size_t i = 1; i < pointsCount; ++i) {
            addLine(points.at(i-1), points.at(i), scale);
            addLine(points.at(i), points.at((i+1) % pointsCount), scale);
        }
    }
    const auto visibleSegment = getVisibleSegment({0, 0});
    for (const auto& seg : visibleSegment) {
        auto* lineItem = addLine(seg, scale);
        lineItem->setPen({Qt::red});
    }

}
