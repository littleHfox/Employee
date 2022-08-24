#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "adddialog.h"
#include "deletedialog.h"
#include "editdialog.h"
#include "seekbybirthdatedialog.h"
#include "seekbystatusdialog.h"
#include "seekbyeducationdialog.h"
#include "seekbymarrieddialog.h"
#include "seekbysalarydialog.h"
#include "readonlydelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ShowInfoTableView->setSelectionMode(QAbstractItemView::SingleSelection); //单次选择
    ui->ShowInfoTableView->setSelectionBehavior(QAbstractItemView::SelectItems); //选中一个item
    agentsInforModel = new QStandardItemModel();
    ui->ShowInfoTableView->setModel(agentsInforModel);
    connect(ui->ShowInfoTableView->itemDelegate(), &QAbstractItemDelegate::closeEditor, this, &MainWindow::on_ShowInfoTableView_changed);
    m_iCurTable = 0;
    this->setContextMenuPolicy(Qt::CustomContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete agentsInforModel;
}
void MainWindow::ShowAllAgents()    //显示所有职工信息
{
    m_iCurTable = 1;
    agentsInforModel->clear();
    agentsInforModel->setColumnCount(8);//8列
    //表头
    QStringList templist;
    templist.append("员工编号");
    templist.append("姓名");
    templist.append("性别");
    templist.append("生日");
    templist.append("职称");
    templist.append("学历");
    templist.append("工资");
    templist.append("婚姻状况");
    agentsInforModel->setHorizontalHeaderLabels(templist);

    int RowCnt = m_InfoTable.getAgentsNum();
    agentsInforModel->setRowCount(RowCnt);  //将表格行数设置为职工数
    //循环输出各职工信息
    QStandardItem *aTempItem;
    QString tempStr;
    for(int i=0; i<RowCnt; ++i)
    {
        CAgent tempAgent = m_InfoTable.getAgent(i);
        tempStr = QString::number(tempAgent.m_iID);
        aTempItem = new QStandardItem(tempStr);
        agentsInforModel->setItem(i, 0, aTempItem);
        aTempItem = new QStandardItem(tempAgent.m_strName);
        agentsInforModel->setItem(i, 1, aTempItem);
        aTempItem = new QStandardItem(tempAgent.m_strSex);
        agentsInforModel->setItem(i, 2, aTempItem);
        tempStr = tempAgent.m_dateBirthdate.toString("yyyy-MM-dd");
        aTempItem = new QStandardItem(tempStr);
        agentsInforModel->setItem(i, 3, aTempItem);
        aTempItem = new QStandardItem(tempAgent.m_strStatus);
        agentsInforModel->setItem(i, 4, aTempItem);
        aTempItem = new QStandardItem(tempAgent.m_strEducation);
        agentsInforModel->setItem(i, 5, aTempItem);
        tempStr = QString::number(tempAgent.m_iSalary);
        aTempItem = new QStandardItem(tempStr);
        agentsInforModel->setItem(i, 6, aTempItem);
        if(tempAgent.m_iMarried == 1)
            tempStr = "已婚";
        else
            tempStr = "未婚";
        aTempItem = new QStandardItem(tempStr);
        agentsInforModel->setItem(i, 7, aTempItem);
    }
    //将员工编号设置为只读
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
    ui->ShowInfoTableView->setItemDelegateForColumn(0, readOnlyDelegate);

}
void MainWindow::ShowBirthDate(int radioID, QDate valueDate)
{
    m_iCurTable = 2;
    agentsInforModel->clear();
    agentsInforModel->setColumnCount(8);//8列
    //表头
    QStringList templist;
    templist.append("员工编号");
    templist.append("姓名");
    templist.append("性别");
    templist.append("生日");
    templist.append("职称");
    templist.append("学历");
    templist.append("工资");
    templist.append("婚姻状况");
    agentsInforModel->setHorizontalHeaderLabels(templist);

    int RowCnt = m_InfoTable.getAgentsNum();
    int RowUsed = 0;    //符合条件的数据数量
    int t = 0;//计数器，用于记录当前输出到第几行
    QStandardItem *aTempItem;
    QString tempStr;
    switch(radioID)
    {
    case 0://以前
        for(int i = 0; i<RowCnt; ++i)   //计数表格显示数据需要的行数
        {
            CAgent tempAgent =m_InfoTable.getAgent(i);
            if(tempAgent.m_dateBirthdate<valueDate)
                ++RowUsed;
        }
        agentsInforModel->setRowCount(RowUsed); //设置表格行数

        //循环输出
        for(int i = 0; i<RowCnt; ++i)
        {
            CAgent tempAgent = m_InfoTable.getAgent(i);
            if(tempAgent.m_dateBirthdate<valueDate)
            {
                tempStr = QString::number(tempAgent.m_iID);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 0, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strName);
                agentsInforModel->setItem(t, 1, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strSex);
                agentsInforModel->setItem(t, 2, aTempItem);
                tempStr = tempAgent.m_dateBirthdate.toString("yyyy-MM-dd");
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 3, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strStatus);
                agentsInforModel->setItem(t, 4, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strEducation);
                agentsInforModel->setItem(t, 5, aTempItem);
                tempStr = QString::number(tempAgent.m_iSalary);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 6, aTempItem);
                if(tempAgent.m_iMarried == 1)
                    tempStr = "已婚";
                else
                    tempStr = "未婚";
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 7, aTempItem);
                ++t;
            }
        }
        break;
    case 1://以后（包含）
        for(int i = 0; i<RowCnt; ++i)   //计数表格显示数据需要的行数
        {
            CAgent tempAgent =m_InfoTable.getAgent(i);
            if(tempAgent.m_dateBirthdate>=valueDate)
                ++RowUsed;
        }
        agentsInforModel->setRowCount(RowUsed); //设置表格行数

        //循环输出
        for(int i = 0; i<RowCnt; ++i)
        {
            CAgent tempAgent = m_InfoTable.getAgent(i);
            if(tempAgent.m_dateBirthdate>=valueDate)
            {
                tempStr = QString::number(tempAgent.m_iID);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 0, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strName);
                agentsInforModel->setItem(t, 1, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strSex);
                agentsInforModel->setItem(t, 2, aTempItem);
                tempStr = tempAgent.m_dateBirthdate.toString("yyyy-MM-dd");
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 3, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strStatus);
                agentsInforModel->setItem(t, 4, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strEducation);
                agentsInforModel->setItem(t, 5, aTempItem);
                tempStr = QString::number(tempAgent.m_iSalary);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 6, aTempItem);
                if(tempAgent.m_iMarried == 1)
                    tempStr = "已婚";
                else
                    tempStr = "未婚";
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 7, aTempItem);
                ++t;
            }
        }
        break;
    default:
        break;
    }
}
void MainWindow::ShowStatus(QString value)
{
    m_iCurTable = 3;
    agentsInforModel->clear();
    agentsInforModel->setColumnCount(8);//8列
    //表头
    QStringList templist;
    templist.append("员工编号");
    templist.append("姓名");
    templist.append("性别");
    templist.append("生日");
    templist.append("职称");
    templist.append("学历");
    templist.append("工资");
    templist.append("婚姻状况");
    agentsInforModel->setHorizontalHeaderLabels(templist);

    int RowCnt = m_InfoTable.getAgentsNum();
    int RowUsed = 0;    //符合条件的数据数量
    int t = 0;//计数器，用于记录当前输出到第几行
    QStandardItem *aTempItem;
    QString tempStr;
    for(int i = 0; i<RowCnt; ++i)   //计数表格显示数据需要的行数
    {
        CAgent tempAgent =m_InfoTable.getAgent(i);
        if(tempAgent.m_strStatus == value)
            ++RowUsed;
    }
    agentsInforModel->setRowCount(RowUsed);//设置表格行数

    //循环输出
    for(int i=0; i<RowCnt; ++i)
    {
        CAgent tempAgent = m_InfoTable.getAgent(i);
        if(tempAgent.m_strStatus == value)
        {
            tempStr = QString::number(tempAgent.m_iID);
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 0, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_strName);
            agentsInforModel->setItem(t, 1, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_strSex);
            agentsInforModel->setItem(t, 2, aTempItem);
            tempStr = tempAgent.m_dateBirthdate.toString("yyyy-MM-dd");
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 3, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_strStatus);
            agentsInforModel->setItem(t, 4, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_strEducation);
            agentsInforModel->setItem(t, 5, aTempItem);
            tempStr = QString::number(tempAgent.m_iSalary);
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 6, aTempItem);
            if(tempAgent.m_iMarried == 1)
                tempStr = "已婚";
            else
                tempStr = "未婚";
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 7, aTempItem);
            ++t;
        }
    }
}
void MainWindow::ShowEducation(QString value)
{
    m_iCurTable = 4;
    agentsInforModel->clear();
    agentsInforModel->setColumnCount(8);//8列
    //表头
    QStringList templist;
    templist.append("员工编号");
    templist.append("姓名");
    templist.append("性别");
    templist.append("生日");
    templist.append("职称");
    templist.append("学历");
    templist.append("工资");
    templist.append("婚姻状况");
    agentsInforModel->setHorizontalHeaderLabels(templist);

    int RowCnt = m_InfoTable.getAgentsNum();
    int RowUsed = 0;    //符合条件的数据数量
    int t = 0;//计数器，用于记录当前输出到第几行
    QStandardItem *aTempItem;
    QString tempStr;
    for(int i = 0; i<RowCnt; ++i)   //计数表格显示数据需要的行数
    {
        CAgent tempAgent =m_InfoTable.getAgent(i);
        if(tempAgent.m_strEducation == value)
            ++RowUsed;
    }
    agentsInforModel->setRowCount(RowUsed);//设置表格行数

    //循环输出
    for(int i=0; i<RowCnt; ++i)
    {

        CAgent tempAgent = m_InfoTable.getAgent(i);
        if(tempAgent.m_strEducation == value)
        {
            tempStr = QString::number(tempAgent.m_iID);
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 0, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_strName);
            agentsInforModel->setItem(t, 1, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_strSex);
            agentsInforModel->setItem(t, 2, aTempItem);
            tempStr = tempAgent.m_dateBirthdate.toString("yyyy-MM-dd");
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 3, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_strStatus);
            agentsInforModel->setItem(t, 4, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_strEducation);
            agentsInforModel->setItem(t, 5, aTempItem);
            tempStr = QString::number(tempAgent.m_iSalary);
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 6, aTempItem);
            if(tempAgent.m_iMarried == 1)
                tempStr = "已婚";
            else
                tempStr = "未婚";
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 7, aTempItem);
            ++t;
        }
    }
}
void MainWindow::ShowMarried(int checkedID)
{
    m_iCurTable = 5;
    agentsInforModel->clear();
    agentsInforModel->setColumnCount(8);//8列
    //表头
    QStringList templist;
    templist.append("员工编号");
    templist.append("姓名");
    templist.append("性别");
    templist.append("生日");
    templist.append("职称");
    templist.append("学历");
    templist.append("工资");
    templist.append("婚姻状况");
    agentsInforModel->setHorizontalHeaderLabels(templist);

    int RowCnt = m_InfoTable.getAgentsNum();
    int RowUsed = 0;    //符合条件的数据数量
    int t = 0;//计数器，用于记录当前输出到第几行
    QStandardItem *aTempItem;
    QString tempStr;
    for(int i = 0; i<RowCnt; ++i)   //计数表格显示数据需要的行数
    {
        CAgent tempAgent =m_InfoTable.getAgent(i);
        if(tempAgent.m_iMarried == checkedID)
            ++RowUsed;
    }
    agentsInforModel->setRowCount(RowUsed);//设置表格行数

    //循环输出
    for(int i=0; i<RowCnt; ++i)
    {
        CAgent tempAgent = m_InfoTable.getAgent(i);
        if(tempAgent.m_iMarried == checkedID)
        {
            tempStr = QString::number(tempAgent.m_iID);
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 0, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_strName);
            agentsInforModel->setItem(t, 1, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_strSex);
            agentsInforModel->setItem(t, 2, aTempItem);
            tempStr = tempAgent.m_dateBirthdate.toString("yyyy-MM-dd");
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 3, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_strStatus);
            agentsInforModel->setItem(t, 4, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_strEducation);
            agentsInforModel->setItem(t, 5, aTempItem);
            tempStr = QString::number(tempAgent.m_iSalary);
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 6, aTempItem);
            if(tempAgent.m_iMarried == 1)
                tempStr = "已婚";
            else
                tempStr = "未婚";
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 7, aTempItem);
            ++t;
        }
    }
}
void MainWindow::ShowSalary(int radioID, int value)
{
    m_iCurTable = 6;
    agentsInforModel->clear();
    agentsInforModel->setColumnCount(8);//8列
    //表头
    QStringList templist;
    templist.append("员工编号");
    templist.append("姓名");
    templist.append("性别");
    templist.append("生日");
    templist.append("职称");
    templist.append("学历");
    templist.append("工资");
    templist.append("婚姻状况");
    agentsInforModel->setHorizontalHeaderLabels(templist);

    int RowCnt = m_InfoTable.getAgentsNum();
    int RowUsed = 0;    //符合条件的数据数量
    int t = 0;//计数器，用于记录当前输出到第几行
    QStandardItem *aTempItem;
    QString tempStr;
    switch(radioID)
    {
    case 0://以前
        for(int i = 0; i<RowCnt; ++i)   //计数表格显示数据需要的行数
        {
            CAgent tempAgent =m_InfoTable.getAgent(i);
            if(tempAgent.m_iSalary<value)
                ++RowUsed;
        }
        agentsInforModel->setRowCount(RowUsed);//设置表格行数

        //循环输出
        for(int i = 0; i<RowCnt; ++i)
        {
            CAgent tempAgent = m_InfoTable.getAgent(i);
            if(tempAgent.m_iSalary<value)
            {
                tempStr = QString::number(tempAgent.m_iID);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 0, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strName);
                agentsInforModel->setItem(t, 1, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strSex);
                agentsInforModel->setItem(t, 2, aTempItem);
                tempStr = tempAgent.m_dateBirthdate.toString("yyyy-MM-dd");
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 3, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strStatus);
                agentsInforModel->setItem(t, 4, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strEducation);
                agentsInforModel->setItem(t, 5, aTempItem);
                tempStr = QString::number(tempAgent.m_iSalary);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 6, aTempItem);
                if(tempAgent.m_iMarried == 1)
                    tempStr = "已婚";
                else
                    tempStr = "未婚";
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 7, aTempItem);
                ++t;
            }
        }
        break;
    case 1://以后（包含）
        for(int i = 0; i<RowCnt; ++i)   //计数表格显示数据需要的行数
        {
            CAgent tempAgent =m_InfoTable.getAgent(i);
            if(tempAgent.m_iSalary>=value)
                ++RowUsed;
        }
        agentsInforModel->setRowCount(RowUsed);//设置表格行数

        //循环输出
        for(int i = 0; i<RowCnt; ++i)
        {
            CAgent tempAgent = m_InfoTable.getAgent(i);
            if(tempAgent.m_iSalary>=value)
            {
                tempStr = QString::number(tempAgent.m_iID);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 0, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strName);
                agentsInforModel->setItem(t, 1, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strSex);
                agentsInforModel->setItem(t, 2, aTempItem);
                tempStr = tempAgent.m_dateBirthdate.toString("yyyy-MM-dd");
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 3, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strStatus);
                agentsInforModel->setItem(t, 4, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strEducation);
                agentsInforModel->setItem(t, 5, aTempItem);
                tempStr = QString::number(tempAgent.m_iSalary);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 6, aTempItem);
                if(tempAgent.m_iMarried == 1)
                    tempStr = "已婚";
                else
                    tempStr = "未婚";
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 7, aTempItem);
                ++t;
            }
        }
        break;
    default:
        break;
    }
}

