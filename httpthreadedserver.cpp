#include "httpthreadedserver.h"
#include "common/logger/log.h"
#include "response.h"
#include "actionhelper.h"
#include <QTextCodec>
#include "threadedsockethandler.h"
#include "common/macrofactory/macro.h"


HTTPThreadedServer::HTTPThreadedServer(const QString& name, QObject *parent) : QTcpServer(parent)
{
    this->_serverName = name;
    qRegisterMetaType<ActionResult>(qPrintable(nameof(ActionResult)));
    zInfo(QStringLiteral("HTTPThreadedServer created: %1").arg(name));
}

void HTTPThreadedServer::setHostAddress(const QHostAddress& a, quint16 p)
{
    this->host = a;
    this->port = p;
    zInfo(QStringLiteral("%1 HostAddress: %2:%3").arg(this->_serverName).arg(getName(a)).arg(p));
}

QString HTTPThreadedServer::getName(const QHostAddress& a){
    if(a==QHostAddress::Null) return nameof(QHostAddress::Null);
    if(a==QHostAddress::Broadcast) return nameof(QHostAddress::Broadcast);
    if(a==QHostAddress::LocalHost) return nameof(QHostAddress::LocalHost);
    if(a==QHostAddress::LocalHostIPv6) return nameof(QHostAddress::LocalHostIPv6);
    if(a==QHostAddress::Any) return nameof(QHostAddress::Any);
    if(a==QHostAddress::AnyIPv6) return nameof(QHostAddress::AnyIPv6);
    if(a==QHostAddress::AnyIPv4) return nameof(QHostAddress::AnyIPv4);
    return a.toString();
}

void HTTPThreadedServer::start()
{
    if(!listen(host,port))
    {
        zInfo(QStringLiteral("%1 could not start").arg(this->_serverName));
    }
    else
    {
        zInfo(QStringLiteral("%3 is listening on port %1:%2").arg(host.toString()).arg(port).arg(_serverName));
    }
}

void HTTPThreadedServer::stop()
{
    this->close();
    zInfo(QStringLiteral("%1 is closed").arg(_serverName));
}

void HTTPThreadedServer::incomingConnection(qintptr socketDescriptor)
{
    zInfo("incoming:"+QString::number(socketDescriptor));
    // Amikor bejön egy connection, csinálunk egy klienst , ami amúgy nem kliens, inkább socket handler
    auto *client = new ThreadedSocketHandler(this);
    client->setSocket(socketDescriptor);
    client->setServer(this);
}

void HTTPThreadedServer::addAction(QString m, QString p, actionFn fn)
{
    if(m.isEmpty()) return;
    if(p.isEmpty()) return;
    if(fn == nullptr) return;
    if(!p.startsWith('/')) p='/'+p;

    if(!ActionHelper::contains(this->actions, m, p))
    {        
        this->actions.append(Action(m, p, fn));
        zInfo(QStringLiteral("%2 action added to server %1").arg(this->_serverName).arg(p));
    }
}

const Action* HTTPThreadedServer::action(Request r)
{
    return ActionHelper::find(actions, r);
}
