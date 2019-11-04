#include "dowork.h"
#include "httpthreadedserver.h"
#include "common/logger/log.h"
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <scatterhelper.h>

doWork::doWork()
{

}

ActionResult doWork::add(const QUrlQuery& param, const QByteArray& content)
{
    auto r = param.queryItemValue(QStringLiteral("r"));
    auto g = param.queryItemValue(QStringLiteral("g"));
    auto b = param.queryItemValue(QStringLiteral("b"));
    auto d = param.queryItemValue(QStringLiteral("d"));
    auto n = param.queryItemValue(QStringLiteral("n"));
    zInfo(QStringLiteral("add: r=%1 g=%2 b=%3 d=%4 n=%5").arg(r, g, b, d, n));

    ScatterHelper::AddPoint(r, g, b, d, n);

    return ActionResult(QStringLiteral("added").toUtf8(), Action::contentType::TEXT);
}

extern HTTPThreadedServer server;

MainWindow* doWork::mw_ = nullptr;

bool doWork::isInit_ = false;

bool doWork::init(MainWindow* mw){
    if(mw==nullptr) return false;
    mw_=mw;
    isInit_ = true;
    return true;
}

ActionResult doWork::clear(const QUrlQuery& param, const QByteArray& content)
{    
    if(!isInit_) return ActionResult(QStringLiteral("not cleared").toUtf8(), Action::contentType::JSON);
    emit mw_->clearPoints();
    return ActionResult(QStringLiteral("cleared").toUtf8(), Action::contentType::JSON);
}

ActionResult doWork::del(const QUrlQuery& param, const QByteArray& content)
{
    if(!isInit_) return ActionResult(QStringLiteral("not deleted").toUtf8(), Action::contentType::JSON);
    auto n = param.queryItemValue(QStringLiteral("n"));
    QMetaObject::invokeMethod(mw_, "onDeletePoint", Qt::QueuedConnection, Q_ARG(const QString&, n));
    return ActionResult(QStringLiteral("cleared").toUtf8(), Action::contentType::JSON);
}

ActionResult doWork::mov(const QUrlQuery& param, const QByteArray& content)
{
    zTrace();
    if(!isInit_) return ActionResult(QStringLiteral("not moved").toUtf8(), Action::contentType::JSON);
    auto n = param.queryItemValue(QStringLiteral("n"));
    auto r = param.queryItemValue(QStringLiteral("r"));
    auto g = param.queryItemValue(QStringLiteral("g"));
    auto b = param.queryItemValue(QStringLiteral("b"));
    auto d = param.queryItemValue(QStringLiteral("d"));
    QMetaObject::invokeMethod(mw_, "onMovePoint", Qt::QueuedConnection, Q_ARG(const QString&, n),
                              Q_ARG(const QString&, r), Q_ARG(const QString&, g), Q_ARG(const QString&, b),
                              Q_ARG(const QString&, d));
    return ActionResult(QStringLiteral("moved").toUtf8(), Action::contentType::JSON);
}
/*
ActionResult doWork::add(const QUrlQuery& param, const QByteArray& content)
{
    QJsonObject j
        {
            {"kulcs1", QStringLiteral("érték1")},
            {"kulcs2", QStringLiteral("érték2")},
            {"kulcs3", 55}
        };
    return ActionResult(QJsonDocument(j).toJson(QJsonDocument::Indented), Action::contentType::JSON);
}
*/
//active
ActionResult doWork::testconnection(const QUrlQuery& param, const QByteArray& content)
{
    return ActionResult(QStringLiteral("true").toUtf8(), Action::contentType::JSON);
}


