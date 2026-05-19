#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStackedWidget>

#include "Settings.h"
#include "LanguageManager/LangManager.h"
#include "Settings/InterfaceSettings.h"

Settings::Settings(QWidget *parent) : QWidget(parent) {
    setupUI();
    retranslateUI();
    setupConnections();
}

void Settings::onMainMenuButtonClicked(){
    emit switchToMainMenu();
}

void Settings::onChangeLangButtonClicked(int selectedIndex){
    emit switchLang(selectedIndex);
}

void Settings::retranslateUI(){
    auto &lang = LangManager::instance();

    mainMenuButton->setText(lang.get("mainMenuButton"));
    interfaceButton->setText(lang.get("interfaceButton"));
    constructorButton->setText(lang.get("constructorButton"));
    controlsButton->setText(lang.get("controlsButton"));
}

void Settings::setupUI() {
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
    logoLabel->setPixmap(logoPixmap.scaled(320, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setStyleSheet("background: transparent;");
    
    containerLayout->addWidget(logoLabel);

    QString menuPanelStyle = 
        "QFrame {"
        "  background-color: transparent;" 
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
        "}";

    stackedWidget = new QStackedWidget(centralMenuContainer);

    mainSettingsPanel = new QFrame(stackedWidget);
    mainSettingsPanel->setFixedWidth(320);
    mainSettingsPanel->setStyleSheet(menuPanelStyle);

    auto *mainSettingsLayout = new QVBoxLayout(mainSettingsPanel);
    mainSettingsLayout->setContentsMargins(0, 0, 0, 0);
    mainSettingsLayout->setSpacing(0);

    interfaceButton = new QPushButton(mainSettingsPanel);
    constructorButton = new QPushButton(mainSettingsPanel);
    controlsButton = new QPushButton(mainSettingsPanel);
    mainMenuButton = new QPushButton(mainSettingsPanel);

    mainSettingsLayout->addWidget(interfaceButton);
    mainSettingsLayout->addWidget(constructorButton);
    mainSettingsLayout->addWidget(controlsButton);
    mainSettingsLayout->addWidget(mainMenuButton);

    stackedWidget->addWidget(mainSettingsPanel);

    interfaceSettingsPage = new InterfaceSettings(menuPanelStyle, stackedWidget);
    stackedWidget->addWidget(interfaceSettingsPage);

    containerLayout->addWidget(stackedWidget);

    gridLayout->addWidget(centralMenuContainer, 2, 2);
    gridLayout->setRowStretch(1, 1);    
    gridLayout->setRowStretch(3, 1);    
    gridLayout->setColumnStretch(1, 1); 
    gridLayout->setColumnStretch(3, 1); 

    mainLayout->addWidget(overlayWidget, 1, 1);
}

void Settings::applyLanguage(){
    this->retranslateUI();
    interfaceSettingsPage->retranslateUI();
}

void Settings::setupConnections(){
    connect(mainMenuButton, &QPushButton::clicked,
            this, &Settings::onMainMenuButtonClicked);

    connect(interfaceButton, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentWidget(interfaceSettingsPage);
    });

    connect(interfaceSettingsPage, &InterfaceSettings::backToSettingsMenu, [this]() {
        stackedWidget->setCurrentWidget(mainSettingsPanel);
    });

    connect(interfaceSettingsPage, &InterfaceSettings::languageChanged,
            this, &Settings::onChangeLangButtonClicked);

    connect(interfaceSettingsPage, &InterfaceSettings::languageChanged, [this](int index){
        onChangeLangButtonClicked(index);
        this->applyLanguage();
    });
}

