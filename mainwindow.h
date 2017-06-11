#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <iostream>
#include <string>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void timerEvent(QTimerEvent *e);
  int TimerID;
  
public slots:
  void Stop();
  void tcpConnect();
  void tcpDisconnect();
  void putData();
  QString getip();
  int getimming();
  int getmin();
  int getmax();
private slots:

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
