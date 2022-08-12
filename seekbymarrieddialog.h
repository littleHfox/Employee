#ifndef SEEKBYMARRIEDDIALOG_H
#define SEEKBYMARRIEDDIALOG_H

#include <QDialog>

namespace Ui {
class SeekbyMarriedDialog;
}

class SeekbyMarriedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SeekbyMarriedDialog(QWidget *parent = nullptr);
    ~SeekbyMarriedDialog();

    int m_iMarried;
private slots:
    void on_checkBoxMarried_stateChanged(int arg1);
private:
    Ui::SeekbyMarriedDialog *ui;
};

#endif // SEEKBYMARRIEDDIALOG_H
