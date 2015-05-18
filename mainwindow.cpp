#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    /*QGraphicsDropShadowEffect *bodyShadow = new QGraphicsDropShadowEffect;
    bodyShadow->setBlurRadius(9.0);
    bodyShadow->setColor(QColor(0, 0, 0, 160));
    bodyShadow->setOffset(4.0);
    setGraphicsEffect(bodyShadow);*/
    QPushButton* button = new QPushButton("coso", this);
    setWindowTitle("My main widget");

    setMinimumSize(500,500);
}

MainWindow::~MainWindow()
{
}
