#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Custom
#include "LineListModel.h"

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
    void lineAdded(QLine line);

private slots:
    void on_newLineBtn_clicked();
private:
    std::unique_ptr<MainWindowPrivate> d;
    std::unique_ptr<Ui::MainWindow> ui;
};
#endif // MAINWINDOW_H
