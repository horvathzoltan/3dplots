#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Q3DScatter>
#include <QFileDialog>
#include <QScatterDataArray>
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
    //ui->widget1->add
    scatter->setFlags(scatter->flags() ^ Qt::FramelessWindowHint);
    //scatter->setParent(ui->frame->windowHandle());
    this->series = new QtDataVisualization::QScatter3DSeries();
    QtDataVisualization::QScatterDataArray data;
    data << QVector3D(0.5f, 0.5f, 0.5f) << QVector3D(-0.3f, -0.5f, -0.4f) << QVector3D(0.0f, -0.3f, 0.2f);
    series->dataProxy()->addItems(data);
    scatter->addSeries(series);
    scatter->show();
}

MainWindow::~MainWindow()
{
    delete scatter;
    delete series;
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
        if(str->startsWith())
    }

}
