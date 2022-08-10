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
    void AddAgent(CAgent& agent);
    void DeleteAgent(int index);
    void EditAgent(int index);
    CAgent& getAgent(int index);
    int getAgentNum();
private:
    QVector<CAgent> m_Agents;
    int m_num;
};

#endif // AGENTSINFOTABLE_H
