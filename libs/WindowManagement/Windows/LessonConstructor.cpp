#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include "LessonConstructor.h"
#include "LanguageManager/LangManager.h"

LessonConstructor::LessonConstructor(QWidget *parent) : QWidget(parent){
    setupUI();
    retranslateUI();
    setupConnections();
}

void LessonConstructor::onMainMenuButtonClicked(){
    emit switchToMainMenu();
}

void LessonConstructor::retranslateUI(){
    auto &lang = LangManager::instance();

    mainMenuButton->setText(lang.get("mainMenuButton"));
}

void LessonConstructor::setupUI(){
    auto *gridLayout = new QGridLayout(this);

    mainMenuButton = new QPushButton(this);


    gridLayout->addWidget(mainMenuButton, 1, 1);
}

void LessonConstructor::setupConnections(){
    connect(mainMenuButton, &QPushButton::clicked,
            this, &LessonConstructor::onMainMenuButtonClicked);
}
