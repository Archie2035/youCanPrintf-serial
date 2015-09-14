#ifndef TYPEDF
#define TYPEDF
#include <QSerialPort>

typedef struct  {
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
}serialSettings;
#endif // TYPEDF

