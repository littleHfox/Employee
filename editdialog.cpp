#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);

    m_iSelectIndex = 0;
}

EditDialog::~EditDialog()
{
    delete ui;
}

int EditDialog::id()
{
    QString temp = ui->textid->toPlainText();
    return temp.toInt();
}
QString EditDialog::newString()
{
    return ui->textNew->toPlainText();
}
void EditDialog::on_comboBoxEdit_currentIndexChanged(int index)
{
    m_iSelectIndex = index;
}
