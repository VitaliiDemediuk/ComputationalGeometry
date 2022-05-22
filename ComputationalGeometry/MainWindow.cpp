#include "MainWindow.h"
#include "./ui_MainWindow.h"

// STL
#include <fstream>
#include <vector>

// Custom
#include "CustomGraphicsScene.h"
#include "AddLineDialog.h"

// Utils
#include "LineList.h"

// Qt
#include <QGraphicsItem>
#include <QFileDialog>
#include <QMessageBox>

struct MainWindowPrivate
{
    LineList lines;
    LineListModel lineListModel{lines};
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

    connect(this, &MainWindow::lineAdded, &d->lineListModel, &LineListModel::addLine);

    connect(&d->lineListModel, &LineListModel::linesChanged, [this] () {
        d->scene.reset();
    });
}

MainWindow::~MainWindow() = default;

////////// SLOTS //////////////////////////////////////////////////////////////

void MainWindow::on_newLineBtn_clicked()
{
    static AddLineDialog dialog;
    static QLine line;
    if (dialog.exec(line) == QDialog::Accepted) {
        emit lineAdded(line);
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

    LineList newLines;
    while (!fin.eof()) {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        newLines.add({x1, y1, x2, y2});
    }
    d->lineListModel.setLines(std::move(newLines));
}