void MainWindow::on_actionOpen_triggered()  //打开
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择一个文件";
    QString filter = "json文件(*.json)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    g_FileName = aFileName;
    if(aFileName.isEmpty())
        return;
    m_InfoTable.ReadAgentfromFile(aFileName);
    ShowAllAgents();
}
void MainWindow::on_actionSaveas_triggered()//另存为
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "另存为一个文件";
    QString filter = "json文件(*.json)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if(aFileName.isEmpty())
        return;
    m_InfoTable.SaveAgenttoFile(aFileName);
}
void MainWindow::on_actionSave_triggered()  //保存
{
    if(g_FileName.isEmpty())
    {
        QString curPath = QDir::currentPath();
        QString dlgTitle = "保存为一个文件";
        QString filter = "json文件(*.json)";
        QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
        if(aFileName.isEmpty())
            return;
        g_FileName = aFileName;
    }
    m_InfoTable.SaveAgenttoFile(g_FileName);
}
void MainWindow::on_actionClose_triggered() //关闭
{
    m_iCurTable = 0;
    agentsInforModel->clear();
    g_FileName.clear();
    m_InfoTable.clear();
}
void MainWindow::on_actionAdd_triggered()   //增加新职工
{
    AddDialog dlgAdd(this);
    int ret = dlgAdd.exec();
    if(ret == QDialog::Accepted)
    {
        CAgent tempAgent;
        tempAgent.m_iID = dlgAdd.id();
        tempAgent.m_strName = dlgAdd.Name();
        tempAgent.m_strSex = dlgAdd.Sex();
        tempAgent.m_dateBirthdate = dlgAdd.BirthDate();
        tempAgent.m_strStatus = dlgAdd.Status();
        tempAgent.m_strEducation = dlgAdd.Education();
        tempAgent.m_iSalary = dlgAdd.Salary();
        tempAgent.m_iMarried = dlgAdd.m_iMarried;
        m_InfoTable.AddAgent(tempAgent);
        ShowAllAgents();
    }
}
void MainWindow::on_actionDelete_triggered()//删除职工
{
    DeleteDialog dlgDel(this);
    int ret = dlgDel.exec();
    if(ret == QDialog::Accepted)
    {
        int index = dlgDel.deid();
        m_InfoTable.DeleteAgent(index);
        ShowAllAgents();
    }
}
void MainWindow::on_actionEdit_triggered()  //编辑职工信息
{
    EditDialog dlgEdit(this);
    int ret = dlgEdit.exec();
    if(ret == QDialog::Accepted)
    {
        CAgent tempAgent;
        try
        {
        tempAgent = m_InfoTable.getAgentbyID(dlgEdit.id()); //职工编号不存在时函数无法返回对象，抛出一个自定义的异常
        }
        catch(const char* msg)  //显示"Agent inexistent"的信息
        {
            qCritical() << msg;
            return;
        }
        switch(dlgEdit.m_iSelectIndex)  //根据选择框的不同对不同数据进行更改
        {
        case 0://职称
            tempAgent.m_strStatus = dlgEdit.newString();
            break;
        case 1://学历
            tempAgent.m_strEducation = dlgEdit.newString();
            break;
        case 2://工资
            tempAgent.m_iSalary = dlgEdit.newString().toInt();
            break;
        case 3://婚姻状况
            tempAgent.m_iMarried = dlgEdit.newString().toInt();
            break;
        default:
            break;
        }
        m_InfoTable.EditAgent(tempAgent);
        ShowAllAgents();
    }
}
void MainWindow::on_actionAll_Agents_triggered()    //显示所有职工
{
    ShowAllAgents();
}
void MainWindow::on_actionSeekbyBirthDate_triggered()   //按生日查找
{
    SeekbyBirthDateDialog dlgBirth;
    int ret = dlgBirth.exec();
    if(ret == QDialog::Accepted)
        ShowBirthDate(dlgBirth.m_iRadioID, dlgBirth.BirthDate());
}
void MainWindow::on_actionSeekbyStatus_triggered()      //按职称查找
{
    SeekbyStatusDialog dlgStatus;
    int ret = dlgStatus.exec();
    if(ret == QDialog::Accepted)
        ShowStatus(dlgStatus.status());
}
void MainWindow::on_actionSeekbyEducation_triggered()   //按学历查找
{
    SeekbyEducationDialog dlgEdu;
    int ret = dlgEdu.exec();
    if(ret == QDialog::Accepted)
        ShowEducation(dlgEdu.Education());
}
void MainWindow::on_actionSeekbyMarried_triggered()     //按婚姻状况查找
{
    SeekbyMarriedDialog dlgMa;
    int ret = dlgMa.exec();
    if(ret == QDialog::Accepted)
        ShowMarried(dlgMa.m_iMarried);
}
void MainWindow::on_actionSeekbySalary_triggered()      //按工资查找
{
    SeekbySalaryDialog dlgSalary;
    int ret = dlgSalary.exec();
    if(ret == QDialog::Accepted)
        ShowSalary(dlgSalary.m_iRadioID, dlgSalary.Salary());
}
void MainWindow::on_ShowInfoTableView_changed()         //直接在表格中更改数据
{

        QModelIndex index = ui->ShowInfoTableView->currentIndex();//获取选中单元格的索引
        QModelIndex IDindex = index.siblingAtColumn(0);     //返回选中单元格所在行的第一格的索引
        QVariant IDdata = agentsInforModel->data(IDindex);  //获取选中员工数据的员工编号
        int col = index.column();
        CAgent& agent = m_InfoTable.getAgentbyID(IDdata.toInt());   //用员工编号查找员工
        QVariant data;
        data = agentsInforModel->data(index);               //获取选中单元格内的数据
        switch (col)    //根据列编号对相应数据进行更改
        {
        case 0: //员工编号。只读，因此不做修改

            break;
        case 1: //姓名
            agent.m_strName = data.toString();
            break;
        case 2: //性别
            agent.m_strSex = data.toString();
            break;
        case 3: //生日
            agent.m_dateBirthdate = data.toDate();
            break;
        case 4: //职称
            agent.m_strStatus = data.toString();
            break;
        case 5: //学历
            agent.m_strEducation = data.toString();
            break;
        case 6: //工资
            agent.m_iSalary = data.toInt();
            break;
        case 7: //婚姻状况
            if(data.toString() == "已婚")
                agent.m_iMarried = 1;
            if(data.toString() == "未婚")
                agent.m_iMarried = 0;
            break;
        default:
            break;
        }
}

