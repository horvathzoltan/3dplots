#ifndef HTTPTHREADSERVER_H
#define HTTPTHREADSERVER_H


#include <iostream>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include "action.h"
#include "request.h"

class HTTPThreadedServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit HTTPThreadedServer(const QString&, QObject *parent = nullptr);
    void setHostAddress(const QHostAddress &, quint16);
    void start();
    void stop();
    void addAction(QString, QString, actionFn);

    const Action* action(Request r);
    const QString serverName(void) const { return _serverName; }
    //QList<zRequest> pending_requests;
    QMap<qintptr, Request> pending_requests;
    QString static getName(const QHostAddress &a);
protected:
    void incomingConnection(qintptr socketDescriptor);

    QHostAddress host;
    quint16 port;
    QString _serverName;
    QList<Action> actions;

};

#endif // HTTPTHREADSERVER_H
