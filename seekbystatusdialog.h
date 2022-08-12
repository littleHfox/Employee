#ifndef SEEKBYSTATUSDIALOG_H
#define SEEKBYSTATUSDIALOG_H

#include <QDialog>

namespace Ui {
class SeekbyStatusDialog;
}

class SeekbyStatusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SeekbyStatusDialog(QWidget *parent = nullptr);
    ~SeekbyStatusDialog();

    QString status();
private:
    Ui::SeekbyStatusDialog *ui;
};

#endif // SEEKBYSTATUSDIALOG_H
