#pragma once

#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>

#include "ConstructorScheme.h"

class Constructor : public QWidget {
    Q_OBJECT
public:
    explicit Constructor(QWidget *parent = nullptr);

    void retranslateUI();

signals:
    void switchToMainMenu();
    
private slots:
    void onMainMenuButtonClicked();

private:
    QWidget *topBar;
    QWidget *projectControlBar;
    QWidget *instrumentBar;
    QWidget *infoSidebar;

    QLabel *titleLabel;
    QPushButton *mainMenuButton;
    QPushButton *newProjectBtn;
    QPushButton *openProjectBtn;
    QPushButton *saveProjectBtn;
    QPushButton *startSimBtn;
    QPushButton *stopSimBtn;

    ConstructorScheme *c_scene;
    QGraphicsView *c_view;

    QWidget *previewBlock;
    QWidget *specsBlock;
    QWidget *historyBlock;
    QPushButton *undoBtn;
    
    void setupUI();
    void setupConnections();
    void setupRules();

    void addItem(qreal x, qreal y);
    void addDCPower();
    void addLED();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

