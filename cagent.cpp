#include "cagent.h"

CAgent::CAgent()
{

}
CAgent::~CAgent()
{

}
CAgent& CAgent::operator=(const CAgent& agent)
{
    m_iID = agent.m_iID;
    m_strName = agent.m_strName;
    m_strSex = agent.m_strSex;
    m_dateBirthdate = agent.m_dateBirthdate;
    m_strStatus = agent.m_strStatus;
    m_strEducation = agent.m_strEducation;
    m_iSalary = agent.m_iSalary;
    m_iMarried = agent.m_iMarried;
    return *this;
}
CAgent::CAgent(const CAgent& agent)
{
    m_iID = agent.m_iID;
    m_strName = agent.m_strName;
    m_strSex = agent.m_strSex;
    m_dateBirthdate = agent.m_dateBirthdate;
    m_strStatus = agent.m_strStatus;
    m_strEducation = agent.m_strEducation;
    m_iSalary = agent.m_iSalary;
    m_iMarried = agent.m_iMarried;
}
void CAgent::ReadAgent(QJsonObject& aObj)
{
    int year,month,day;
    m_iID = aObj.value("id").toInt();
    m_strName = aObj.value("Name").toString();
    m_strSex = aObj.value("Sex").toString();
    year = aObj.value("BirthDate.year").toInt();
    month = aObj.value("BirthDate.month").toInt();
    day = aObj.value("BirthDate.day").toInt();
    m_dateBirthdate.setDate(year,month,day);
    m_strStatus = aObj.value("Status").toString();
    m_strEducation = aObj.value("Education").toString();
    m_iSalary = aObj.value("Salary").toInt();
    m_iMarried = aObj.value("Married").toInt();
}
void CAgent::SaveAgent(QJsonObject& aObj)
{
    aObj.insert("id",m_iID);
    aObj.insert("Name",m_strName);
    aObj.insert("Sex",m_strSex);
    aObj.insert("BirthDate.year",m_dateBirthdate.year());
    aObj.insert("BirthDate.month",m_dateBirthdate.month());
    aObj.insert("BirthDate.day",m_dateBirthdate.day());
    aObj.insert("Status",m_strStatus);
    aObj.insert("Education",m_strEducation);
    aObj.insert("Salary",m_iSalary);
    aObj.insert("Married",m_iMarried);
}
