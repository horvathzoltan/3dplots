#include "actiontask.h"
#include "common/logger/log.h"


ActionTask::ActionTask()
{
    // zlog.trace(QStringLiteral("MyTask()"));
}

void ActionTask::setActionFn(const actionFn& a, const QUrlQuery& p, const QByteArray& c)
{
    this->aFn = a;
    this->aParam = p;
    this->content = c;
}

// When the thread pool kicks up
// it's going to hit this run, and it's going to do this time consuming task.
// After it's done, we're going to send the results back to our main thread.
// This runs in the separate thread, and we do not have any control over this thread,
// but Qt does.
// This may just stay in the queue for several ms depending on how busy the server is.

void ActionTask::run()
{
    // time consumer

    zInfo(QStringLiteral("Task started"));


    //    int iNumber = 0;
    //    for(int i = 0; i < 100; i++)
    //    {
    //        iNumber += 1;
    //    }

    ActionResult eredmeny = this->aFn(aParam, content);

    zInfo(QStringLiteral("Task done"));
    emit Result(eredmeny);
}
