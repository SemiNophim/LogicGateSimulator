#pragma once

#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>

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
    QPushButton *mainMenuButton;
    QWidget *instrumentBar;
    ConstructorScheme *c_scene;
    QGraphicsView *c_view;
    
    void setupUI();
    void setupConnections();
    void setupRules();
    void testRect(const QPointF &pos);
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

