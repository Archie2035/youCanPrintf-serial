#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "src/serialsetting.h"
#include "ui_mainwindow.h"
class MainWindow : public QMainWindow,Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    SerialSetting *serialSettingDialog;
    QSerialPort *serial;
    void openSerialPort();
    void closeSerialPort();
private slots:
    void  readData();
    void handleError(QSerialPort::SerialPortError error);
    void on_pushButtonOpen_clicked();
    void on_pushButtonClose_clicked();
};

#endif // MAINWINDOW_H
