#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "agentsinfotable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ShowAllAgents();
    void ShowBirthDate(int radioID, QDate valueDate);   //选中的radio编号，输入的日期
    void ShowStatus(QString value);     //输入的职称
    void ShowEducation(QString value);  //输入的学历
    void ShowMarried(int checkedID);    //是否勾选，0为未勾选，2为勾选
    void ShowSalary(int radioID, int value);    //选中的radio的编号，输入的工资值

private slots:
    void on_actionOpen_triggered();

    void on_actionSaveas_triggered();

    void on_actionSave_triggered();

    void on_actionClose_triggered();

    void on_actionAdd_triggered();

    void on_actionDelete_triggered();

    void on_actionEdit_triggered();

    void on_actionAll_Agents_triggered();

    void on_actionSeekbyBirthDate_triggered();

    void on_actionSeekbyStatus_triggered();

    void on_actionSeekbyEducation_triggered();

    void on_actionSeekbyMarried_triggered();

    void on_actionSeekbySalary_triggered();

    void on_ShowInfoTableView_changed();

    void on_MainWindow_customContextMenuRequested(const QPoint& pos);   //鼠标右键菜单

    void Deletethis();                  //直接删除选中的职工信息

    void SeekbyThis();                  //筛选与当前单元格内数据相同的员工数据

private:
    Ui::MainWindow *ui;
    QStandardItemModel * agentsInforModel;
    AgentsInfotable m_InfoTable;
    int m_iCurTable;    //当前显示的表格，0--初始状态 1--所有职员信息 2--按生日查找 3--按职称查找 4--按学历查找 5--按婚姻状况查找 6--按工资查找
    QString g_FileName; //全局变量，打开的文件名
};
#endif // MAINWINDOW_H
