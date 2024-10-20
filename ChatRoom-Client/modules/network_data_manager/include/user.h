#ifndef USER_H  
#define USER_H

#include <QString>

class User{
public:
    QString m_userID;
    QString m_userIP;
    User(QString userID, QString userIP):
        m_userID(userID),
        m_userIP(userIP)
    {}  
    QString getUserID() const {
        return m_userID;
    }
    QString getUserIP() const {
        return m_userIP;
    }
};

#endif