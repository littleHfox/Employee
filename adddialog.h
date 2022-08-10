#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();
    QString Name();
    int id();
    QString Sex();
    QDate BirthDate();
    QString Status();
    QString Education();
    int Salary();
private slots:
    void on_checkboxMarried_clicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
