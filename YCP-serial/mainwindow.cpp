#include "mainwindow.h"
#include "QMessageBox"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setupUi(this);
    serialSettingDialog = new SerialSetting();

    serialSettingDialog->show();
    serial = new QSerialPort(this);
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}
MainWindow::~MainWindow()
{

}
void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    textBrowser->insertPlainText(data.toHex());
    qDebug()<<data.toHex();
}
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}
void MainWindow::openSerialPort()
{
    serialSettings p = serialSettingDialog->getSerilaSettings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite))
    {
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
    }
}
void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
}
void MainWindow::on_pushButtonOpen_clicked()
{
    openSerialPort();
}

void MainWindow::on_pushButtonClose_clicked()
{
    closeSerialPort();
}
