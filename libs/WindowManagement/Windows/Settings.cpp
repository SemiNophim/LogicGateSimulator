#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>

#include "Settings.h"
#include "LanguageManager/LangManager.h"

Settings::Settings(QWidget *parent) : QWidget(parent) {
    setupUI();
    retranslateUI();
    setupConnections();
}

void Settings::onMainMenuButtonClicked(){
    emit switchToMainMenu();
}

void Settings::onChangeLangButtonClicked(){
    int selectedIndex = langBox->currentIndex();

    emit switchLang(selectedIndex);
}

void Settings::retranslateUI(){
    auto &lang = LangManager::instance();

    mainMenuButton->setText(lang.get("mainMenuButton"));
    changeLangButton->setText(lang.get("changeLangButton"));
}

void Settings::setupUI(){
    auto *gridLayout = new QGridLayout(this);

    mainMenuButton = new QPushButton(this);
    changeLangButton = new QPushButton(this);
    langBox = new QComboBox(this);

    gridLayout->addWidget(mainMenuButton, 1, 1);
    gridLayout->addWidget(changeLangButton, 2, 1);
    gridLayout->addWidget(langBox, 2, 2);

    auto &langManager = LangManager::instance();
    for(int i = 0; i < langManager.languageCount(); i++){
        langBox->addItem(langManager.getLanguageName(i));
    }
    langBox->setCurrentIndex(langManager.currentIndex());
}

void Settings::setupConnections(){
    connect(mainMenuButton, &QPushButton::clicked,
            this, &Settings::onMainMenuButtonClicked);

    connect(changeLangButton, &QPushButton::clicked,
            this, &Settings::onChangeLangButtonClicked);

}
