#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   MainWindow terminal;
   terminal.show();
   return app.exec();
}
