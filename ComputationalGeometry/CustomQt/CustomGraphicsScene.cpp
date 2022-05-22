#include "CustomGraphicsScene.h"

// Custom
#include "LineList.h"
#include "CustomGraphicsView.h"

CustomGraphicsScene::CustomGraphicsScene(LineList& lines)
    : lines{lines} {}

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

    const auto rect = lines.rect();
    const auto maxRectSize = std::max(rect.width(), rect.height());

    const double scale = static_cast<double>(minViewSize) / maxRectSize;

    for (const auto& line : lines) {
        QLineF scaledLine{line.x1() * scale, line.y1() * scale, line.x2() * scale, line.y2() * scale};
        addLine(scaledLine);
    }
}
