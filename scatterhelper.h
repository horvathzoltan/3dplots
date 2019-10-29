#ifndef SCATTERHELPER_H
#define SCATTERHELPER_H

#include <Q3DScatter>
#include <QString>

class ScatterHelper
{
private:
    static QtDataVisualization::Q3DScatter *sc_;
    static bool isInitialised;
public:
    static bool init(QtDataVisualization::Q3DScatter *sc);
    static void AddPoint(const QString &, const QString &, const QString &, const QString &);
    static void Clear();
};

#endif // SCATTERHELPER_H
