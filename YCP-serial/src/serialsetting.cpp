#include "serialsetting.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QIntValidator>
#include <QLineEdit>

#define  BLANKSTRING "N/A"
SerialSetting::SerialSetting(QWidget *parent):
    QDialog(parent)
{
    this->setupUi(this);

    intValidator = new QIntValidator(0, 4000000, this);
    connect(pushButtonSubmit, SIGNAL(clicked()),this, SLOT(submit()));
    connect(comboBoxSerialCom, SIGNAL(currentIndexChanged(int)),this, SLOT(showPortInfo(int)));
    connect(comboBoxBaudRate, SIGNAL(currentIndexChanged(int)),this, SLOT(checkCustomBaudRatePolicy(int)));
    connect(comboBoxSerialCom, SIGNAL(currentIndexChanged(int)),this, SLOT(checkCustomDevicePathPolicy(int)));
    fillPortsParameters();
    fillPortsInfo();
}

SerialSetting::~SerialSetting()
{

}
void SerialSetting::submit()
{
    updateSettings();
}
void SerialSetting::fillPortsParameters()
{
    comboBoxBaudRate->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    comboBoxBaudRate->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    comboBoxBaudRate->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    comboBoxBaudRate->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    comboBoxBaudRate->addItem(tr("Custom"));

    comboBoxDataBits->addItem(QStringLiteral("5"), QSerialPort::Data5);
    comboBoxDataBits->addItem(QStringLiteral("6"), QSerialPort::Data6);
    comboBoxDataBits->addItem(QStringLiteral("7"), QSerialPort::Data7);
    comboBoxDataBits->addItem(QStringLiteral("8"), QSerialPort::Data8);
    comboBoxDataBits->setCurrentIndex(3);

    comboBoxParity->addItem(tr("None"), QSerialPort::NoParity);
    comboBoxParity->addItem(tr("Even"), QSerialPort::EvenParity);
    comboBoxParity->addItem(tr("Odd"), QSerialPort::OddParity);
    comboBoxParity->addItem(tr("Mark"), QSerialPort::MarkParity);
    comboBoxParity->addItem(tr("Space"), QSerialPort::SpaceParity);

    comboBoxStopBits->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    comboBoxStopBits->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    comboBoxStopBits->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    comboBoxFlowControl->addItem(tr("None"), QSerialPort::NoFlowControl);
    comboBoxFlowControl->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    comboBoxFlowControl->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void SerialSetting::fillPortsInfo()
{
    comboBoxSerialCom->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : BLANKSTRING)
             << (!manufacturer.isEmpty() ? manufacturer : BLANKSTRING)
             << (!serialNumber.isEmpty() ? serialNumber : BLANKSTRING)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : BLANKSTRING)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : BLANKSTRING);

        comboBoxSerialCom->addItem(list.first(), list);
    }

    comboBoxSerialCom->addItem(tr("Custom"));
}
void SerialSetting::showPortInfo(int idx)
{
    QStringList list = comboBoxSerialCom->itemData(idx).toStringList();

    labelDescription->setText(tr("Description: %1").arg(list.count() > 1 ? list.at(1) : tr(BLANKSTRING)));
    labelManufacturer->setText(tr("Manufacturer: %1").arg(list.count() > 2 ? list.at(2) : tr(BLANKSTRING)));
    labelSerialnum->setText(tr("Serial number: %1").arg(list.count() > 3 ? list.at(3) : tr(BLANKSTRING)));
    labelLocation->setText(tr("Location: %1").arg(list.count() > 4 ? list.at(4) : tr(BLANKSTRING)));
    labelVid->setText(tr("Vendor Identifier: %1").arg(list.count() > 5 ? list.at(5) : tr(BLANKSTRING)));
    labelPid->setText(tr("Product Identifier: %1").arg(list.count() > 6 ? list.at(6) : tr(BLANKSTRING)));
}
void SerialSetting::checkCustomBaudRatePolicy(int idx)
{
    bool isCustomBaudRate = !comboBoxBaudRate->itemData(idx).isValid();
    comboBoxBaudRate->setEditable(isCustomBaudRate);
    if (isCustomBaudRate) {
        comboBoxBaudRate->clearEditText();
        QLineEdit *edit = comboBoxBaudRate->lineEdit();
        edit->setValidator(intValidator);
    }
}

void SerialSetting::checkCustomDevicePathPolicy(int idx)
{
    bool isCustomPath = !comboBoxSerialCom->itemData(idx).isValid();
    comboBoxSerialCom->setEditable(isCustomPath);
    if (isCustomPath)
        comboBoxSerialCom->clearEditText();
}
void SerialSetting::updateSettings()
{
    currentSettings.name = comboBoxSerialCom->currentText();
    currentSettings.baudRate = comboBoxBaudRate->currentText().toInt();

    currentSettings.dataBits = static_cast<QSerialPort::DataBits>(comboBoxDataBits->itemData(comboBoxDataBits->currentIndex()).toInt());
    currentSettings.parity = static_cast<QSerialPort::Parity>(comboBoxParity->itemData(comboBoxParity->currentIndex()).toInt());
    currentSettings.stopBits = static_cast<QSerialPort::StopBits>(comboBoxStopBits->itemData(comboBoxStopBits->currentIndex()).toInt());
    currentSettings.flowControl = static_cast<QSerialPort::FlowControl>(comboBoxFlowControl->itemData(comboBoxFlowControl->currentIndex()).toInt());
}

serialSettings SerialSetting::getSerilaSettings()
{
    return currentSettings;
}