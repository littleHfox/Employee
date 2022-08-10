#ifndef CAGENT_H
#define CAGENT_H
#include<qstring.h>
#include<qdatetime.h>
#include <QTextStream>
class CAgent
{
public:
    CAgent();
    CAgent(const CAgent& agent);
    virtual ~CAgent();
    void SaveAgent(QTextStream& aStream);
    void ReadAgent(QTextStream& aStream);
private:
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
