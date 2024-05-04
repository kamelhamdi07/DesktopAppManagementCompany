#ifndef ADMIN_H
#define ADMIN_H
#include<QString>
#include<login.h>

class user
{
private:
    QString Login,Password;
public:
    void setLogin(QString n);
     void setPassword(QString n);
     QString Getlogin();
     QString GetPassword();
    user();
};


#endif // ADMIN_H
