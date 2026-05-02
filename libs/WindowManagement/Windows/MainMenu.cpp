#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <qpushbutton.h>

#include "MainMenu.h"
#include "LanguageManager/LangManager.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    auto *gridLayout = new QGridLayout(this);

    // Language manager
    auto *lang = LangManager::instance().current();

    educationalSectionButton = new QPushButton(lang->eduSectionBtn(), this);
    gridLayout->addWidget(educationalSectionButton, 0, 0);

    settingsButton = new QPushButton(lang->settingsBtn(), this);
    gridLayout->addWidget(settingsButton, 1,0);

    connect(educationalSectionButton, &QPushButton::clicked,
            this, &MainMenu::onEducationalSectionButtonClicked);

    connect(settingsButton, &QPushButton::clicked,
            this, &MainMenu::onSettingsButtonClicked);
}

void MainMenu::onEducationalSectionButtonClicked(){
    emit switchToEducationalSection();
}

void MainMenu::onSettingsButtonClicked(){
    emit switchToSettings();
}

void MainMenu::retranslateUI(){
    auto* lang = LangManager::instance().current();

    educationalSectionButton->setText(lang->eduSectionBtn());
    settingsButton->setText(lang->settingsBtn());
}

