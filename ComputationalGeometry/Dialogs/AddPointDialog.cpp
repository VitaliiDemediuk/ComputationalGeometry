#include "AddPointDialog.h"
#include "ui_AddPointDialog.h"

// Qt
#include <QMessageBox>
#include <QPushButton>
#include <QIntValidator>

AddPointDialog::AddPointDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog)
{
    ui->setupUi(this);

    static const QIntValidator validator;
    ui->xEdit->setValidator(&validator);
    ui->yEdit->setValidator(&validator);

    connect(ui->xEdit, &QLineEdit::textEdited, this, &AddPointDialog::reenableButtonBox);
    connect(ui->yEdit, &QLineEdit::textEdited, this, &AddPointDialog::reenableButtonBox);
}

void AddPointDialog::init() {
    ui->xEdit->setText("");
    ui->yEdit->setText("");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

QPoint AddPointDialog::getPoint() const
{
    const auto x = ui->xEdit->text().toInt();
    const auto y = ui->yEdit->text().toInt();
    return {x, y};
}

int AddPointDialog::exec(QPoint& resPoint)
{
    init();
    if (const auto res = Super::exec(); res != QDialog::Accepted) {
        return res;
    }
    resPoint = getPoint();
    return QDialog::Accepted;
}

AddPointDialog::~AddPointDialog() = default;

////////// SLOTS //////////////////////////////////////////////////////////////

void AddPointDialog::reenableButtonBox()
{
    const bool okBtnDisable = ui->xEdit->text().isEmpty() || ui->yEdit->text().isEmpty();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(okBtnDisable);
}
