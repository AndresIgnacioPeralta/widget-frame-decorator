#ifndef WINDOWDECORATOR_H
#define WINDOWDECORATOR_H

#include <QWidget>

class ContainerFrame;
class QFrame;
class WindowDecorator : public QWidget {
    Q_OBJECT
public:
    WindowDecorator(QWidget* widgetInstance);

    QColor getOrinialWidgetColor() const;

    QColor getOrininalBackgroundColor() const;

public slots:
    void setWidgetColor(const QColor color);

    void setBackgroundColor(const QColor color);

    void setBoderColor(const QColor color);

    void showToolBar(const bool show);

    void setOpacity(const int opacity);

    void showShadow(const bool show);

    void setShadowWidth(const int width);

private:
    virtual bool eventFilter(QObject *object, QEvent *event);

    void paintBackground();

    void paintBorder();

    void paintShadow(QPainter& painter, const QRect area);

    void applyDecoration();

    void updateBorderZones();

    QWidget* widget;

    QPoint clickpostion;

    qreal opacityLevel;
    QColor backgroundColor;
    QColor widgetColor;
    QColor borderColor;
    int shadowWidth;

    QColor originalWidgetColor;
    QColor originqlBackgroundColor;

    bool drawShadow;
    bool drawWidgetBackground;

    QRect diagonalTL;
    QRect diagonalTR;
    QRect diagonalBL;
    QRect diagonalBR;
    QRect diagonalL;
    QRect diagonalR;
    QRect diagonalT;
    QRect diagonalB;

    QRect outerBorder;
    QRect innerBorder;
    QRect original;

    ContainerFrame* containerWidget;
};

#endif // WINDOWDECORATOR_H
