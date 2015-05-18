#ifndef DECORATIONCONFIGURATIONWIDGET_H
#define DECORATIONCONFIGURATIONWIDGET_H

#include <QWidget>

namespace Ui {
class DecorationConfigurationWidget;
}
class QPushButton;
class WindowDecorator;
class DecorationConfigurationWidget : public QWidget {
    Q_OBJECT

public:
    explicit DecorationConfigurationWidget(WindowDecorator *widget, QWidget* const parent = nullptr);
    ~DecorationConfigurationWidget();

private:
    void setButtonColor(const QColor color, QPushButton* button);

    Ui::DecorationConfigurationWidget *ui;
    WindowDecorator *decorationWidget;
    QColor widgetOriginalColor;
    QColor backgroundOriginalColor;

private slots:
    void onOpacitySliderChanged(const int value);

    void onSelecBorderColorClicked();
    void onSelecBackgroundColorClicked();
    void onSelecWidgetColorClicked();

    void onBorderColorSelected(const QColor color);
    void onBackgroundColorSelected(const QColor color);
    void onWidgetColorSelected(const QColor color);
    void onShadowSpanSliderChanged(const int value);
};

#endif // DECORATIONCONFIGURATIONWIDGET_H
