#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Q3DScatter>
#include <QScatterDataArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QtDataVisualization::Q3DScatter *scatter;
    QList<QtDataVisualization::QScatter3DSeries*> series;
    //QtDataVisualization::QScatterDataArray *data;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void onClearPoints();
    void onDeletePoint(const QString &n);
    void onMovePoint(const QString &,
                     const QString &, const QString &, const QString &,
                     const QString &);
    void onCountChanged();

signals:
    void clearPoints();
    void countChanged();
    //void deletePoint(const QString&);


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
