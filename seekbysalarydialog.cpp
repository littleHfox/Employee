#include "seekbysalarydialog.h"
#include "ui_seekbysalarydialog.h"

SeekbySalaryDialog::SeekbySalaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekbySalaryDialog)
{
    ui->setupUi(this);
    RadioGroup = new QButtonGroup(this);
    RadioGroup->addButton(ui->radioLessthan);
    RadioGroup->addButton(ui->radioLargerthan);
    m_iRadioID = 0;
}

SeekbySalaryDialog::~SeekbySalaryDialog()
{
    delete ui;
    delete RadioGroup;
}

int SeekbySalaryDialog::Salary()
{
    QString salary;
    salary = ui->textSeekbySalary->toPlainText();
    return salary.toInt();
}
void SeekbySalaryDialog::on_radioLessthan_clicked()
{
    m_iRadioID = 0;
}
void SeekbySalaryDialog::on_radioLargerthan_clicked()
{
    m_iRadioID = 1;
}
