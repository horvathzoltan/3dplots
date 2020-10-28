#ifndef ACTIONHELPER_H
#define ACTIONHELPER_H

#include "action.h"

class ActionHelper
{
public:
    ActionHelper();

    static const Action* find(const QList<Action>& actions, QString r, QString p);
    static const Action* find(const QList<Action>& actions, const Request& r);
    static bool contains(const QList<Action>& actions, QString r, QString p);
};

#endif // ACTIONHELPER_H
