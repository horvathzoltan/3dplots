#include "scatterhelper.h"
#include <QScatter3DSeries>
#include "common/logger/log.h"

bool ScatterHelper::isInitialised = false;
QtDataVisualization::Q3DScatter * ScatterHelper::sc_ = nullptr;

bool ScatterHelper::init(QtDataVisualization::Q3DScatter *sc)
{
    if(!sc) return false;
    sc_ = sc;
    isInitialised = true;
    return true;
}

void ScatterHelper::AddPoint(const QString &a0, const QString &a1, const QString &a2, const QString &a3)
{
    if(!isInitialised) {
        zError("ScatterHelper is unInitialised");
        return;
    }
    auto r = a0.toFloat();
    auto g = a1.toFloat();
    auto b = a2.toFloat();
    QString a31 = a3;
    auto d = (a31.replace(',','.').toFloat())/30.0f;
    if(d>1.0f) d = 1.0f;
    auto s = new QtDataVisualization::QScatter3DSeries();
    s->setItemSize(d);
    auto c = QColor(r, g, b);
    s->setBaseColor(c);
    sc_->seriesList().append(s);
    //series.append(s);
    sc_->addSeries(s);
    s->dataProxy()->addItem(
        QtDataVisualization::QScatterDataItem(QVector3D(r, g, b))
                );
}

void ScatterHelper::Clear()
{
    auto max = sc_->seriesList().count();
    auto l = sc_->seriesList();
    for(int i=0;i<max;i++){sc_->removeSeries(l[i]);}
}