void MainWindow::on_MainWindow_customContextMenuRequested(const QPoint& pos)
{
    //添加右键菜单内容
    QMenu *pMenu = new QMenu(this);
    QAction *add = new QAction(tr("Add"), this);                        //添加职工信息
    QAction *edit = new QAction(tr("Edit"), this);                      //编辑职工信息
    QAction *del = new QAction(tr("Delete"), this);                     //删除职工信息
    QAction *delthis = new QAction(tr("Delete this agent"), this);      //直接删除当前选中职工信息
    QAction *all = new QAction(tr("All Agents"), this);                 //显示所有职工信息
    QAction *byThis = new QAction(tr("Seek by this"), this);            //筛选与当前单元格内数据相同的员工数据
    QAction *byBirthDate = new QAction(tr("Seek by BirthDate"), this);  //按生日查找
    QAction *byEducation = new QAction(tr("Seek by Education"), this);  //按学历查找
    QAction *byStatus = new QAction(tr("Seek by Status"), this);        //按职称查找
    QAction *bySalary = new QAction(tr("Seek by Salary"), this);        //按工资查找
    QAction *byMarried = new QAction(tr("Seek by Married"), this);      //按婚姻状况查找
    pMenu->addAction(add);
    pMenu->addAction(edit);
    pMenu->addAction(del);
    pMenu->addAction(delthis);
    pMenu->addAction(all);
    pMenu->addAction(byThis);
    pMenu->addAction(byBirthDate);
    pMenu->addAction(byEducation);
    pMenu->addAction(byStatus);
    pMenu->addAction(bySalary);
    pMenu->addAction(byMarried);
    //连接右键菜单选项和对应函数
    connect(add, SIGNAL(triggered()), this, SLOT(on_actionAdd_triggered()));
    connect(edit, SIGNAL(triggered()), this, SLOT(on_actionEdit_triggered()));
    connect(del, SIGNAL(triggered()), this, SLOT(on_actionDelete_triggered()));
    connect(delthis, SIGNAL(triggered()), this, SLOT(Deletethis()));
    connect(all, SIGNAL(triggered()), this, SLOT(on_actionAll_Agents_triggered()));
    connect(byBirthDate, SIGNAL(triggered()), this, SLOT(on_actionSeekbyBirthDate_triggered()));
    connect(byThis, SIGNAL(triggered()), this, SLOT(SeekbyThis()));
    connect(byEducation, SIGNAL(triggered()), this, SLOT(on_actionSeekbyEducation_triggered()));
    connect(byStatus, SIGNAL(triggered()),this, SLOT(on_actionSeekbyStatus_triggered()));
    connect(bySalary, SIGNAL(triggered()), this, SLOT(on_actionSeekbySalary_triggered()));
    connect(byMarried, SIGNAL(triggered()), this, SLOT(on_actionSeekbyMarried_triggered()));

    pMenu->exec(cursor().pos());    //在鼠标右键处显示右键菜单

    //释放内存
    QList<QAction*> list = pMenu->actions();
    foreach(QAction* pAction, list)
        delete pAction;
    delete pMenu;
}

