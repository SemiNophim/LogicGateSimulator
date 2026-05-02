#pragma once
#include "LanguageManager/LangManager.h"
#include "LanguageManager/EnglishLang.h"
#include "LanguageManager/UkrainianLang.h"

void registerLanguages(){
    LangManager::instance().registerLanguage(std::make_unique<UkrainianLang>());
    LangManager::instance().registerLanguage(std::make_unique<EnglishLang>());
}
