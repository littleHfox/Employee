#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = nullptr);
    ~EditDialog();

    int id();
    QString newString();
    int m_iSelectIndex;//选中的目标0--职称 1--学历 2--工资 3--婚姻状况

private slots:
    void on_comboBoxEdit_currentIndexChanged(int index);

private:
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
