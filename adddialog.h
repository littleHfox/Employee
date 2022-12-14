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
    int m_iMarried;//指示是否已婚，1--已婚 0--未婚
private slots:
    void on_checkBoxMarried_stateChanged(int arg1);

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
