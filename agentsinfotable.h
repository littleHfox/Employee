#ifndef AGENTSINFOTABLE_H
#define AGENTSINFOTABLE_H
#include<QVector>
#include"cagent.h"
class AgentsInfotable
{
public:
    AgentsInfotable();
    bool ReadAgentfromFile(const QString& aReadFileName);
    bool SaveAgenttoFile(const QString& aSaveFileName);
    void clear();   //用于在关闭当前文件时清空内存中写入的职工信息
    void AddAgent(CAgent& agent);
    void DeleteAgent(int index);
    void EditAgent(CAgent& agent);
    CAgent& getAgent(int index);    //按创建顺序获取职工指针
    CAgent& getAgentbyID(int id);   //按职工编号获取职工指针
    int getAgentsNum();

private:
    QVector<CAgent> m_Agents;   //写入内存的职工信息
    int m_iNum; //职工数量
};

#endif // AGENTSINFOTABLE_H
