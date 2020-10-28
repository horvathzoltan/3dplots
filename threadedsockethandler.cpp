#include "threadedsockethandler.h"
#include "common/logger/log.h"
//#include "zrequest.h"
//#include "zactionhelper.h"
//#include "zresponse.h"
//#include <QUrlQuery>
#include <QThreadPool>
#include "actiontask.h"


const QString ThreadedSocketHandler::LOGPATTERN = QStringLiteral("conn %1: %2");

ThreadedSocketHandler::ThreadedSocketHandler(QObject *parent) : QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(5);
}

// amikor a szerver elkap egy bejövő connectiont, csinál egy socketet
// a szervertől kapott descriptoral
void ThreadedSocketHandler::setSocket(qintptr descriptor)
{
    // make a new socket
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(descriptor);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    trace("socket created:"+QString::number(descriptor));
}


void ThreadedSocketHandler::setServer(HTTPThreadedServer *s)
{
    this->server = s;
}

// asynchronous - runs separately from the thread we created
void ThreadedSocketHandler::connected()
{
    //trace(QStringLiteral("connected"));
}

// asynchronous
void ThreadedSocketHandler::disconnected()
{
    //trace(QStringLiteral("disconnected"));
}

// ez itt mind a fő szálon történik
// de mi a taskot a poolból vesszük és haszáljuk fel

void ThreadedSocketHandler::readyRead()
{
    QByteArray ba;
    auto descriptor = socket->socketDescriptor();

    ba = socket->readAll();

    Request r(ba);

    trace(r.toString());

    //const zAction* action = nullptr;

    if(r.status==1)
    {
        if(r.isCompleted())
        {
            auto action = server->action(r);
            if(action !=nullptr)
            {
                startTask(r, *action);
            }
            else
            {
                notFound();
            }
        }
        else
        {
            server->pending_requests[descriptor]=r;
        }
    }
    else
    {
        if(server->pending_requests.contains(descriptor))
        {
            auto r2 = server->pending_requests[descriptor];
            r2.content+=ba;

            if(r2.isCompleted())
            {
                server->pending_requests.remove(descriptor);
                auto action = server->action(r2);
                if(action != nullptr)
                {
                    startTask(r2, *action);
                }
                else
                {
                    notFound();
                }
            }
        }
        else
        {
            Response rs;
            rs.setStatus(Response::statusCode::OK);
            rs.addHeaderField(Response::headerField::Server, server->serverName());
            rs.addBody("");

            socket->write(rs.toByteArray());
            socket->close();
            socket->disconnectFromHost();

        }
    }

}

// miután a task elkészült
// az eredményt válasszá alakítjuk
void ThreadedSocketHandler::TaskResult(ActionResult e)
{
    Response rs;

    rs.setStatus(Response::statusCode::OK);
    rs.addBody(e);
    rs.addHeaderField(Response::headerField::Server, server->serverName());

    sendResponse(rs);
}


// az api válaszát közöljük a klienssel
void ThreadedSocketHandler::sendResponse(Response rs){

    trace(rs.getStatus());
    socket->write(rs.toByteArray());
    socket->disconnectFromHost();
}

void ThreadedSocketHandler::trace(QString p1)
{
    zInfo(LOGPATTERN.arg(socket->socketDescriptor()).arg(p1));
}

void ThreadedSocketHandler::startTask(const Request& r, const Action action){
    zInfo(QStringLiteral("TASK(%1)").arg(r.instance));
    ActionTask *mytask = new ActionTask();
    //QString q_str = r.url.query();

    mytask->setActionFn(action.fn, r.urlparams, r.content);
    mytask->setAutoDelete(true);

    // sorba állítjuk
    connect(mytask, SIGNAL(Result(ActionResult)), this, SLOT(TaskResult(ActionResult)), Qt::QueuedConnection);

    QThreadPool::globalInstance()->start(mytask);
}

void ThreadedSocketHandler::notFound()
{
    Response rs;

    rs.setStatus(Response::statusCode::NotFound);
    rs.addHeaderField(Response::headerField::Server, server->serverName());
    sendResponse(rs);
}
