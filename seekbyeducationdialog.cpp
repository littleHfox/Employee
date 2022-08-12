#include "seekbyeducationdialog.h"
#include "ui_seekbyeducationdialog.h"

SeekbyEducationDialog::SeekbyEducationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekbyEducationDialog)
{
    ui->setupUi(this);
}

SeekbyEducationDialog::~SeekbyEducationDialog()
{
    delete ui;
}

QString SeekbyEducationDialog::Education()
{
    return ui->textSeekbyEducation->toPlainText();
}
