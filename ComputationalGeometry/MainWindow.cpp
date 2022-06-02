#include "MainWindow.h"
#include "./ui_MainWindow.h"

// STL
#include <fstream>
#include <vector>

// Custom
#include "CustomGraphicsScene.h"
#include "AddPointDialog.h"

// Utils
#include "PointList.h"

// Qt
#include <QGraphicsItem>
#include <QFileDialog>
#include <QMessageBox>

struct MainWindowPrivate
{
    PointList points;
    PointListModel pointListModel{points};
    CustomGraphicsScene scene{points};
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , d{new MainWindowPrivate}
    , ui{new Ui::MainWindow}
{
    ui->setupUi(this);

    static const QIntValidator validator;
    ui->pointXEdit->setValidator(&validator);
    ui->pointYEdit->setValidator(&validator);

    ui->lineListView->setModel(&d->pointListModel);
    ui->graphicsView->setScene(&d->scene);

    connect(this, &MainWindow::pointAdded, &d->pointListModel, &PointListModel::addPoint);

    connect(&d->pointListModel, &PointListModel::linesChanged, [this] () {
        d->scene.reset();
    });

    connect(ui->pointYEdit, &QLineEdit::textEdited, [this] () {
        d->scene.reset(getFromPoint());
    });
}

std::optional<QPointF> MainWindow::getFromPoint()
{
    const auto textX = ui->pointXEdit->text();
    const auto textY = ui->pointYEdit->text();
    if (textX.isEmpty() || textY.isEmpty())
        return std::nullopt;
    return QPoint{textX.toInt(), textY.toInt()};
}

MainWindow::~MainWindow() = default;

////////// SLOTS //////////////////////////////////////////////////////////////

void MainWindow::on_newLineBtn_clicked()
{
    static AddPointDialog dialog;
    static QPoint point;
    if (dialog.exec(point) == QDialog::Accepted) {
        emit pointAdded(point);
    }
}

void MainWindow::on_loadLinesTxt_triggered()
{
    const auto file = QFileDialog::getOpenFileName(this, "Text file", "", "Text file (*.txt)");
    std::ifstream fin{std::filesystem::path{file.toStdWString()}};
    if (!fin.is_open()) {
        QMessageBox::critical(this, "File error", "Cannot open the file.");
        return;
    }

    PointList newPoints;
    while (!fin.eof()) {
        int x, y;
        fin >> x >> y;
        newPoints.add({x, y});
    }
    d->pointListModel.setPoints(std::move(newPoints));
}
