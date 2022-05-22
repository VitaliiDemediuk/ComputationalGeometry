#include "MainWindow.h"
#include "./ui_MainWindow.h"

// STL
#include <iostream>
#include <vector>

// Custom
#include "CustomGraphicsScene.h"
#include "AddLineDialog.h"

// Utils
#include "LineList.h"

// Qt
#include <QGraphicsItem>

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

    connect(&d->lineListModel, &LineListModel::lineAdded, [this] () {
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

