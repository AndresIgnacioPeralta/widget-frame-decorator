#include "containerframe.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QLabel>
#include <QMenu>
#include <QDebug>

static const unsigned int TOP_BAR_HEIGHT(30);

ContainerFrame::ContainerFrame(QWidget* contained, QWidget* const parent) :
    QFrame(parent),
    containedWidget(contained),
    borderWidth(10),
    hasTopBar(true)
{
    setupUi(this);
    contained->setParent(this);
    mainLayout->addWidget(containedWidget);
    updateBorderWidth();
    showControlBar(true);
    labelTitle->setText(contained->windowTitle());
}

void ContainerFrame::setBorderWidth(const unsigned int width) {
    borderWidth = width;
}

void ContainerFrame::showControlBar(const bool show) {
    hasTopBar = show;
    connect(buttonLogo,     &QPushButton::clicked, this, &ContainerFrame::onButtonLogoClicked);
    connect(buttonMinimize, &QPushButton::clicked, this, &ContainerFrame::onButtonMinimizeClicked);
    connect(buttonMaximize, &QPushButton::clicked, this, &ContainerFrame::onButtonMaximizeClicked);
    connect(buttonHelp,     &QPushButton::clicked, this, &ContainerFrame::onButtonHelpClicked);
    connect(buttonClose,    &QPushButton::clicked, this, &ContainerFrame::onButtonCloseClicked);
}

void ContainerFrame::onButtonLogoClicked() {

}

void ContainerFrame::onButtonMinimizeClicked() {
    showMinimized();
}

void ContainerFrame::onButtonMaximizeClicked() {
    if(isMaximized()) {
        showNormal();
        containedWidget->showNormal();
    } else {
        showMaximized();
        containedWidget->showMaximized();
    }
}

void ContainerFrame::onButtonHelpClicked() {

}

void ContainerFrame::onButtonOnTopClicked(const bool checked) {
    if(checked) {
        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    } else {
        setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
    }
    show();
}

void ContainerFrame::onButtonCloseClicked() {
    close();
}

void ContainerFrame::updateBorderWidth() {
    setFixedSize(containedWidget->width() + 2 * borderWidth + 10 + 10 ,
                 containedWidget->height() + TOP_BAR_HEIGHT + borderWidth);
    mainLayout->setContentsMargins(borderWidth, 0, borderWidth, borderWidth);
}

void ContainerFrame::setTopBarIcons() {
}
