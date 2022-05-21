#include "AddLineDialog.h"
#include "ui_AddLineDialog.h"

// Qt
#include <QMessageBox>
#include <QPushButton>
#include <QIntValidator>

AddLineDialog::AddLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLineDialog)
{
    ui->setupUi(this);

    static const QIntValidator validator;
    ui->x1Edit->setValidator(&validator);
    ui->y1Edit->setValidator(&validator);
    ui->x2Edit->setValidator(&validator);
    ui->y2Edit->setValidator(&validator);

    connect(ui->x1Edit, &QLineEdit::textEdited, this, &AddLineDialog::reenableButtonBox);
    connect(ui->y1Edit, &QLineEdit::textEdited, this, &AddLineDialog::reenableButtonBox);
    connect(ui->x2Edit, &QLineEdit::textEdited, this, &AddLineDialog::reenableButtonBox);
    connect(ui->y2Edit, &QLineEdit::textEdited, this, &AddLineDialog::reenableButtonBox);
}

void AddLineDialog::init() {
    ui->x1Edit->setText("");
    ui->y1Edit->setText("");
    ui->x2Edit->setText("");
    ui->y2Edit->setText("");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

QLine AddLineDialog::getLine() const
{
    const auto x1 = ui->x1Edit->text().toInt();
    const auto y1 = ui->y1Edit->text().toInt();
    const auto x2 = ui->x2Edit->text().toInt();
    const auto y2 = ui->y2Edit->text().toInt();
    return {x1, y1, x2, y2};
}

int AddLineDialog::exec(QLine& resLine)
{
    init();
    int res;
    while(true) {
        if (res = Super::exec(); res == QDialog::Accepted) {
            if (const auto line = getLine(); line.p1() != line.p2()) {
                resLine = line;
                break;
            } else {
                QMessageBox::critical(this, "Invalid line", "This is point!");
            }
        } else {
            break;
        }
    }
    return res;
}

AddLineDialog::~AddLineDialog() = default;

////////// SLOTS //////////////////////////////////////////////////////////////

void AddLineDialog::reenableButtonBox()
{
    const bool okBtnDisable = ui->x1Edit->text().isEmpty() || ui->y1Edit->text().isEmpty()
                           || ui->x2Edit->text().isEmpty() || ui->y2Edit->text().isEmpty();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(okBtnDisable);
}
