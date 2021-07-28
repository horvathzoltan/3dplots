#ifndef DOWORK_H
#define DOWORK_H

#include "action.h"
#include "mainwindow.h"

class doWork
{
private:
    static MainWindow* mw_;
    static bool isInit_;
public:
    doWork();
    static bool init(MainWindow* mw);
    static ActionResult add(const QUrlQuery& param, const QByteArray& content);
    static ActionResult clear(const QUrlQuery& param, const QByteArray& content);
    static ActionResult testconnection(const QUrlQuery& param, const QByteArray& content);

    static ActionResult del(const QUrlQuery& param, const QByteArray& content);
    static ActionResult mov(const QUrlQuery& param, const QByteArray& content);
};

#endif // DOWORK_H
