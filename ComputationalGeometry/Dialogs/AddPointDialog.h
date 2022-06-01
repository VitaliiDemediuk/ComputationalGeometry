#ifndef NEWLINEDIALOG_H
#define NEWLINEDIALOG_H

#include <QDialog>

namespace Ui {
class AddPointDialog;
}

class AddPointDialog : public QDialog
{
    Q_OBJECT
    using Super = QDialog;
    using This = AddPointDialog;
public:
    using Super::exec;

    explicit AddPointDialog(QWidget *parent = nullptr);
    ~AddPointDialog();

    int exec(QPoint& resPoint);

public slots:
    void reenableButtonBox();

private:
    QPoint getPoint() const;
    void init();
    std::unique_ptr<Ui::AddPointDialog> ui;
};

#endif // NEWLINEDIALOG_H
