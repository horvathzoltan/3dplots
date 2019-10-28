#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Q3DScatter>
#include <QFileDialog>
#include <QScatterDataArray>
#include <QScatterDataItem>
#include <QtDataVisualization>
#include <Q3DTheme>
#include "common/logger/log.h"
#include "common/helper/textfilehelper/textfilehelper.h"
#include "common/macrofactory/macro.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->scatter = new QtDataVisualization::Q3DScatter();
    auto container = QWidget::createWindowContainer(scatter);
    QHBoxLayout *hLayout = new QHBoxLayout(ui->widget1);
    hLayout->addWidget(container, 1);
    scatter->axisX()->setMin(0);
    scatter->axisX()->setMax(255);
    scatter->axisY()->setMin(0);
    scatter->axisY()->setMax(255);
    scatter->axisZ()->setMin(0);
    scatter->axisZ()->setMax(255);

    //ui->widget1->add
    scatter->setFlags(scatter->flags() ^ Qt::FramelessWindowHint);
    //scatter->setParent(ui->frame->windowHandle());
    //this->series = new QtDataVisualization::QScatter3DSeries();
    //QtDataVisualization::QScatterDataArray data;
    //data << QVector3D(0.5f, 0.5f, 0.5f) << QVector3D(-0.3f, -0.5f, -0.4f) << QVector3D(0.0f, -0.3f, 0.2f);
    //series->dataProxy()->addItems(data);
    //scatter->addSeries(series);
    scatter->show();
}

MainWindow::~MainWindow()
{
    delete scatter;
    qDeleteAll(series);
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    zTrace();

    //series->dataProxy()->addItem(QVector3D(0.2f*i, 0.2f*i, 0.2f)*i);
    //auto fn = com::helper::File
    auto fn = QFileDialog::getOpenFileName(this,tr("Open CSV"), "C:/ColorData", tr("CSV Files (*.csv)"));
    auto strs = com::helper::TextFileHelper::loadLines(fn);

    zforeach(str, strs){
        if(str->isEmpty()) continue;
        if(str->startsWith('#')) continue;
        auto a = str->split(';');
        if(a.length()<4) continue;
        auto r = a[0].toFloat();
        auto g = a[1].toFloat();
        auto b = a[2].toFloat();
        auto d = (a[3].replace(',','.').toFloat())/30.0f;
        if(d>1.0f) d = 1.0f;
        auto s = new QtDataVisualization::QScatter3DSeries();
        s->setItemSize(d);
        auto c = QColor(r, g, b);

//        QLinearGradient linearGrad(QPointF(100, 100), QPointF(200, 200));
//        linearGrad.setColorAt(0, c);
//        auto c2 = QColor(r*1.1f, g*1.1f, b*1.1f);
//        linearGrad.setColorAt(1, c2);
//        s->setBaseGradient(linearGrad);

        s->setBaseColor(c);
        //s->setColorStyle(QtDataVisualization::Q3DTheme::ColorStyle::ColorStyleObjectGradient);
        series.append(s);
        scatter->addSeries(s);


        s->dataProxy()->addItem(QtDataVisualization::QScatterDataItem(
            QVector3D(r, g, b)));

    }

}
