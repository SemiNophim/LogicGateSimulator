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

bool placeble = false;

Constructor::Constructor(QWidget *parent) : QWidget(parent){
    setupUI();
    setupConnections();
    setupRules();
}

void Constructor::onMainMenuButtonClicked(){
    emit switchToMainMenu();
}

void Constructor::retranslateUI(){
    auto &lang = LangManager::instance();

    mainMenuButton->setText(lang.get("mainMenuButton"));
    newProjectBtn->setText(lang.get("newProjectButton"));
    openProjectBtn->setText(lang.get("openProjectButton"));
    saveProjectBtn->setText(lang.get("saveProjectButton"));
    startSimBtn->setText(lang.get("startSimButton"));
    stopSimBtn->setText(lang.get("stopSimButton"));
    undoBtn->setText(lang.get("undoButton"));
    titleLabel->setText(lang.get("constructorTitle"));
}

void Constructor::setupUI(){
    mainMenuButton = new QPushButton(this);
    newProjectBtn = new QPushButton(this);
    openProjectBtn = new QPushButton(this);
    saveProjectBtn = new QPushButton(this);
    startSimBtn = new QPushButton(this);
    stopSimBtn = new QPushButton(this);
    undoBtn = new QPushButton(this);
    
    titleLabel = new QLabel(this);
    instrumentBar = new QWidget(this);
    c_scene = new ConstructorScheme(this);
    c_view = new QGraphicsView(c_scene, this);
    
    retranslateUI();

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    this->setStyleSheet(
        "QWidget {"
        "  background-color: #2E3440;"
        "  font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QPushButton {"
        "  background-color: #434C5E;"
        "  color: #ffffff;"
        "  border: 1px solid #2E3440;"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  padding: 10px;"
        "  margin: 0px;"
        "  border-radius: 0px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #4C566A;"
        "}"
        "QLabel {"
        "  color: #ffffff;"
        "  font-weight: bold;"
        "}"
    );

    topBar = new QWidget(this);
    topBar->setObjectName("topBar");
    topBar->setStyleSheet(
        "QWidget#topBar {"
        "  background-color: #2E3440;"
        "  border-bottom: 3px solid #2E3440;"
        "}"
    );
    
    auto *topBarLayout = new QHBoxLayout(topBar);
    topBarLayout->setContentsMargins(15, 10, 15, 10);
    
    titleLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 20px;"
        "  font-weight: bold;"
        "}"
    );
    
    
    topBarLayout->addWidget(titleLabel, 1, Qt::AlignCenter);
    mainLayout->addWidget(topBar);

    projectControlBar = new QWidget(this);
    projectControlBar->setObjectName("controlBar");
    projectControlBar->setStyleSheet(
        "QWidget#controlBar {"
        "  background-color: #3B4252;"
        "  border-bottom: 3px solid #2E3440;"
        "}"
    );
    
    auto *controlLayout = new QHBoxLayout(projectControlBar);
    controlLayout->setContentsMargins(0, 0, 0, 0);
    controlLayout->setSpacing(0);

    mainMenuButton->setFixedWidth(160);
    mainMenuButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #BF616A;"
        "}"
        "QPushButton:hover {"
        "  background-color: #ED7C87;"
        "}"

    );

    startSimBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: #434C5E;"
        "  color: #A3BE8C;"
        "}"
        "QPushButton:hover {"
        "  background-color: #4C566A;"
        "}"
    ); 
    
    stopSimBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: #434C5E;"
        "  color: #BF616A;"
        "}"
        "QPushButton:hover {"
        "  background-color: #4C566A;"
        "}"
    );  

    mainMenuButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    newProjectBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    openProjectBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    saveProjectBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    startSimBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    stopSimBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    controlLayout->addWidget(mainMenuButton);
    controlLayout->addWidget(newProjectBtn);
    controlLayout->addWidget(openProjectBtn);
    controlLayout->addWidget(saveProjectBtn);
    controlLayout->addWidget(startSimBtn);
    controlLayout->addWidget(stopSimBtn);
    mainLayout->addWidget(projectControlBar);

    auto *workspaceWidget = new QWidget(this);
    auto *workspaceLayout = new QHBoxLayout(workspaceWidget);
    workspaceLayout->setContentsMargins(0, 0, 0, 0);
    workspaceLayout->setSpacing(0);

    instrumentBar->setFixedWidth(160);
    instrumentBar->setStyleSheet(
        "QWidget {"
        "  background-color: #3B4252;"
        "  border-right: 3px solid #2E3440;"
        "}"
    );
    
    auto *instrumentGrid = new QGridLayout(instrumentBar);
    instrumentGrid->setContentsMargins(0, 0, 0, 0);
    instrumentGrid->setSpacing(0);

    auto *andGate = new QPushButton("AND", instrumentBar);
    andGate->setStyleSheet(
        "QPushButton {"
        "  background-color: #434C5E;"
        "  border: 2px solid #2E3440;"
        "  font-size: 12px;"
        "}"
    );
    connect(andGate, &QPushButton::clicked, this, [](){ placeble = true; });
    
    auto *orGate = new QPushButton("OR", instrumentBar);
    orGate->setStyleSheet(
        "QPushButton {"
        "  background-color: #434C5E;"
        "  border: 2px solid #2E3440;"
        "  font-size: 12px;"
        "}"
    );

    instrumentGrid->addWidget(andGate, 0, 0);
    instrumentGrid->addWidget(orGate, 0, 1);
    instrumentGrid->setRowStretch(1, 1); 

    c_view->setStyleSheet(
        "QGraphicsView {"
        "  border: none;"
        "  background-color: #ECEFF4;"
        "}"
    );

    infoSidebar = new QWidget(this);
    infoSidebar->setFixedWidth(240);
    infoSidebar->setStyleSheet(
        "QWidget {"
        "  background-color: #3B4252;"
        "  border-left: 3px solid #2E3440;"
        "}"
    );
    
    auto *sidebarLayout = new QVBoxLayout(infoSidebar);
    sidebarLayout->setContentsMargins(0, 0, 0, 0);
    sidebarLayout->setSpacing(0);

    previewBlock = new QWidget(infoSidebar);
    previewBlock->setFixedHeight(140);
    previewBlock->setStyleSheet(
        "QWidget {"
        "  background-color: #ffffff;"
        "  border-bottom: 3px solid #2E3440;"
        "  margin: 10px;"
        "}"
    ); 
    
    specsBlock = new QWidget(infoSidebar);
    auto *specsLayout = new QVBoxLayout(specsBlock);
    specsLayout->setContentsMargins(15, 10, 15, 10);
    
    auto *specTitle = new QLabel("Кон'юнктор\nНапруга: 3.3 В\nСтрум: X.X А\nОпір: X.X Ом", specsBlock);
    specTitle->setStyleSheet(
        "QLabel {"
        "  font-size: 13px;"
        "  line-height: 1.4;"
        "  color: #E5E9F0;"
        "}"
    );
    
    specsLayout->addWidget(specTitle);
    specsBlock->setStyleSheet(
        "QWidget {"
        "  border-bottom: 3px solid #2E3440;"
        "}"
    );

    historyBlock = new QWidget(infoSidebar);
    auto *historyLayout = new QVBoxLayout(historyBlock);
    historyLayout->setContentsMargins(15, 10, 15, 10);
    
    auto *historyTitle = new QLabel("Історія змін:\nsnap12 (поточний стан)\nsnap11\nsnap10", historyBlock);
    historyTitle->setStyleSheet(
        "QLabel {"
        "  font-size: 12px;"
        "  color: #D8DEE9;"
        "}"
    );
    
    historyLayout->addWidget(historyTitle);
    historyLayout->addStretch(1);

    undoBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: #4C566A;"
        "  border-top: 3px solid #2E3440;"
        "}"
    );

    sidebarLayout->addWidget(previewBlock);
    sidebarLayout->addWidget(specsBlock);
    sidebarLayout->addWidget(historyBlock, 1);
    sidebarLayout->addWidget(undoBtn);

    workspaceLayout->addWidget(instrumentBar);
    workspaceLayout->addWidget(c_view, 1);
    workspaceLayout->addWidget(infoSidebar);

    mainLayout->addWidget(workspaceWidget, 1);
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

void Constructor::testRect(const QPointF &pos){
    QColor customColor("#848C8E");
    QBrush brush(customColor);
    QPen pen(Qt::black, c_scene->getBorderSize());

    int step = c_scene->getGridSize();

    qreal snappedX = std::round(pos.x() / step) * step;
    qreal snappedY = std::round(pos.y() / step) * step;

    QGraphicsRectItem *gate = c_scene->addRect(snappedX, snappedY, 80, 60, pen, brush);
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
            else if(mouseEvent->button() == Qt::LeftButton && placeble){
                QPointF scenePos = c_view->mapToScene(mouseEvent->position().toPoint());
                testRect(scenePos);
                placeble = false;

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

