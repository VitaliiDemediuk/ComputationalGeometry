#ifndef NEWLINEDIALOG_H
#define NEWLINEDIALOG_H

#include <QDialog>

namespace Ui {
class AddLineDialog;
}

class AddLineDialog : public QDialog
{
    Q_OBJECT
    using Super = QDialog;
    using This = AddLineDialog;
public:
    using Super::exec;

    explicit AddLineDialog(QWidget *parent = nullptr);
    ~AddLineDialog();

    int exec(QLine& resLine);

public slots:
    void reenableButtonBox();

private:
    QLine getLine() const;
    void init();
    std::unique_ptr<Ui::AddLineDialog> ui;
};

#endif // NEWLINEDIALOG_H
