#ifndef CAGENT_H
#define CAGENT_H
#include<qstring.h>
#include<qdatetime.h>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>
#include<QFile>

class CAgent
{
public:
    CAgent();
    virtual ~CAgent();
    CAgent& operator=(const CAgent& agent);
    CAgent(const CAgent& agent);
    void ReadAgent(QJsonObject& aObj);
    void SaveAgent(QJsonObject& aObj);
    int m_id;
    QString m_Name;
    QString m_Sex;
    QDate m_Birthdate;
    QString m_Status;
    QString m_Education;
    int m_Salary;
    int m_Married;
};

#endif // CAGENT_H
