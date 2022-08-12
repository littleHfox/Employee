#include "cagent.h"

CAgent::CAgent()
{

}
CAgent::~CAgent()
{

}
CAgent& CAgent::operator=(const CAgent& agent)
{
    m_id = agent.m_id;
    m_Name = agent.m_Name;
    m_Sex = agent.m_Sex;
    m_Birthdate = agent.m_Birthdate;
    m_Status = agent.m_Status;
    m_Education = agent.m_Education;
    m_Salary = agent.m_Salary;
    m_Married = agent.m_Married;
    return *this;
}
CAgent::CAgent(const CAgent& agent)
{
    m_id = agent.m_id;
    m_Name = agent.m_Name;
    m_Sex = agent.m_Sex;
    m_Birthdate = agent.m_Birthdate;
    m_Status = agent.m_Status;
    m_Education = agent.m_Education;
    m_Salary = agent.m_Salary;
    m_Married = agent.m_Married;
}
void CAgent::ReadAgent(QJsonObject& aObj)
{
    int year,month,day;
    m_id = aObj.value("id").toInt();
    m_Name = aObj.value("Name").toString();
    m_Sex = aObj.value("Sex").toString();
    year = aObj.value("BirthDate.year").toInt();
    month = aObj.value("BirthDate.month").toInt();
    day = aObj.value("BirthDate.day").toInt();
    m_Birthdate.setDate(year,month,day);
    m_Status = aObj.value("Status").toString();
    m_Education = aObj.value("Education").toString();
    m_Salary = aObj.value("Salary").toInt();
    m_Married = aObj.value("Married").toInt();
}
void CAgent::SaveAgent(QJsonObject& aObj)
{
    aObj.insert("id",m_id);
    aObj.insert("Name",m_Name);
    aObj.insert("Sex",m_Sex);
    aObj.insert("BirthDate.year",m_Birthdate.year());
    aObj.insert("BirthDate.month",m_Birthdate.month());
    aObj.insert("BirthDate.day",m_Birthdate.day());
    aObj.insert("Status",m_Status);
    aObj.insert("Education",m_Education);
    aObj.insert("Salary",m_Salary);
    aObj.insert("Married",m_Married);
}
