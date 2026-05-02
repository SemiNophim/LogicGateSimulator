#pragma once

#include <QString>

#include "Language.h"

class EnglishLang : public Language {
public:
    QString langName() const override { return "English"; }

    // MainMenu
    QString eduSectionBtn() const override { return "Education"; }
    QString settingsBtn() const override { return "Settings"; }

    // EducationalSection
    QString mainMenuTitle() const override { return "Main menu"; }

    // Settings
    QString changeLangBtn() const override { return "Change language"; }
};
