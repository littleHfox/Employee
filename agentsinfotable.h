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
    void EditAgent(CAgent& agent);
    CAgent& getAgent(int index);
    CAgent& getAgentbyID(int id);
    int getAgentsNum();

private:
    QVector<CAgent> m_Agents;
    int m_iNum;
};

#endif // AGENTSINFOTABLE_H
