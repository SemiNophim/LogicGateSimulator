#pragma once

#include <QString>

class Language {
public:
    virtual ~Language() = default;

    virtual QString langName() const = 0;

    // MainMenu
    virtual QString eduSectionBtn() const = 0;
    virtual QString settingsBtn() const = 0;

    // EducationalSection
    virtual QString mainMenuTitle() const = 0;

    // Settings
    virtual QString changeLangBtn() const = 0;

};
