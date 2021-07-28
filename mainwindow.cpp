#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Q3DScatter>
#include <QFileDialog>
//#include <QScatterDataArray>
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

    connect(this, SIGNAL(clearPoints()),this, SLOT(onClearPoints()));
    connect(this, SIGNAL(countChanged()),this, SLOT(onCountChanged()));

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
    int i =0;
    zforeach(str, strs){
        if(str->isEmpty()) continue;
        bool isHex =  false;

        static QRegularExpression hexMatcher("[#$]?([0-9a-fA-F]{6})", QRegularExpression::CaseInsensitiveOption);
        auto m = hexMatcher.match(*str);

        if(m.hasMatch())
        {
            *str= m.captured(1);
            isHex = true;
        }
/*
    RYB_RED,RYB_GREEN,RYB_BLUE,
    RYB_YELLOW,RYB_ORANGE,RYB_PURPLE
        */
        if(isHex)
        {
            if (str->length() >= 6)
            {
                bool ok;
                //auto rr = str->mid(0, 2).toInt(&ok, 16);
                auto r = str->mid(0, 2).toInt(&ok, 16);//*16;
                auto g = str->mid(2, 2).toInt(&ok, 16);//*16;
                auto b = str->mid(4, 2).toInt(&ok, 16);//*16;
                ScatterHelper::AddPoint(
                    QString::number(r),
                    QString::number(g),
                    QString::number(b), "3", "u");
            }
        }
        else
        {
            //if(str->startsWith('#')) continue;
            auto a = str->split(';');
            if(a.length()<4) continue;
            auto n = QString::number(i++);
            // r, g, b, d
            ScatterHelper::AddPoint(a[0], a[1], a[2], a[3], n);
        }
        //ScatterHelper::AddPoint(a[0], a[1], a[2], a[3], n);
    }

}

void MainWindow::onClearPoints()
{
    ScatterHelper::Clear();    
}



void MainWindow::on_pushButton_2_clicked()
{
    emit clearPoints();
    emit countChanged();
}


void MainWindow::onDeletePoint(const QString &n)
{
    ScatterHelper::Delete(n);
}

void MainWindow::onMovePoint(const QString &n,
                             const QString &r,const QString &g,const QString &b,
                             const QString &d)
{
    zTrace();
    ScatterHelper::Move(n, r, g, b, d);
}

void MainWindow::onCountChanged(){
    auto n = scatter->seriesList().count();
    ui->lcdNumber->display(n);
}
