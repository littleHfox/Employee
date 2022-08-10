#include "seekbystatusdialog.h"
#include "ui_seekbystatusdialog.h"

SeekbyStatusDialog::SeekbyStatusDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekbyStatusDialog)
{
    ui->setupUi(this);
}

SeekbyStatusDialog::~SeekbyStatusDialog()
{
    delete ui;
}
