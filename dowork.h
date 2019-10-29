#ifndef DOWORK_H
#define DOWORK_H

#include "action.h"

class doWork
{
public:
    doWork();

    static ActionResult add(const QUrlQuery& param, const QByteArray& content);
    static ActionResult testconnection(const QUrlQuery& param, const QByteArray& content);    
};

#endif // DOWORK_H
