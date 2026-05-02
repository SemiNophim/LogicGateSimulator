#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include "EducationalSection.h"
#include "LanguageManager/LangManager.h"

EducationalSection::EducationalSection(QWidget *parent) : QWidget(parent) {
    auto *gridLayout = new QGridLayout(this);

    // Language manager
    auto* lang = LangManager::instance().current();

    mainMenuButton = new QPushButton(lang->mainMenuTitle(), this);
    gridLayout->addWidget(mainMenuButton, 0, 0);

    connect(mainMenuButton, &QPushButton::clicked,
            this, &EducationalSection::onMainMenuButtonClicked);
}

void EducationalSection::onMainMenuButtonClicked(){
    emit switchToMainMenu();
}

void EducationalSection::retranslateUI(){
    auto *lang = LangManager::instance().current();

    mainMenuButton->setText(lang->mainMenuTitle());
}
