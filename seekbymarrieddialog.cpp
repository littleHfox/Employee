#include "seekbymarrieddialog.h"
#include "ui_seekbymarrieddialog.h"

SeekbyMarriedDialog::SeekbyMarriedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekbyMarriedDialog)
{
    ui->setupUi(this);
    m_iMarried = 0;
}

SeekbyMarriedDialog::~SeekbyMarriedDialog()
{
    delete ui;
}

void SeekbyMarriedDialog::on_checkBoxMarried_stateChanged(int arg1)
{
    if(arg1 == 2)
        m_iMarried = 1;
    if(arg1 == 0)
        m_iMarried = 0;
}
