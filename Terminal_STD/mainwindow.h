#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

   public:
   MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

   private slots:

      void serialRecieve();
      void on_btnOnOff_clicked(bool checked);
      void on_btnSend_clicked();

      void on_lineWordsTX_textChanged(const QString &wordTX);

      void on_gridTXWords_customContextMenuRequested(const QPoint &pos);

  private:
      Ui::MainWindow *ui;
      QSerialPort *serial;
};
#endif // MAINWINDOW_H
