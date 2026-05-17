#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>

#include "MainMenu.h"
#include "LanguageManager/LangManager.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    setupUI();
    retranslateUI();
    setupConnections();
}

void MainMenu::onEducationalSectionButtonClicked(){
    emit switchToEducationalSection();
}

void MainMenu::onConstructorButtonClicked(){
    emit switchToConstructor();
}

void MainMenu::onSettingsButtonClicked(){
    emit switchToSettings();
}

void MainMenu::onLessonConstructorButtonClicked(){
    emit switchToLessonConstructor();
}

void MainMenu::retranslateUI(){
    auto &lang = LangManager::instance();

    educationalSectionButton->setText(lang.get("educationalSectionButton"));
    constructorButton->setText(lang.get("constructorButton"));
    settingsButton->setText(lang.get("settingsButton"));
    lessonConstructorButton->setText(lang.get("lessonConstructorButton"));
}

void MainMenu::setupUI(){
    auto *mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0); 

    auto *animationBackground = new QWidget(this);
    animationBackground->setStyleSheet("background-color: #4A5062;");
    mainLayout->addWidget(animationBackground, 1, 1);

    auto *overlayWidget = new QWidget(this);
    auto *gridLayout = new QGridLayout(overlayWidget);
    
    gridLayout->setContentsMargins(0, 0, 0, 0);

    auto *centralMenuContainer = new QWidget(overlayWidget);
    centralMenuContainer->setFixedWidth(320);

    auto *containerLayout = new QVBoxLayout(centralMenuContainer);
    containerLayout->setContentsMargins(0, 0, 0, 0);
    containerLayout->setSpacing(0);

    auto *logoLabel = new QLabel(centralMenuContainer);
    QPixmap logoPixmap(":/resources/logo_lgs.png");

    logoLabel->setPixmap(logoPixmap.scaled(320, 150,
                                    Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setStyleSheet("background: transparent;");

    auto *menuPanel = new QFrame(centralMenuContainer);
    menuPanel->setFixedWidth(320); 
    menuPanel->setStyleSheet(
        "QFrame {"
        "  background-color: #3C4252;" 
        "  border-radius: 0px;"
        "}"
        "QPushButton {"
        "  background-color: #434C5E;" 
        "  border: 3px solid #2E3440;"   
        "  border-top: none;"
        "  border-radius: 0px;"
        "  color: #ffffff;"
        "  font-size: 16px;"           
        "  font-weight: bold;"
        "  padding: 12px 5px;"        
        "}"
        "QPushButton:hover {"
        "  background-color: #4C566A;"
        "}"
    );

    auto *menuLayout = new QVBoxLayout(menuPanel);
    menuLayout->setContentsMargins(0, 0, 0, 0); 
    menuLayout->setSpacing(0);                     

    educationalSectionButton = new QPushButton(menuPanel);
    constructorButton = new QPushButton(menuPanel);
    settingsButton = new QPushButton(menuPanel);
    lessonConstructorButton = new QPushButton(menuPanel);

    menuLayout->addWidget(educationalSectionButton);
    menuLayout->addWidget(constructorButton);
    menuLayout->addWidget(settingsButton);
    menuLayout->addWidget(lessonConstructorButton);

    containerLayout->addWidget(logoLabel);
    containerLayout->addWidget(menuPanel);

    gridLayout->addWidget(centralMenuContainer, 2, 2);

    gridLayout->setRowStretch(1, 1);    
    gridLayout->setRowStretch(3, 1);    
    gridLayout->setColumnStretch(1, 1); 
    gridLayout->setColumnStretch(3, 1); 

    mainLayout->addWidget(overlayWidget, 1, 1);

}

void MainMenu::setupConnections(){
    connect(educationalSectionButton, &QPushButton::clicked,
            this, &MainMenu::onEducationalSectionButtonClicked);

    connect(constructorButton, &QPushButton::clicked,
            this, &MainMenu::onConstructorButtonClicked);

    connect(settingsButton, &QPushButton::clicked,
            this, &MainMenu::onSettingsButtonClicked);
    
    connect(lessonConstructorButton, &QPushButton::clicked,
            this, &MainMenu::onLessonConstructorButtonClicked);
}

