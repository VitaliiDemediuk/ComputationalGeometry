#include "MainWindow.h"
#include "./ui_MainWindow.h"

// STL
#include <iostream>
#include <vector>

// Custom
#include "CustomGraphicsScene.h"
#include "AddLineDialog.h"

// Qt
#include <QGraphicsItem>

struct MainWindowPrivate
{
    std::vector<QLine> lines;
    LineListModel lineListModel{lines};
    CustomGraphicsScene scene;
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

