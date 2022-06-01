#include "CustomGraphicsScene.h"

// Custom
#include "PointList.h"
#include "CustomGraphicsView.h"

CustomGraphicsScene::CustomGraphicsScene(PointList& points)
    : points{points} {}

void CustomGraphicsScene::addLine(const QPoint& p1, const QPoint& p2, double scale)
{
    QLineF scaledLine{p1.x() * scale, p1.y() * scale, p2.x() * scale, p2.y() * scale};
    addLine(scaledLine);
}

void CustomGraphicsScene::reset()
{
    clear();

    const auto viewList = views();
    assert(viewList.size() == 1);
    CustomGraphicsView* view = qobject_cast<CustomGraphicsView*>(viewList[0]);
    assert(view);

    const auto viewSize = view->size();
    constexpr static int BORDERS = 10;
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
}
