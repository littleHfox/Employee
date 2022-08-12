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
}

MainWindow::~MainWindow()
{
    delete ui;
    delete agentsInforModel;
}
void MainWindow::ShowAllAgents()
{
    m_iCurTable = 1;
    agentsInforModel->clear();
    agentsInforModel->setColumnCount(8);//8列

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
    agentsInforModel->setRowCount(RowCnt);

    QStandardItem *aTempItem;
    QString tempStr;
    for(int i=0; i<RowCnt; ++i)
    {
        CAgent tempAgent = m_InfoTable.getAgent(i);
        tempStr = QString::number(tempAgent.m_id);
        aTempItem = new QStandardItem(tempStr);
        agentsInforModel->setItem(i, 0, aTempItem);
        aTempItem = new QStandardItem(tempAgent.m_Name);
        agentsInforModel->setItem(i, 1, aTempItem);
        aTempItem = new QStandardItem(tempAgent.m_Sex);
        agentsInforModel->setItem(i, 2, aTempItem);
        tempStr = tempAgent.m_Birthdate.toString("yyyy-MM-dd");
        aTempItem = new QStandardItem(tempStr);
        agentsInforModel->setItem(i, 3, aTempItem);
        aTempItem = new QStandardItem(tempAgent.m_Status);
        agentsInforModel->setItem(i, 4, aTempItem);
        aTempItem = new QStandardItem(tempAgent.m_Education);
        agentsInforModel->setItem(i, 5, aTempItem);
        tempStr = QString::number(tempAgent.m_Salary);
        aTempItem = new QStandardItem(tempStr);
        agentsInforModel->setItem(i, 6, aTempItem);
        if(tempAgent.m_Married == 1)
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
    int t = 0;//计数器
    QStandardItem *aTempItem;
    QString tempStr;
    switch(radioID)
    {
    case 0://以前
        for(int i = 0; i<RowCnt; ++i)
        {
            CAgent tempAgent =m_InfoTable.getAgent(i);
            if(tempAgent.m_Birthdate<valueDate)
                ++RowUsed;
        }
        agentsInforModel->setRowCount(RowUsed);
        for(int i = 0; i<RowCnt; ++i)
        {
            CAgent tempAgent = m_InfoTable.getAgent(i);
            if(tempAgent.m_Birthdate<valueDate)
            {
                tempStr = QString::number(tempAgent.m_id);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 0, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_Name);
                agentsInforModel->setItem(t, 1, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_Sex);
                agentsInforModel->setItem(t, 2, aTempItem);
                tempStr = tempAgent.m_Birthdate.toString("yyyy-MM-dd");
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 3, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_Status);
                agentsInforModel->setItem(t, 4, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_Education);
                agentsInforModel->setItem(t, 5, aTempItem);
                tempStr = QString::number(tempAgent.m_Salary);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 6, aTempItem);
                if(tempAgent.m_Married == 1)
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
        for(int i = 0; i<RowCnt; ++i)
        {
            CAgent tempAgent =m_InfoTable.getAgent(i);
            if(tempAgent.m_Birthdate>=valueDate)
                ++RowUsed;
        }
        agentsInforModel->setRowCount(RowUsed);
        for(int i = 0; i<RowCnt; ++i)
        {
            CAgent tempAgent = m_InfoTable.getAgent(i);
            if(tempAgent.m_Birthdate>=valueDate)
            {
                tempStr = QString::number(tempAgent.m_id);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 0, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_Name);
                agentsInforModel->setItem(t, 1, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_Sex);
                agentsInforModel->setItem(t, 2, aTempItem);
                tempStr = tempAgent.m_Birthdate.toString("yyyy-MM-dd");
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 3, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_Status);
                agentsInforModel->setItem(t, 4, aTempItem);
                aTempItem = new QStandardItem(tempAgent.m_Education);
                agentsInforModel->setItem(t, 5, aTempItem);
                tempStr = QString::number(tempAgent.m_Salary);
                aTempItem = new QStandardItem(tempStr);
                agentsInforModel->setItem(t, 6, aTempItem);
                if(tempAgent.m_Married == 1)
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
    int t = 0;//计数器
    QStandardItem *aTempItem;
    QString tempStr;
    for(int i = 0; i<RowCnt; ++i)
    {
        CAgent tempAgent =m_InfoTable.getAgent(i);
        if(tempAgent.m_Status == value)
            ++RowUsed;
    }
    agentsInforModel->setRowCount(RowUsed);
    for(int i=0; i<RowCnt; ++i)
    {
        CAgent tempAgent = m_InfoTable.getAgent(i);
        if(tempAgent.m_Status == value)
        {
            tempStr = QString::number(tempAgent.m_id);
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 0, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_Name);
            agentsInforModel->setItem(t, 1, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_Sex);
            agentsInforModel->setItem(t, 2, aTempItem);
            tempStr = tempAgent.m_Birthdate.toString("yyyy-MM-dd");
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 3, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_Status);
            agentsInforModel->setItem(t, 4, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_Education);
            agentsInforModel->setItem(t, 5, aTempItem);
            tempStr = QString::number(tempAgent.m_Salary);
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 6, aTempItem);
            if(tempAgent.m_Married == 1)
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
    int t = 0;//计数器
    QStandardItem *aTempItem;
    QString tempStr;
    for(int i = 0; i<RowCnt; ++i)
    {
        CAgent tempAgent =m_InfoTable.getAgent(i);
        if(tempAgent.m_Education == value)
            ++RowUsed;
    }
    agentsInforModel->setRowCount(RowUsed);
    for(int i=0; i<RowCnt; ++i)
    {

        CAgent tempAgent = m_InfoTable.getAgent(i);
        if(tempAgent.m_Education == value)
        {
            tempStr = QString::number(tempAgent.m_id);
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 0, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_Name);
            agentsInforModel->setItem(t, 1, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_Sex);
            agentsInforModel->setItem(t, 2, aTempItem);
            tempStr = tempAgent.m_Birthdate.toString("yyyy-MM-dd");
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 3, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_Status);
            agentsInforModel->setItem(t, 4, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_Education);
            agentsInforModel->setItem(t, 5, aTempItem);
            tempStr = QString::number(tempAgent.m_Salary);
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 6, aTempItem);
            if(tempAgent.m_Married == 1)
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
    int t = 0;//计数器
    QStandardItem *aTempItem;
    QString tempStr;
    for(int i = 0; i<RowCnt; ++i)
    {
        CAgent tempAgent =m_InfoTable.getAgent(i);
        if(tempAgent.m_Married == checkedID)
            ++RowUsed;
    }
    agentsInforModel->setRowCount(RowUsed);
    for(int i=0; i<RowCnt; ++i)
    {
        CAgent tempAgent = m_InfoTable.getAgent(i);
        if(tempAgent.m_Married == checkedID)
        {
            tempStr = QString::number(tempAgent.m_id);
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 0, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_Name);
            agentsInforModel->setItem(t, 1, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_Sex);
            agentsInforModel->setItem(t, 2, aTempItem);
            tempStr = tempAgent.m_Birthdate.toString("yyyy-MM-dd");
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 3, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_Status);
            agentsInforModel->setItem(t, 4, aTempItem);
            aTempItem = new QStandardItem(tempAgent.m_Education);
            agentsInforModel->setItem(t, 5, aTempItem);
            tempStr = QString::number(tempAgent.m_Salary);
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 6, aTempItem);
            if(tempAgent.m_Married == 1)
                tempStr = "已婚";
            else
                tempStr = "未婚";
            aTempItem = new QStandardItem(tempStr);
            agentsInforModel->setItem(t, 7, aTempItem);
            ++t;
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择一个文件";
    QString filter = "json文件(*.json)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if(aFileName.isEmpty())
        return;
    m_InfoTable.ReadAgentfromFile(aFileName);
    ShowAllAgents();
}
void MainWindow::on_actionSave_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "另存为一个文件";
    QString filter = "json文件(*.json)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if(aFileName.isEmpty())
        return;
    m_InfoTable.SaveAgenttoFile(aFileName);
}
void MainWindow::on_actionAdd_triggered()
{
    AddDialog dlgAdd(this);
    int ret = dlgAdd.exec();
    if(ret == QDialog::Accepted)
    {
        CAgent tempAgent;
        tempAgent.m_id = dlgAdd.id();
        tempAgent.m_Name = dlgAdd.Name();
        tempAgent.m_Sex = dlgAdd.Sex();
        tempAgent.m_Birthdate = dlgAdd.BirthDate();
        tempAgent.m_Status = dlgAdd.Status();
        tempAgent.m_Education = dlgAdd.Education();
        tempAgent.m_Salary = dlgAdd.Salary();
        tempAgent.m_Married = dlgAdd.m_iMarried;
        m_InfoTable.AddAgent(tempAgent);
        ShowAllAgents();
    }
}
void MainWindow::on_actionDelete_triggered()
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
void MainWindow::on_actionEdit_triggered()
{
    EditDialog dlgEdit(this);
    int ret = dlgEdit.exec();
    if(ret == QDialog::Accepted)
    {
        CAgent tempAgent;
        try
        {
        tempAgent = m_InfoTable.getAgentbyID(dlgEdit.id());
        }
        catch(const char* msg)
        {
            qCritical() << msg;
            return;
        }
        switch(dlgEdit.m_iSelectIndex)
        {
        case 0://职称
            tempAgent.m_Status = dlgEdit.newString();
            break;
        case 1://学历
            tempAgent.m_Education = dlgEdit.newString();
            break;
        case 2://工资
            tempAgent.m_Salary = dlgEdit.newString().toInt();
            break;
        case 3://婚姻状况
            tempAgent.m_Married = dlgEdit.newString().toInt();
            break;
        default:
            break;
        }
        m_InfoTable.EditAgent(tempAgent);
        ShowAllAgents();
    }
}
void MainWindow::on_actionAll_Agents_triggered()
{
    ShowAllAgents();
}
void MainWindow::on_actionSeekbyBirthDate_triggered()
{
    SeekbyBirthDateDialog dlgBirth;
    int ret = dlgBirth.exec();
    if(ret == QDialog::Accepted)
        ShowBirthDate(dlgBirth.m_iRadioID, dlgBirth.BirthDate());
}
void MainWindow::on_actionSeekbyStatus_triggered()
{
    SeekbyStatusDialog dlgStatus;
    int ret = dlgStatus.exec();
    if(ret == QDialog::Accepted)
        ShowStatus(dlgStatus.status());
}
void MainWindow::on_actionSeekbyEducation_triggered()
{
    SeekbyEducationDialog dlgEdu;
    int ret = dlgEdu.exec();
    if(ret == QDialog::Accepted)
        ShowEducation(dlgEdu.Education());
}
void MainWindow::on_actionSeekbyMarried_triggered()
{
    SeekbyMarriedDialog dlgMa;
    int ret = dlgMa.exec();
    if(ret == QDialog::Accepted)
        ShowMarried(dlgMa.m_iMarried);
}
void MainWindow::on_ShowInfoTableView_changed()
{
    if(m_iCurTable == 1)
    {
        QModelIndex index = ui->ShowInfoTableView->currentIndex();
        int row = index.row();
        int col = index.column();
        CAgent& agent = m_InfoTable.getAgent(row);
        QVariant data;
        data = agentsInforModel->data(index);
        switch (col) {
        case 0:

            break;
        case 1:
            agent.m_Name = data.toString();
            break;
        case 2:
            agent.m_Sex = data.toString();
            break;
        case 3:
            agent.m_Birthdate = data.toDate();
            break;
        case 4:
            agent.m_Status = data.toString();
            break;
        case 5:
            agent.m_Education = data.toString();
            break;
        case 6:
            agent.m_Salary = data.toInt();
            break;
        case 7:
            if(data.toString() == "已婚")
                agent.m_Married = 1;
            if(data.toString() == "未婚")
                agent.m_Married = 0;
            break;
        default:
            break;
        }
    }
}
