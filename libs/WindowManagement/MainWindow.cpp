#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "MainWindow.h"
#include "Windows/EducationalSection.h"
#include "Windows/MainMenu.h"
#include "Windows/Settings.h"
#include "LanguageManager/LangManager.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    m_stackedWidget = new QStackedWidget(this);

    m_mainMenu = new MainMenu(this);
    m_eduPage = new EducationalSection(this);
    m_setPage = new Settings(this);

    m_stackedWidget->addWidget(m_mainMenu);
    m_stackedWidget->addWidget(m_eduPage);
    m_stackedWidget->addWidget(m_setPage);

    mainLayout->addWidget(m_stackedWidget);

    setWindowTitle("LogicGateSim");

    connect(m_mainMenu, &MainMenu::switchToEducationalSection, [this](){
        m_stackedWidget->setCurrentWidget(m_eduPage);
    });

    connect(m_mainMenu, &MainMenu::switchToSettings, [this](){
        m_stackedWidget->setCurrentWidget(m_setPage);
    });

    connect(m_eduPage, &EducationalSection::switchToMainMenu, [this](){
        m_stackedWidget->setCurrentWidget(m_mainMenu);
    });

    connect(m_setPage, &Settings::switchToMainMenu, [this](){
        m_stackedWidget->setCurrentWidget(m_mainMenu);
    });

    connect(m_setPage, &Settings::switchLang, [this](int index) {
        LangManager::instance().setLanguage(index);
        // Викликаєш метод, який оновить тексти у всіх вікнах
        this->applyLanguage(); 
    });
};

void MainWindow::applyLanguage(){
    auto *lang = LangManager::instance().current();

    m_mainMenu->retranslateUI();
    m_eduPage->retranslateUI();
    m_setPage->retranslateUI();
}

