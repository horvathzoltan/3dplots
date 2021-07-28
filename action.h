#ifndef ACTION_H
#define ACTION_H

#include "request.h"

// ez történik amikor egy kérés befut a szerverhez
// és a kérés methodhoz és url-hez van társítva egy függvény

struct ActionResult{
    QByteArray content;
    QString type;

    ActionResult(){}
    ActionResult(const QByteArray& b, const QString& t){
        this->content = b;
        this->type = t;
    }
};
//Q_DECLARE_METATYPE(zActionResult);

typedef ActionResult (*actionFn)(const QUrlQuery&, const QByteArray&);

class Action
{
public:
    struct contentType{
        static const QString HTML;
        static const QString TEXT;
        static const QString JSON;
    };

    Action();

    Action(QString, QString, actionFn);

    QString method;
    QString path;
    actionFn fn;
};



#endif // ACTION_H
