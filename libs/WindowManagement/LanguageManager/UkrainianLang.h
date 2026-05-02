#pragma once

#include <QString>

#include "Language.h"

class UkrainianLang : public Language {
public:
    QString langName() const override { return "Українська"; }

    // MainMenu
    QString eduSectionBtn() const override { return "Навчання"; }
    QString settingsBtn() const override { return "Налаштування"; }

    // EducationalSection
    QString mainMenuTitle() const override { return "Головне меню"; }

    // Settings 
    QString changeLangBtn() const override { return "Змінити мову"; }

};

