#ifndef SEEKBYEDUCATIONDIALOG_H
#define SEEKBYEDUCATIONDIALOG_H

#include <QDialog>

namespace Ui {
class SeekbyEducationDialog;
}

class SeekbyEducationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SeekbyEducationDialog(QWidget *parent = nullptr);
    ~SeekbyEducationDialog();

    QString Education();
private:
    Ui::SeekbyEducationDialog *ui;
};

#endif // SEEKBYEDUCATIONDIALOG_H
