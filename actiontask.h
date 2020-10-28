#ifndef ACTIONTASK_H
#define ACTIONTASK_H


#include <QObject>
#include <QRunnable>
#include "action.h"

// A signal/slot használata miatt kell származtatni a QObjectből
// a task miatt pedig a QRunnable-ből is

class ActionTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ActionTask();
    void setActionFn(const actionFn& a, const QUrlQuery& param, const QByteArray& c);
signals:
    // a fő szálat értesíti és adja át az eredményt
    void Result(ActionResult e);

protected:
    void run();
    actionFn aFn;
    QUrlQuery aParam;
    QByteArray content;
};


#endif // ACTIONTASK_H
