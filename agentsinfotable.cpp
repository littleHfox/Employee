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
    m_iNum = ary[0].toInt();            //从文件的第一个数据读取职工数量
    CAgent tempAgent;
    if(m_iNum>0)
    {
        for(int i=0;i<m_iNum;++i)       //依次读取职工信息
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
    ary.append(m_iNum);                 //将职工数量作为文件的第一个数据单独输出
    if(m_iNum>0)
    {
        for(int i=0; i<m_iNum; ++i)     //将每个职工的数据作为一个object输出
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
        for(int i=0; i<m_iNum; ++i) //检查职工编号是否已被使用
        {
            if(m_Agents[i].m_iID == agent.m_iID)
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
        for(int i=0; i<m_iNum; ++i) //检查职工编号是否存在
        {
            if(m_Agents[i].m_iID == index)
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
        for(int i=0; i<m_iNum; ++i) //检查职工编号是否存在
        {
            if(m_Agents[i].m_iID == agent.m_iID)
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
    for(int i=0; i<m_iNum; ++i) //穷举查找对应职工编号
    {
        if(m_Agents[i].m_iID == id)
            return m_Agents[i];
    }

    //若职工编号不存在，函数无法返回值，所以抛出一个异常，用于后续处理
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
