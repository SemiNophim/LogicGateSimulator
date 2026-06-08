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

    enum class EditorMode {
        Select,  
        PlaceItem, 
        DrawWire  
    };

    EditorMode m_currentMode = EditorMode::Select;
    Pin *m_selectedStartPin = nullptr;
    Wire *m_previewWire = nullptr;
    Element *bufferElement = nullptr;

    void addItem(qreal x, qreal y);
    void shadowItemLogic();
    void addDCPower();
    void addLED();
    void addGround();

    bool handleWheelEvent(QWheelEvent *wheelEvent);
    bool handleMousePressEvent(QMouseEvent *mouseEvent);
    bool handleMouseMoveEvent(QMouseEvent *mouseEvent);
    bool handleMouseReleaseEvent(QMouseEvent *mouseEvent);

    void handleBufferElements();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