void MainWindow::Deletethis()
{
    QModelIndex index = ui->ShowInfoTableView->currentIndex();//获取选中单元格的索引
    QModelIndex IDindex = index.siblingAtColumn(0);     //返回选中单元格所在行的第一格的索引
    QVariant IDdata = agentsInforModel->data(IDindex);  //获取选中员工数据的员工编号
    m_InfoTable.DeleteAgent(IDdata.toInt());            //删除对应编号员工
    ShowAllAgents();
}

void MainWindow::SeekbyThis()
{
    QModelIndex index = ui->ShowInfoTableView->currentIndex();//获取选中单元格的索引
    int col = index.column();   //获取选中单元格的列
    QVariant data = agentsInforModel->data(index);  //获取单元格内数据
    QStringList templist;
    int RowUsed = 0;    //符合条件的数据数量
    int t = 0;//计数器，用于记录当前输出到第几行
    int RowCnt = m_InfoTable.getAgentsNum();
    QStandardItem *aTempItem;
    QString tempStr;

    switch (col)    //根据列号对相应数据进行筛选
    {
    case 0: //员工编号，不做筛选

        break;
    case 1: //姓名
        agentsInforModel->clear();
        agentsInforModel->setColumnCount(8);//8列
        //表头
        templist.append("员工编号");
        templist.append("姓名");
        templist.append("性别");
        templist.append("生日");
        templist.append("职称");
        templist.append("学历");
        templist.append("工资");
        templist.append("婚姻状况");
        agentsInforModel->setHorizontalHeaderLabels(templist);

        for(int i = 0; i<RowCnt; ++i)   //计数表格显示数据需要的行数
        {
            CAgent tempAgent =m_InfoTable.getAgent(i);
            if(tempAgent.m_strName == data.toString())
                ++RowUsed;
        }
        agentsInforModel->setRowCount(RowUsed);//设置表格行数

        //循环输出
        for(int i=0; i<RowCnt; ++i)
        {

            CAgent tempAgent = m_InfoTable.getAgent(i);
            if(tempAgent.m_strName == data.toString())
            {
                tempStr = QString::number(tempAgent.m_iID);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 0, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strName);
                agentsInforModel->setItem(t, 1, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strSex);
                agentsInforModel->setItem(t, 2, aTempItem);
                tempStr = tempAgent.m_dateBirthdate.toString("yyyy-MM-dd");
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 3, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strStatus);
                agentsInforModel->setItem(t, 4, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strEducation);
                agentsInforModel->setItem(t, 5, aTempItem);
                tempStr = QString::number(tempAgent.m_iSalary);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 6, aTempItem);
                if(tempAgent.m_iMarried == 1)
                    tempStr = "已婚";
                else
                    tempStr = "未婚";
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 7, aTempItem);
                ++t;
            }
        }
        break;
    case 2: //性别
        agentsInforModel->clear();
        agentsInforModel->setColumnCount(8);//8列
        //表头

        templist.append("员工编号");
        templist.append("姓名");
        templist.append("性别");
        templist.append("生日");
        templist.append("职称");
        templist.append("学历");
        templist.append("工资");
        templist.append("婚姻状况");
        agentsInforModel->setHorizontalHeaderLabels(templist);



        for(int i = 0; i<RowCnt; ++i)   //计数表格显示数据需要的行数
        {
            CAgent tempAgent =m_InfoTable.getAgent(i);
            if(tempAgent.m_strSex == data.toString())
                ++RowUsed;
        }
        agentsInforModel->setRowCount(RowUsed);//设置表格行数

        //循环输出
        for(int i=0; i<RowCnt; ++i)
        {
            CAgent tempAgent = m_InfoTable.getAgent(i);
            if(tempAgent.m_strSex == data.toString())
            {
                tempStr = QString::number(tempAgent.m_iID);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 0, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strName);
                agentsInforModel->setItem(t, 1, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strSex);
                agentsInforModel->setItem(t, 2, aTempItem);
                tempStr = tempAgent.m_dateBirthdate.toString("yyyy-MM-dd");
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 3, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strStatus);
                agentsInforModel->setItem(t, 4, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strEducation);
                agentsInforModel->setItem(t, 5, aTempItem);
                tempStr = QString::number(tempAgent.m_iSalary);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 6, aTempItem);
                if(tempAgent.m_iMarried == 1)
                    tempStr = "已婚";
                else
                    tempStr = "未婚";
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 7, aTempItem);
                ++t;
            }
        }
        break;
    case 3: //生日
        agentsInforModel->clear();
        agentsInforModel->setColumnCount(8);//8列
        //表头
        templist.append("员工编号");
        templist.append("姓名");
        templist.append("性别");
        templist.append("生日");
        templist.append("职称");
        templist.append("学历");
        templist.append("工资");
        templist.append("婚姻状况");
        agentsInforModel->setHorizontalHeaderLabels(templist);

        for(int i = 0; i<RowCnt; ++i)   //计数表格显示数据需要的行数
        {
            CAgent tempAgent =m_InfoTable.getAgent(i);
            if(tempAgent.m_dateBirthdate == data.toDate())
                ++RowUsed;
        }
        agentsInforModel->setRowCount(RowUsed);//设置表格行数

        //循环输出
        for(int i=0; i<RowCnt; ++i)
        {

            CAgent tempAgent = m_InfoTable.getAgent(i);
            if(tempAgent.m_dateBirthdate == data.toDate())
            {
                tempStr = QString::number(tempAgent.m_iID);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 0, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strName);
                agentsInforModel->setItem(t, 1, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strSex);
                agentsInforModel->setItem(t, 2, aTempItem);
                tempStr = tempAgent.m_dateBirthdate.toString("yyyy-MM-dd");
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 3, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strStatus);
                agentsInforModel->setItem(t, 4, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strEducation);
                agentsInforModel->setItem(t, 5, aTempItem);
                tempStr = QString::number(tempAgent.m_iSalary);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 6, aTempItem);
                if(tempAgent.m_iMarried == 1)
                    tempStr = "已婚";
                else
                    tempStr = "未婚";
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 7, aTempItem);
                ++t;
            }
        }
        break;
    case 4: //职称
        ShowStatus(data.toString());
        break;
    case 5: //学历
        ShowEducation(data.toString());
        break;
    case 6: //工资
        agentsInforModel->clear();
        agentsInforModel->setColumnCount(8);//8列
        //表头
        templist.append("员工编号");
        templist.append("姓名");
        templist.append("性别");
        templist.append("生日");
        templist.append("职称");
        templist.append("学历");
        templist.append("工资");
        templist.append("婚姻状况");
        agentsInforModel->setHorizontalHeaderLabels(templist);

        for(int i = 0; i<RowCnt; ++i)   //计数表格显示数据需要的行数
        {
            CAgent tempAgent =m_InfoTable.getAgent(i);
            if(tempAgent.m_iSalary == data.toInt())
                ++RowUsed;
        }
        agentsInforModel->setRowCount(RowUsed);//设置表格行数

        //循环输出
        for(int i=0; i<RowCnt; ++i)
        {

            CAgent tempAgent = m_InfoTable.getAgent(i);
            if(tempAgent.m_iSalary == data.toInt())
            {
                tempStr = QString::number(tempAgent.m_iID);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 0, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strName);
                agentsInforModel->setItem(t, 1, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strSex);
                agentsInforModel->setItem(t, 2, aTempItem);
                tempStr = tempAgent.m_dateBirthdate.toString("yyyy-MM-dd");
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 3, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strStatus);
                agentsInforModel->setItem(t, 4, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_strEducation);
                agentsInforModel->setItem(t, 5, aTempItem);
                tempStr = QString::number(tempAgent.m_iSalary);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 6, aTempItem);
                if(tempAgent.m_iMarried == 1)
                    tempStr = "已婚";
                else
                    tempStr = "未婚";
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 7, aTempItem);
                ++t;
            }
        }
        break;
    case 7: //婚姻状况
        if(data.toString() == "已婚")
            ShowMarried(1);
        if(data.toString() == "未婚")
            ShowMarried(0);
        break;
    default:
        break;
    }
}
