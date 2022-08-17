#include "agentsinfotable.h"

AgentsInfotable::AgentsInfotable()
{
    m_iNum = 0;
}

bool AgentsInfotable::ReadAgentfromFile(const QString& aReadFileName)
{
    m_Agents.clear();
    QFile file(aReadFileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "JsonFile open error";
        return false;
    }
    QJsonDocument jdc(QJsonDocument::fromJson(file.readAll()));
    QJsonObject obj;
    QJsonArray ary = jdc.array();
    m_iNum = ary[0].toInt();
    CAgent tempAgent;
    if(m_iNum>0)
    {
        for(int i=0;i<m_iNum;++i)
        {
            obj = ary[i+1].toObject();
            tempAgent.ReadAgent(obj);
            m_Agents.push_back(tempAgent);
        }
    }
    file.close();
    return true;
}
bool AgentsInfotable::SaveAgenttoFile(const QString& aSaveFileName)
{
    QFile file(aSaveFileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        qCritical() << "JsonFile open error";
        return false;
    }
    QJsonArray ary;
    QJsonObject obj;
    ary.append(m_iNum);
    if(m_iNum>0)
    {
        for(int i=0; i<m_iNum; ++i)
        {
            m_Agents[i].SaveAgent(obj);
            ary.append(obj);
        }
    }
    QJsonDocument jsonDoc;
    jsonDoc.setArray(ary);
    file.write(jsonDoc.toJson());
    file.close();
    return true;
}
void AgentsInfotable::clear()
{
    m_Agents.clear();
    m_iNum = 0;
}

void AgentsInfotable::AddAgent(CAgent& agent)
{
    if(m_iNum>0)
    {
        for(int i=0; i<m_iNum; ++i)
        {
            if(m_Agents[i].m_id == agent.m_id)
            {
                qCritical() << "Agent ID already existent";
                return;
            }
        }
    }
    m_Agents.push_back(agent);
    ++m_iNum;
}
void AgentsInfotable::DeleteAgent(int index)
{
    bool findit = false;
    if(m_iNum>0)
    {
        for(int i=0; i<m_iNum; ++i)
        {
            if(m_Agents[i].m_id == index)
            {
                m_Agents.erase(m_Agents.begin() + i);
                findit = true;
                --m_iNum;
            }
        }
    }
    if(!findit)
        qCritical() << "Agent inexistent";
}
void AgentsInfotable::EditAgent(CAgent& agent)
{
    bool findit = false;
    if(m_iNum>0)
    {
        for(int i=0; i<m_iNum; ++i)
        {
            if(m_Agents[i].m_id == agent.m_id)
            {
                m_Agents.replace(i,agent);
                findit = true;
            }
        }
    }
    if(!findit)
        qCritical() << "Agent inexistent";
}
CAgent& AgentsInfotable::getAgent(int index)
{
    return m_Agents[index];
}
CAgent& AgentsInfotable::getAgentbyID(int id)
{
    for(int i=0; i<m_iNum; ++i)
    {
        if(m_Agents[i].m_id == id)
            return m_Agents[i];
    }
    try
    {
        throw "Agent inexistent";
    }
    catch(...)
    {
        throw;
    }
}
int AgentsInfotable::getAgentsNum()
{
    return m_iNum;
}
