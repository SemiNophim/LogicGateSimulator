#pragma once

#include <QString>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <vector>

struct LangInfo{
    QString fileName;
    QString displayName;
};

class LangManager {
public:
    static LangManager& instance() {
        static LangManager inst;
        return inst;
    }

    void scanLanguages() {
        m_languages.clear();
        QString path = QCoreApplication::applicationDirPath() + "/locales";
        QDir dir(path);

        if (!dir.exists()) {
            dir.mkpath("."); 
        }

        QStringList filters;
        filters << "*.json";
        QStringList files = dir.entryList(filters, QDir::Files);

        for (const QString& fileName : files) {
            QFile file(path + "/" + fileName);
            if (file.open(QIODevice::ReadOnly)) {
                QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
                QString dName = doc.object().value("langName").toString(fileName);
                m_languages.push_back({fileName, dName});
                file.close();
            }
        }
        
        if (!m_languages.empty() && m_currentData.isEmpty()) {
            setLanguage(0);
        }
    }

    void setLanguage(int index) {
        if (index >= 0 && index < languageCount()) {
            QString path = QCoreApplication::applicationDirPath() 
                + "/locales/" + m_languages[index].fileName;
            QFile file(path);

            if (file.open(QIODevice::ReadOnly)) {
                QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
                m_currentData = doc.object();
                m_currentIndex = index;
                file.close();
            }
        }
    }

    QString get(const QString &key) const{
        return m_currentData.value(key).toString("MISSING: " + key);
    }

    int currentIndex() const {
        return m_currentIndex;
    }

    int languageCount() const {
        return m_languages.size();
    }

    QString getLanguageName(int index) const {
        if (index >= 0 && index < languageCount()) {
            return m_languages[index].displayName;
        }
        return "";
    }

    
private:
    LangManager(){
        scanLanguages();
    };
    std::vector<LangInfo> m_languages;
    QJsonObject m_currentData;
    int m_currentIndex = 0;

    LangManager(const LangManager&) = delete;
    LangManager & operator = (const LangManager&) = delete;
};

