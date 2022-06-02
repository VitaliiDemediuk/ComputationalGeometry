#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Custom
#include "PointListModel.h"

// Qt
#include <QMainWindow>

class CustomGraphicsScene;
class MainWindowPrivate;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void pointAdded(QPoint line);

private slots:
    void on_newLineBtn_clicked();
    void on_loadLinesTxt_triggered();
private:
    std::optional<QPointF> getFromPoint();

    std::unique_ptr<MainWindowPrivate> d;
    std::unique_ptr<Ui::MainWindow> ui;
};
#endif // MAINWINDOW_H
