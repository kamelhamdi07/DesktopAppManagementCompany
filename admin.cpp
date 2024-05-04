#include "admin.h"

#include <QString>

user::user()
{ Login="";
Password="";
}
void user::setLogin(QString n)
{ Login=n;
}
void user::setPassword(QString n)
{
 Password=n;
}
QString user::Getlogin()
{
    return Login   ;
}
QString user::GetPassword()
{
    return  Password;
}
