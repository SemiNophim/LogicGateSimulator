#include <QWidget>
#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

#include <QEvent>
#include <QMouseEvent>
#include <QWheelEvent>

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QBrush> 
#include <QPen>
#include <QColor>
#include <Qt>

#include "Constructor.h"
#include "LanguageManager/LangManager.h"

Constructor::Constructor(QWidget *parent) : QWidget(parent){
    setupUI();
    retranslateUI();
    setupConnections();
    setupRules();
    testRect();
}

void Constructor::onMainMenuButtonClicked(){
    emit switchToMainMenu();
}

void Constructor::retranslateUI(){
    auto &lang = LangManager::instance();

    mainMenuButton->setText(lang.get("mainMenuButton"));
}

void Constructor::setupUI(){
    auto *gridLayout = new QGridLayout(this);

    mainMenuButton = new QPushButton(this);
    instrumentBar = new QWidget(this);
    c_scene = new ConstructorScheme(this);
    c_view = new QGraphicsView(c_scene, this);

    instrumentBar->setFixedWidth(150);
    auto *instrumentBarLayout = new QVBoxLayout(instrumentBar);

    instrumentBar->setStyleSheet("background-color: #2b2b2b; color: white;");

    auto *andGate = new QPushButton("andGate", instrumentBar);
    auto *orGate = new QPushButton("orGate", instrumentBar);

    instrumentBarLayout->addWidget(andGate);
    instrumentBarLayout->addWidget(orGate);
    instrumentBarLayout->addStretch();

    gridLayout->addWidget(mainMenuButton, 1, 2);
    gridLayout->addWidget(instrumentBar, 1, 1, 2, 1);
    gridLayout->addWidget(c_view, 2, 2);

    gridLayout->setRowStretch(2, 1);
    gridLayout->setColumnStretch(2, 1);
}

void Constructor::setupConnections(){
    connect(mainMenuButton, &QPushButton::clicked,
            this, &Constructor::onMainMenuButtonClicked);

}

void Constructor::setupRules(){
    c_view->setRenderHint(QPainter::Antialiasing); 
    c_view->setDragMode(QGraphicsView::RubberBandDrag); 
    c_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse); 

    c_view->viewport()->installEventFilter(this);
}

void Constructor::testRect(){
    QColor customColor("#848C8E");
    QBrush brush(customColor);
    QPen pen(Qt::black, 2);

    QGraphicsRectItem *gate = c_scene->addRect(100, 100, 80, 60, pen, brush);
    gate->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

bool Constructor::eventFilter(QObject *obj, QEvent *event){
    if (obj == c_view->viewport()){
        if(event->type() == QEvent::Wheel){
            auto *wheelEvent = static_cast<QWheelEvent*>(event);
        
            if(wheelEvent->modifiers() & Qt::ControlModifier){
                qreal currentScale = c_view->transform().m11();

                qreal factor = 1.1;
                if(wheelEvent->angleDelta().y() < 0){
                    factor = 1.0 / factor;
                }
            
                qreal nextScale = currentScale * factor;
            
                if(nextScale >= 0.3 && nextScale <= 3.0){
                    c_view->scale(factor, factor);
                }

                return true;
            }
        } 
        else if(event->type() == QEvent::MouseButtonPress){
            auto *mouseEvent = static_cast<QMouseEvent*>(event);
            
            if (mouseEvent->button() == Qt::MiddleButton) {
                c_view->setDragMode(QGraphicsView::ScrollHandDrag);
                
                QMouseEvent fakePress(
                    QEvent::MouseButtonPress, 
                    mouseEvent->position(), 
                    mouseEvent->globalPosition(),
                    Qt::LeftButton, 
                    Qt::LeftButton, 
                    mouseEvent->modifiers()
                );
                
                QApplication::sendEvent(c_view->viewport(), &fakePress);
                return true;
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease) {
            auto *mouseEvent = static_cast<QMouseEvent*>(event);
            
            if (mouseEvent->button() == Qt::MiddleButton) {
                QMouseEvent fakeRelease(
                    QEvent::MouseButtonRelease, 
                    mouseEvent->position(), 
                    mouseEvent->globalPosition(),
                    Qt::LeftButton, 
                    Qt::LeftButton, 
                    mouseEvent->modifiers()
                );
                
                QApplication::sendEvent(c_view->viewport(), &fakeRelease);

                c_view->setDragMode(QGraphicsView::RubberBandDrag);
                return true;
            }
        }
    }
    
    return QWidget::eventFilter(obj, event);
}

