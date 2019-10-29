#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Q3DScatter>
#include <QFileDialog>
#include <QScatterDataArray>
#include <QScatterDataItem>
#include <QtDataVisualization>
#include <Q3DTheme>
#include <QString>
#include "common/logger/log.h"
#include "common/helper/textfilehelper/textfilehelper.h"
#include "common/macrofactory/macro.h"
#include "scatterhelper.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->scatter = new QtDataVisualization::Q3DScatter();
    ScatterHelper::init(scatter);
    auto container = QWidget::createWindowContainer(scatter);
    QHBoxLayout *hLayout = new QHBoxLayout(ui->widget1);
    hLayout->addWidget(container, 1);
    scatter->axisX()->setMin(0);
    scatter->axisX()->setMax(255);
    scatter->axisY()->setMin(0);
    scatter->axisY()->setMax(255);
    scatter->axisZ()->setMin(0);
    scatter->axisZ()->setMax(255);
    scatter->axisX()->setTitle(QStringLiteral("R"));
    scatter->axisY()->setTitle(QStringLiteral("G"));
    scatter->axisZ()->setTitle(QStringLiteral("B"));

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
    //zTrace();
    auto fn = QFileDialog::getOpenFileName(this,tr("Open CSV"), "C:/ColorData", tr("CSV Files (*.csv)"));
    auto strs = com::helper::TextFileHelper::loadLines(fn);

    zforeach(str, strs){
        if(str->isEmpty()) continue;
        if(str->startsWith('#')) continue;
        auto a = str->split(';');
        if(a.length()<4) continue;
        ScatterHelper::AddPoint(a[0], a[1], a[2], a[3]);
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    ScatterHelper::Clear();
}
