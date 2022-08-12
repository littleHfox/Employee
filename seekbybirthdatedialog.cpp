#include "seekbybirthdatedialog.h"
#include "ui_seekbybirthdatedialog.h"

SeekbyBirthDateDialog::SeekbyBirthDateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekbyBirthDateDialog)
{
    ui->setupUi(this);
    RadioGroup = new QButtonGroup(this);
    RadioGroup->addButton(ui->radioBefore);
    RadioGroup->addButton(ui->radioAfter);
    m_iRadioID = 0;
}

SeekbyBirthDateDialog::~SeekbyBirthDateDialog()
{
    delete ui;
    delete RadioGroup;
}

QDate SeekbyBirthDateDialog::BirthDate()
{
    return ui->dateSeekbyBirthDate->date();
}

void SeekbyBirthDateDialog::on_radioBefore_clicked()
{
    m_iRadioID = 0;
}
void SeekbyBirthDateDialog::on_radioAfter_clicked()
{
    m_iRadioID = 1;
}
