#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <qpushbutton.h>

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

void MainMenu::retranslateUI(){
    auto &lang = LangManager::instance();

    educationalSectionButton->setText(lang.get("educationalSectionButton"));
    constructorButton->setText(lang.get("constructorButton"));
    settingsButton->setText(lang.get("settingsButton"));
}

void MainMenu::setupUI(){
    auto *gridLayout = new QGridLayout(this);


    educationalSectionButton = new QPushButton(this);
    constructorButton = new QPushButton(this);
    settingsButton = new QPushButton(this);
    
    gridLayout->addWidget(educationalSectionButton, 0, 0);
    gridLayout->addWidget(constructorButton, 1, 0);
    gridLayout->addWidget(settingsButton, 2, 0);


}

void MainMenu::setupConnections(){
    connect(educationalSectionButton, &QPushButton::clicked,
            this, &MainMenu::onEducationalSectionButtonClicked);

    connect(constructorButton, &QPushButton::clicked,
            this, &MainMenu::onConstructorButtonClicked);

    connect(settingsButton, &QPushButton::clicked,
            this, &MainMenu::onSettingsButtonClicked);

}

