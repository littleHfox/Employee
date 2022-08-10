#ifndef SEEKBYBIRTHDATEDIALOG_H
#define SEEKBYBIRTHDATEDIALOG_H

#include <QDialog>

namespace Ui {
class SeekbyBirthDateDialog;
}

class SeekbyBirthDateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SeekbyBirthDateDialog(QWidget *parent = nullptr);
    ~SeekbyBirthDateDialog();

private:
    Ui::SeekbyBirthDateDialog *ui;
};

#endif // SEEKBYBIRTHDATEDIALOG_H
