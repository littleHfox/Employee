#ifndef SEEKBYBIRTHDATEDIALOG_H
#define SEEKBYBIRTHDATEDIALOG_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class SeekbyBirthDateDialog;
}

class SeekbyBirthDateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SeekbyBirthDateDialog(QWidget *parent = nullptr);
    ~SeekbyBirthDateDialog();

    QDate BirthDate();
    int m_iRadioID;//当前选中哪一个，0--以前 1--以后（包含）

private slots:
    void on_radioBefore_clicked();
    void on_radioAfter_clicked();
private:
    Ui::SeekbyBirthDateDialog *ui;
    QButtonGroup *RadioGroup;
};

#endif // SEEKBYBIRTHDATEDIALOG_H
