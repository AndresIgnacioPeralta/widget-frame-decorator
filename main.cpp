#include "mainwindow.h"
#include "windowdecorator.h"
#include <QApplication>
#include "decorationconfigurationwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    MainWindow w;
    WindowDecorator decorator(&w);
    DecorationConfigurationWidget configurationWIdget(&decorator);
    WindowDecorator decorator2(&configurationWIdget);
    configurationWIdget.show();
    w.show();

    return a.exec();
}
