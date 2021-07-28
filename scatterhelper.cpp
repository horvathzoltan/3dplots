#include "scatterhelper.h"
#include <QScatter3DSeries>
#include "common/logger/log.h"

bool ScatterHelper::isInitialised = false;
QtDataVisualization::Q3DScatter * ScatterHelper::sc_ = nullptr;
//bool ScatterHelper::isClearing = false;
//bool ScatterHelper::isAddingPoint = false;

bool ScatterHelper::init(QtDataVisualization::Q3DScatter *sc)
{
    if(!sc) return false;
    sc_ = sc;
    isInitialised = true;
    return true;
}

float ScatterHelper::getD(const QString &a3){
    QString a31 = a3;
    //auto d = (a31.replace(',','.').toFloat())/30.0f;
    //if(d>1.0f) d = 1.0f;
    auto d = (a31.replace(',','.').toFloat());
    return d;
}
void ScatterHelper::AddPoint(const QString &a0, const QString &a1, const QString &a2, const QString &a3, const QString &name)
{
    if(!initValidator()) return;
//    if(isClearing) return;
//    if(isAddingPoint) return;
//    isAddingPoint = true;
    auto r = a0.toFloat();
    auto g = a1.toFloat();
    auto b = a2.toFloat();
    auto d = getD(a3);

    auto s = new QtDataVisualization::QScatter3DSeries();
    s->setName(name);
    s->setItemSize(d);
    auto c = QColor(r, g, b);
    s->setBaseColor(c);
    sc_->seriesList().append(s);
    //series.append(s);
    sc_->addSeries(s);
    s->dataProxy()->addItem(
        QtDataVisualization::QScatterDataItem(QVector3D(r, g, b))
                );    
    zInfo(QStringLiteral("point added: %1").arg(name));

//    isAddingPoint = false;
}

void ScatterHelper::Clear()
{
    if(!initValidator()) return;
//    if(isClearing) return;
//    if(isAddingPoint) return;
//    isClearing = true;

    //zforeach(l, sc_->seriesList()) sc_->removeSeries(*l);

    auto max = sc_->seriesList().count();
    auto l = sc_->seriesList();
    for(int i=0;i<max;i++){sc_->removeSeries(l[i]);}
//    while(!sc_->seriesList().isEmpty()){
//        auto l = sc_->seriesList().last();
//        sc_->removeSeries(l);
//    }
//    isClearing = false;
}

QtDataVisualization::QScatter3DSeries* ScatterHelper::FindByName(const QString &n){
    auto max = sc_->seriesList().count();
    auto l = sc_->seriesList();
    for(int i=0;i<max;i++){if(l[i]->name()==n) return l[i];}
    return nullptr;
}

bool ScatterHelper::Delete(const QString &n)
{
    if(!initValidator()) return false;

    auto c = FindByName(n);
    if(c) {
        sc_->removeSeries(c);
        return true;
    }
    return false;
}

bool ScatterHelper::Move(const QString &n,
                         const QString &a0, const QString &a1, const QString &a2,
                          const QString &a3)
{
    if(!initValidator()) return false;

    auto r = a0.toFloat();
    auto g = a1.toFloat();
    auto b = a2.toFloat();
    auto d = getD(a3);

    auto s = FindByName(n);
    if(s) {
        s->setBaseColor(QColor(r, g, b));
        s->setItemSize(d);
        s->dataProxy()->setItem(0, QtDataVisualization::QScatterDataItem(QVector3D(r, g, b)));
        return true;
    }
    return false;
}


bool ScatterHelper::initValidator()
{
    if(isInitialised) return true;
    zError("ScatterHelper is unInitialised");
    return false;
}
