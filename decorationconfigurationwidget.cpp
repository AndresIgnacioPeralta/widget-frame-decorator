#include "decorationconfigurationwidget.h"
#include "ui_decorationconfigurationwidget.h"
#include "windowdecorator.h"
#include <QGraphicsDropShadowEffect>
#include <QColorDialog>
#include <QDebug>

DecorationConfigurationWidget::DecorationConfigurationWidget(WindowDecorator *widget, QWidget * const parent) :
    QWidget(parent),
    ui(new Ui::DecorationConfigurationWidget),
    decorationWidget(widget) {
    ui->setupUi(this);

    connect(ui->sliderBackgroundOpacity, &QSlider::valueChanged, this, &DecorationConfigurationWidget::onOpacitySliderChanged);
    ui->sliderBackgroundOpacity->setValue(100);

    connect(ui->checkShadowOptions, &QGroupBox::toggled, decorationWidget, &WindowDecorator::showShadow);
    connect(ui->sliderBackgroundOpacity, &QSlider::valueChanged, decorationWidget, &WindowDecorator::setOpacity);
    connect(ui->buttonColorBackground, &QPushButton::clicked, this, &DecorationConfigurationWidget::onSelecBackgroundColorClicked);
    connect(ui->buttonColorBorder, &QPushButton::clicked, this, &DecorationConfigurationWidget::onSelecBorderColorClicked);
    connect(ui->buttonColorWidget, &QPushButton::clicked, this, &DecorationConfigurationWidget::onSelecWidgetColorClicked);
    connect(ui->sliderShadowSpan, &QSlider::valueChanged, this, &DecorationConfigurationWidget::onShadowSpanSliderChanged);
    connect(ui->sliderShadowSpan, &QSlider::valueChanged, decorationWidget, &WindowDecorator::setShadowWidth);

    setButtonColor(decorationWidget->getOrininalBackgroundColor(), ui->buttonColorBackground);
    setButtonColor(Qt::white, ui->buttonColorBorder);
    setButtonColor(decorationWidget->getOrinialWidgetColor(), ui->buttonColorWidget);
}

DecorationConfigurationWidget::~DecorationConfigurationWidget() {
    delete ui;
}

void DecorationConfigurationWidget::setButtonColor(const QColor color, QPushButton *button) {
    QPalette buttonPalette = button->palette();
    buttonPalette.setColor(QPalette::Button, color);
    button->setAutoFillBackground(true);
    button->setPalette(buttonPalette);
    button->update();
}

void DecorationConfigurationWidget::onOpacitySliderChanged(const int value) {
    ui->labelOpacityLevel->setText(QString::number(10 * value) + "%");
}

void DecorationConfigurationWidget::onSelecBorderColorClicked() {
    QColorDialog* colorDialog = new QColorDialog(Qt::white, this);
    connect(colorDialog, &QColorDialog::colorSelected, this, &DecorationConfigurationWidget::onBorderColorSelected);
    colorDialog->exec();
}

void DecorationConfigurationWidget::onSelecBackgroundColorClicked() {
    QColorDialog* colorDialog = new QColorDialog(decorationWidget->getOrininalBackgroundColor(), this);
    connect(colorDialog, &QColorDialog::colorSelected, this, &DecorationConfigurationWidget::onBackgroundColorSelected);
    colorDialog->exec();
}

void DecorationConfigurationWidget::onSelecWidgetColorClicked() {
    QColorDialog* colorDialog = new QColorDialog(decorationWidget->getOrinialWidgetColor(), this);
    connect(colorDialog, &QColorDialog::colorSelected, this, &DecorationConfigurationWidget::onWidgetColorSelected);
    colorDialog->exec();
}

void DecorationConfigurationWidget::onBorderColorSelected(const QColor color) {
    setButtonColor(color, ui->buttonColorBorder);
    decorationWidget->setBoderColor(color);
}

void DecorationConfigurationWidget::onBackgroundColorSelected(const QColor color) {
    setButtonColor(color, ui->buttonColorBackground);
    decorationWidget->setBackgroundColor(color);
}

void DecorationConfigurationWidget::onWidgetColorSelected(const QColor color) {
    setButtonColor(color, ui->buttonColorWidget);
    decorationWidget->setWidgetColor(color);
}

void DecorationConfigurationWidget::onShadowSpanSliderChanged(const int value) {
    ui->labelSpanValue->setText(QString::number(value) + "px");
}
