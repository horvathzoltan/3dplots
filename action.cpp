#include "action.h"

const QString Action::contentType::HTML = QStringLiteral("text/html");
const QString Action::contentType::TEXT = QStringLiteral("text/plain");
const QString Action::contentType::JSON = QStringLiteral("application/json");

Action::Action()
{

}

Action::Action(QString m, QString p, actionFn fn)
{
    this->method = m;
    this->path = p;
    this->fn = fn;
}



