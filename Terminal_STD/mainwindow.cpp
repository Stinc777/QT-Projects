#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   ui->lineWordsTX->setText("0");

   // Получение списка доступных COM-портов
   QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();

   // Заполнение QComboBox именами портов
   for (const QSerialPortInfo &portInfo : portList)
   {
      ui->comboBoxComList->addItem(portInfo.portName());
   }

}

MainWindow::~MainWindow()
{
   delete ui;

   // Close the serial port
   if (serial->isOpen())
   {
      serial->close();
      qDebug() << "Serial port closed.";
   }

   delete serial;
}

void MainWindow::on_btnSend_clicked()
{
   // // Отправка данных через COM-порт
   // QString dataToSend = ui->textEdit->toPlainText();

   // // Проверка, что строка состоит из 4 цифр
   // if (dataToSend.size() != 4 || !dataToSend.toInt())
   // {
   //    qDebug() << "Invalid input. Please enter a 4-digit number.";
   //    return;
   // }

   // // Разделение 4 цифр на два байта
   // QString firstByteStr = dataToSend.mid(0, 2);
   // QString secondByteStr = dataToSend.mid(2, 2);

   // // Преобразование строк в байты
   // char firstByte = static_cast<char>(firstByteStr.toInt(nullptr, 16));
   // char secondByte = static_cast<char>(secondByteStr.toInt(nullptr, 16));

   // // Отправка двух байтов через COM-порт
   // if (serial->isOpen())
   // {
   //    QByteArray firstbyteArray;
   //    firstbyteArray.append(firstByte);
   //    serial->write(firstbyteArray);
   //    QByteArray secondByteArray;
   //    secondByteArray.append(secondByte);
   //    serial->write(secondByteArray);
   // }
}

void MainWindow::serialRecieve() //получаем данные
{
   // Чтение двух байтов
   QByteArray highByte = serial->read(1);
   QByteArray lowByte = serial->read(1);

   // Преобразование байтов в числа
   int highValue = highByte.toInt(nullptr, 16);
   int lowValue = lowByte.toInt(nullptr, 16);

   // Объединение чисел в строку
   QString result = QString("%1 %2").arg(highValue, 2, 16, QChar('0')).arg(lowValue, 2, 16, QChar('0'));

   // Отображение результата в label
   //ui->label->setText(result);
}

void MainWindow::on_btnOnOff_clicked(bool checked)
{
   if (checked == true)
   {
      serial = new QSerialPort(this);  //новый экземпляр класса AbstractSerial
      serial->setPortName(ui->comboBoxComList->currentText());    //указали com порт и параметры порта(далее)
      serial->setBaudRate(QSerialPort::Baud115200);
      serial->setDataBits(QSerialPort::Data8);
      serial->setParity(QSerialPort::NoParity);
      serial->setStopBits(QSerialPort::OneStop);
      serial->setFlowControl(QSerialPort::NoFlowControl);
      // Открытие COM-порта
      if (serial->open(QIODevice::ReadWrite))
      {
         qDebug() << "Serial port opened successfully.";

         // Connect the readyRead signal to the slot for receiving data
         connect(serial, SIGNAL(readyRead()), this, SLOT(serialRecieve()));
      }
      else
      {
         qDebug() << "Failed to open serial port.";
      }
   }
   else
   {
      serial->close();
      qDebug() << "Serial port closed.";
   }
}

/*
 * Изменение кол-ва слов на записи.
 *
 * 1. Сделать List - который будет запоминать, что уже данные есть и добавлять их или удалять при необходимости.
 * Мб тогда сделать класс отдельный?
 *
 */
void MainWindow::on_lineWordsTX_textChanged(const QString &wordTX)
{
   uint words = wordTX.length();

   if (words >= 1)
   {
      // // Очищаем gridTXWords перед добавлением новых элементов
      // QLayoutItem* item;
      // while ((item = ui->gridTXWords->takeAt(0)) != nullptr) {
      //    delete item->widget(); // Удаляем дочерние элементы
      //    delete item;
      // }

      // // Создание нового QLabel
      // QLabel *label = new QLabel(wordTX);

      // // Создание нового QLineEdit
      // QLineEdit *lineEdit = new QLineEdit;
      // lineEdit->setMaxLength(4); // Устанавливаем максимальную длину в 4 символа
      // lineEdit->setPlaceholderText("Введите значение");

      // // Добавляем QLabel и QLineEdit в gridLayout_2
      // int row = gridLayout_2->rowCount();
      // gridLayout_2->addWidget(label, row, 0);
      // gridLayout_2->addWidget(lineEdit, row, 1);
   }
}


void MainWindow::on_gridTXWords_customContextMenuRequested(const QPoint &pos)
{

}

