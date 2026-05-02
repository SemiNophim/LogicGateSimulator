#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>

#include "Settings.h"
#include "LanguageManager/LangManager.h"

Settings::Settings(QWidget *parent) : QWidget(parent) {
    auto *gridLayout = new QGridLayout(this);

    // Language manager
    auto &langManager = LangManager::instance();
    auto *lang = langManager.current();

    mainMenuButton = new QPushButton(lang->mainMenuTitle(), this);
    gridLayout->addWidget(mainMenuButton, 1, 1);

    changeLangButton = new QPushButton(lang->changeLangBtn(), this);
    gridLayout->addWidget(changeLangButton, 2, 1);

    langBox = new QComboBox(this);

    for(int i = 0; i < langManager.languageCount(); i++){
        langBox->addItem(langManager.getLanguageName(i));
    }
    langBox->setCurrentIndex(langManager.currentIndex());

    gridLayout->addWidget(langBox, 2, 2);

    connect(mainMenuButton, &QPushButton::clicked,
            this, &Settings::onMainMenuButtonClicked);

    connect(changeLangButton, &QPushButton::clicked,
            this, &Settings::onChangeLangButtonClicked);
}

void Settings::onMainMenuButtonClicked(){
    emit switchToMainMenu();
}

void Settings::onChangeLangButtonClicked(){
    int selectedIndex = langBox->currentIndex();

    emit switchLang(selectedIndex);
}

void Settings::retranslateUI(){
    auto* lang = LangManager::instance().current();

    mainMenuButton->setText(lang->mainMenuTitle());
    changeLangButton->setText(lang->changeLangBtn());
}

