#ifndef THREADEDSOCKETHANDLER_H
#define THREADEDSOCKETHANDLER_H


//#include <QObject>
//#include <QTcpSocket>
//#include <QDebug>
//#include <QThreadPool>
//#include "zactiontask.h"
#include "action.h"
#include "httpthreadedserver.h"
#include "response.h"

class ThreadedSocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit ThreadedSocketHandler(QObject *parent = nullptr);
    void setSocket(qintptr Descriptor);
    void setServer(HTTPThreadedServer *s);
    void trace(QString);
    void startTask(const Request& r, const Action action);
    void notFound();
    //signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();


    // make the server fully ascynchronous
    // by doing time consuming task
    void TaskResult(ActionResult e);

private:
    static const QString LOGPATTERN;

    QTcpSocket *socket;
    HTTPThreadedServer *server;

    void sendResponse(Response e);
};

#endif // THREADEDSOCKETHANDLER_H
