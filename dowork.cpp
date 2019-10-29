#include "dowork.h"
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
    zInfo(QStringLiteral("add: r=%1 g=%2 b=%3 d=%4").arg(r, g, b, d));

    ScatterHelper::AddPoint(r, g, b, d);

    return ActionResult(QStringLiteral("added").toUtf8(), Action::contentType::TEXT);
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


