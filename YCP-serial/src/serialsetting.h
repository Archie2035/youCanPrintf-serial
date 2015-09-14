#ifndef SERIALSETTING_H
#define SERIALSETTING_H
#include <QDialog>
#include <QSerialPort>
#include "ui_serialsetting.h"
#include "src/typedf.h"
class SerialSetting : public QDialog,Ui::DialogSerilaSetting
{
    Q_OBJECT
public:
    SerialSetting(QWidget *parent = 0);
    ~SerialSetting();


    void fillPortsParameters();
    void fillPortsInfo();
    serialSettings getSerilaSettings();
private:
    QIntValidator *intValidator;
    serialSettings currentSettings;
private slots:
    void submit();
    void showPortInfo(int idx);
    void checkCustomDevicePathPolicy(int idx);
    void checkCustomBaudRatePolicy(int idx);
    void updateSettings();
};

#endif // SERIALSETTING_H
