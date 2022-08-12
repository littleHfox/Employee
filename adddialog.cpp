#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    m_iMarried = 0;
}
QString AddDialog::Name()
{
    return ui->textName->toPlainText();
}
int AddDialog::id()
{
    QString tid = ui->textid->toPlainText();
    return tid.toInt();
}
QString AddDialog::Sex()
{
    return ui->textSex->toPlainText();
}
QDate AddDialog::BirthDate()
{
    return ui->dateBirth->date();
}
QString AddDialog::Status()
{
    return ui->textStatus->toPlainText();
}
QString AddDialog::Education()
{
    return ui->textEducation->toPlainText();
}
int AddDialog::Salary()
{
    QString s = ui->textSalary->toPlainText();
    return s.toInt();
}
void AddDialog::on_checkBoxMarried_stateChanged(int arg1)
{
    if(arg1 == 2)
        m_iMarried = 1;
    if(arg1 == 0)
        m_iMarried = 0;
}

AddDialog::~AddDialog()
{
    delete ui;
}
