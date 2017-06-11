#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);

  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpConnect()));

  connect(ui->pushButton_2Disconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpDisconnect()));


  connect(ui->pushButton_3Start,
          SIGNAL(clicked(bool)),
          this,
          SLOT(putData()));

  connect(ui->pushButton_4Stop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(Stop()));
}

void MainWindow::timerEvent(QTimerEvent *e){
    QDateTime datetime;
    QString str;
    if(socket->state()== QAbstractSocket::ConnectedState){
        if ((getmax()<=getmin())){
            qDebug()<< "Range invalido (max < min)";
        }
        else if ((getmax()>=getmin())){
        datetime = QDateTime::currentDateTime();
        str = "set "+
            datetime.toString(Qt::ISODate)+
            " "+
            QString::number(qrand()%(getmax()-getmin())+(getmin()))+"\r\n";

        qDebug() << str;
        qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
        ui->textBrowser->insertPlainText( "set "+
                                          datetime.toString(Qt::ISODate)+
                                          " "+
                                          QString::number(qrand()%(getmax()-getmin())+(getmin()))+"\r\n");
               if(socket->waitForBytesWritten(1000)){
          qDebug() << "wrote";
        }
    }
    }
}


int MainWindow::getimming(){
      return(ui->horizontalSlider_3timming->value());
    }

QString MainWindow::getip(){
      return(ui->lineEdit->text());
    }

int MainWindow::getmin(){
      return(ui->horizontalSliderMin->value());
    }
int MainWindow::getmax(){
      return(ui->horizontalSlider_2Max->value());
    }

void MainWindow::tcpConnect(){
  //socket->connectToHost("127.0.0.1",1234);
    socket->connectToHost(getip(),1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}

void MainWindow::tcpDisconnect(){
  //socket->connectToHost("127.0.0.1",1234);
    socket->disconnectFromHost();
  if(socket->waitForDisconnected(3000)){
    qDebug() << "Disconnected";
  }
}
void MainWindow::Stop()
{
    killTimer(TimerID);
}


void MainWindow::putData()
{
    killTimer(TimerID);
    TimerID = startTimer(getimming()*100);

}



MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}


