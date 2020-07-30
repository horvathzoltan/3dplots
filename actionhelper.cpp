#include "common/macrofactory/macro.h"
#include "actionhelper.h"

ActionHelper::ActionHelper()
{

}

const Action* ActionHelper::find(const QList<Action>& actions, QString m, QString p)
{
    //for (auto i = actions.begin(); i != actions.end(); ++i)
    zforeach(i, actions)
    {
        if(i->method == m && i->path == p)
        {
            return i.operator->();
        }
    }
    return nullptr;
}

const Action *ActionHelper::find(const QList<Action>& actions, const Request& r)
{
    return find(actions, r.method, r.url.path());
}

bool ActionHelper::contains(const QList<Action>& actions, QString m, QString p)
{
    return(find(actions, m, p)!=nullptr);
}
