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
    PointList lines;
    PointListModel lineListModel{lines};
    CustomGraphicsScene scene{lines};
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , d{new MainWindowPrivate}
    , ui{new Ui::MainWindow}
{
    ui->setupUi(this);

    ui->lineListView->setModel(&d->lineListModel);
    ui->graphicsView->setScene(&d->scene);

    connect(this, &MainWindow::pointAdded, &d->lineListModel, &PointListModel::addPoint);

    connect(&d->lineListModel, &PointListModel::linesChanged, [this] () {
        d->scene.reset();
    });
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
    d->lineListModel.setPoints(std::move(newPoints));
}
