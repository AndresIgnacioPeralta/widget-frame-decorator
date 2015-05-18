#ifndef CONTAINERFRAME_H
#define CONTAINERFRAME_H
#include <QFrame>
#include "ui_containerframe.h"

class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QSpacerItem;
class QLabel;

enum class ToolBarItem {
    LOGO,
    TITLE,
    MINIMIZE,
    MAXIMIZE,
    HELP,
    ONTOP,
    CLOSE
};

typedef QMap<ToolBarItem, bool> TopBarConfiguration;

class ContainerFrame : public QFrame, public Ui::ContainerWidgetClass {
    Q_OBJECT
public:
    ContainerFrame(QWidget* contained, QWidget* const parent = nullptr);

    void setBorderWidth(const unsigned int width);
    void showControlBar(const bool show);

private slots:
    void onButtonLogoClicked();
    void onButtonMinimizeClicked();
    void onButtonMaximizeClicked();
    void onButtonHelpClicked();
    void onButtonOnTopClicked(const bool checked);
    void onButtonCloseClicked();

private:
    void updateBorderWidth();
    void setTopBarIcons();

    QWidget* containedWidget;
    unsigned int borderWidth;
    bool hasTopBar;
};

#endif // CONTAINERFRAME_H
