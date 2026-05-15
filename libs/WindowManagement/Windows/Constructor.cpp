#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include "Constructor.h"
#include "LanguageManager/LangManager.h"

Constructor::Constructor(QWidget *parent) : QWidget(parent){
    setupUI();
    retranslateUI();
    setupConnections();
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


    gridLayout->addWidget(mainMenuButton, 1, 1);

}

void Constructor::setupConnections(){
    connect(mainMenuButton, &QPushButton::clicked,
            this, &Constructor::onMainMenuButtonClicked);

}
