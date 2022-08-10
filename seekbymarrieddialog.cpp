#include "seekbymarrieddialog.h"
#include "ui_seekbymarrieddialog.h"

SeekbyMarriedDialog::SeekbyMarriedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekbyMarriedDialog)
{
    ui->setupUi(this);
}

SeekbyMarriedDialog::~SeekbyMarriedDialog()
{
    delete ui;
}
