#ifndef SEEKBYSALARYDIALOG_H
#define SEEKBYSALARYDIALOG_H
#include <QButtonGroup>
#include <QDialog>

namespace Ui {
class SeekbySalaryDialog;
}

class SeekbySalaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SeekbySalaryDialog(QWidget *parent = nullptr);
    ~SeekbySalaryDialog();

    int Salary();
    int m_iRadioID;//当前选中哪一个，0--少于 1--大于（包含）

private slots:
    void on_radioLessthan_clicked();
    void on_radioLargerthan_clicked();

private:
    Ui::SeekbySalaryDialog *ui;
    QButtonGroup *RadioGroup;
};

#endif // SEEKBYSALARYDIALOG_H
