#pragma once

#include <QString>

#include "Language.h"

class LangManager {
public:
    static LangManager& instance() {
        static LangManager inst;
        return inst;
    }

    void registerLanguage(std::unique_ptr<Language> lang) {
        m_languages.emplace_back(std::move(lang));
    }

    Language* current() { return m_languages[m_currentIndex].get(); }

    int currentIndex() const {
        return m_currentIndex;
    }

    int languageCount() const {
        return m_languages.size();
    }

    QString getLanguageName(int index) const {
        if (index >= 0 && index < languageCount()) {
            return m_languages[index]->langName();
        }
        return "";
    }

    void setLanguage(int index) {
        if (index >= 0 && index < languageCount()) {
            m_currentIndex = index;
        }
    }

private:
    LangManager() = default;
    std::vector<std::unique_ptr<Language>> m_languages;
    int m_currentIndex = 0;
};

