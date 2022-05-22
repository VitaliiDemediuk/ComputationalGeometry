#include "CustomGraphicsView.h"

CustomGraphicsView::CustomGraphicsView(QWidget* parent)
    : Super{parent}
{
    scale(1, -1);
}
