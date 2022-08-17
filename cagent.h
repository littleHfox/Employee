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
    int m_iID;              //员工编号
    QString m_strName;      //姓名
    QString m_strSex;       //性别
    QDate m_dateBirthdate;   //生日
    QString m_strStatus;    //职称
    QString m_strEducation; //学历
    int m_iSalary;          //工资
    int m_iMarried;         //婚姻状况，0--未婚 1--已婚
};

#endif // CAGENT_H
