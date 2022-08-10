#include "seekbybirthdatedialog.h"
#include "ui_seekbybirthdatedialog.h"

SeekbyBirthDateDialog::SeekbyBirthDateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekbyBirthDateDialog)
{
    ui->setupUi(this);
}

SeekbyBirthDateDialog::~SeekbyBirthDateDialog()
{
    delete ui;
}
