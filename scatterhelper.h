#ifndef SCATTERHELPER_H
#define SCATTERHELPER_H

#include <Q3DScatter>
#include <QString>

class ScatterHelper
{
private:
    static QtDataVisualization::Q3DScatter *sc_;
    static bool isInitialised;
//    static bool isClearing;
//    static bool isAddingPoint;
public:
    static bool init(QtDataVisualization::Q3DScatter *sc);
    static void AddPoint(const QString &, const QString &, const QString &, const QString &, const QString &);

    static QtDataVisualization::QScatter3DSeries* FindByName(const QString &n);
    static void Clear();

    static bool Delete(const QString &);
    static bool Move(const QString &,
                     const QString &, const QString &, const QString &,
                     const QString &);

    static bool initValidator();
    static float getD(const QString &a3);
};

#endif // SCATTERHELPER_H
