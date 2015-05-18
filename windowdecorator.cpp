#include "windowdecorator.h"
#include "containerframe.h"
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QPainter>
#include <QFrame>
#include <QLayout>
#include <QtWin>

WindowDecorator::WindowDecorator(QWidget *widgetInstance):
    widget(widgetInstance),
    containerWidget(new ContainerFrame(widgetInstance)),
    opacityLevel(1),
    backgroundColor(QtWin::realColorizationColor()),
    widgetColor(widget->palette().color(QPalette::Background)),
    borderColor(QtWin::realColorizationColor()),
    drawShadow(true),
    originalWidgetColor(widgetColor),
    originqlBackgroundColor(backgroundColor)
{
    applyDecoration();
    containerWidget->show();
}

QColor WindowDecorator::getOrinialWidgetColor() const {
    return originalWidgetColor;
}

QColor WindowDecorator::getOrininalBackgroundColor() const {
    return originqlBackgroundColor;
}

void WindowDecorator::setWidgetColor(const QColor color) {
    widgetColor = color;
    update();
}

void WindowDecorator::setBackgroundColor(const QColor color) {
    backgroundColor = color;
    update();
}

void WindowDecorator::setBoderColor(const QColor color) {
    borderColor = color;
    update();
}

void WindowDecorator::showToolBar(const bool show) {

}

void WindowDecorator::setOpacity(const int opacity) {
    opacityLevel = qreal(opacity / 10.0);
    containerWidget->setAttribute(Qt::WA_NoSystemBackground,   opacityLevel < 1.0);
    containerWidget->setAttribute(Qt::WA_TranslucentBackground,opacityLevel < 1.0);
    update();
}

void WindowDecorator::showShadow(const bool show) {
    drawShadow = show;
    update();
}

bool WindowDecorator::eventFilter(QObject * object, QEvent * event) {
    if(object == containerWidget) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent *>(event);
        if(event->type() == QEvent::MouseButtonPress && mouseEvent->buttons() & Qt::LeftButton) {
            clickpostion = mouseEvent->pos();
        } else if (event->type() == QEvent::MouseMove && mouseEvent->buttons() & Qt::LeftButton) {
            containerWidget->move(containerWidget->mapToParent(mouseEvent->pos() - clickpostion));
        } else if (event->type() == QEvent::Paint) {
            paintBorder();
        } /*else if (event->type() == QEvent::HoverEnter) {
            if (outerBorder.contains(mouseEvent->pos()) && !innerBorder.contains(mouseEvent->pos())) {
                QCursor resizeCursor;
                if(diagonalTL.contains(mouseEvent->pos()))      {qDebug() << "TL"; resizeCursor = Qt::SizeFDiagCursor;}
                else if(diagonalTR.contains(mouseEvent->pos())) {qDebug() << "TR"; resizeCursor = Qt::SizeBDiagCursor;}
                else if(diagonalBL.contains(mouseEvent->pos())) {qDebug() << "BL"; resizeCursor = Qt::SizeBDiagCursor;}
                else if(diagonalBR.contains(mouseEvent->pos())) {qDebug() << "BR"; resizeCursor = Qt::SizeFDiagCursor;}
                else if(diagonalL.contains(mouseEvent->pos()))  {qDebug() << "L";  resizeCursor = Qt::SizeHorCursor;}
                else if(diagonalR.contains(mouseEvent->pos()))  {qDebug() << "R";  resizeCursor = Qt::SizeHorCursor;}
                else if(diagonalT.contains(mouseEvent->pos()))  {qDebug() << "T";  resizeCursor = Qt::SizeVerCursor;}
                else if(diagonalB.contains(mouseEvent->pos()))  {qDebug() << "B";  resizeCursor = Qt::SizeVerCursor;}
                else { resizeCursor = Qt::ArrowCursor; }
                containerWidget->setCursor(resizeCursor);
            } else if (innerBorder.contains(mouseEvent->pos())){
                containerWidget->setCursor(Qt::ArrowCursor);
            }
        }*/

    } else if (object == widget) {
        if (event->type() == QEvent::Paint) {
            paintBackground();
        }
    }
    return QWidget::eventFilter(object, event);
}

void WindowDecorator::paintBackground() {
    QPainter painter(widget);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.setPen(QPen(widgetColor));
    painter.setBrush(widgetColor);
    painter.drawRect(widget->rect());
    painter.end();
}

void WindowDecorator::paintBorder() {
    QPainter painter(containerWidget);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    if(drawShadow) {
        paintShadow(painter);
    }
    painter.setOpacity(opacityLevel);
    painter.setPen(QPen(backgroundColor));
    painter.setBrush(backgroundColor);
    QRect widgetRect = containerWidget->rect();
    widgetRect.adjust(3, 3, -3, -3);
    painter.drawRect(widgetRect);
    painter.end();
}

void WindowDecorator::paintShadow(QPainter &painter) {
    int shadowThickness = 3;
    QLinearGradient gradient;
    gradient.setStart(0,0);
    gradient.setFinalStop(containerWidget->width() ,0);
    QColor grey1(0, 0, 0, 100);
    QColor grey2(0, 0, 0, 50);
    gradient.setColorAt((qreal)0, grey1);
    gradient.setColorAt((qreal)1, grey2);
    QBrush brush(gradient);
    painter.setBrush( brush);
    painter.setPen(Qt::NoPen);
    QPointF topLeft(shadowThickness + 0, shadowThickness + 0);
    QPointF bottomRight(containerWidget->width(), containerWidget->height());
    QRectF rect(topLeft, bottomRight);
    painter.drawRoundRect(rect, 2, 2);
}

void WindowDecorator::applyDecoration() {
    widget->setWindowFlags(Qt::FramelessWindowHint);
    widget->setAttribute(Qt::WA_Hover);
    widget->installEventFilter(this);
    widget->setAttribute(Qt::WA_NoSystemBackground, false);
    widget->setAttribute(Qt::WA_TranslucentBackground, false);

    containerWidget->setWindowFlags(Qt::FramelessWindowHint);
    containerWidget->setAttribute(Qt::WA_Hover);
    containerWidget->installEventFilter(this);
    containerWidget->setAttribute(Qt::WA_NoSystemBackground, true);
    containerWidget->setAttribute(Qt::WA_TranslucentBackground, true);
    updateBorderZones();
}

void WindowDecorator::updateBorderZones() {
    outerBorder = widget->rect();
    innerBorder = outerBorder;
    original = outerBorder;
    static const int margin = 5;
    innerBorder.adjust(margin, margin, -margin, -margin);

    diagonalTL = QRect(outerBorder.topLeft(), innerBorder.topLeft());
    diagonalTR = QRect(innerBorder.right(), outerBorder.top(), outerBorder.right(), innerBorder.top());
    diagonalBL = QRect(outerBorder.left(), innerBorder.bottom(), innerBorder.left(), outerBorder.bottom());
    diagonalBR = QRect(innerBorder.bottomRight(),outerBorder.bottomRight());
    diagonalL  = QRect(diagonalTL.topLeft(), diagonalBL.bottomRight());
    diagonalR  = QRect(diagonalTR.topLeft(), diagonalBR.bottomRight());
    diagonalT  = QRect(diagonalTL.topLeft(), diagonalTR.bottomRight());
    diagonalB  = QRect(diagonalBL.topLeft(), diagonalBR.bottomRight());
}
