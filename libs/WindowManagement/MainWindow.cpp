#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "MainWindow.h"
#include "Windows/EducationalSection.h"
#include "Windows/MainMenu.h"
#include "Windows/Settings.h"
#include "Windows/Constructor.h"

#include "LanguageManager/LangManager.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
};

void MainWindow::applyLanguage(){
    m_mainMenu->retranslateUI();
    m_eduPage->retranslateUI();
    m_setPage->retranslateUI();
    m_conPage->retranslateUI();
}

void MainWindow::setupUI(){
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    m_stackedWidget = new QStackedWidget(this);

    m_mainMenu = new MainMenu(this);
    m_eduPage = new EducationalSection(this);
    m_setPage = new Settings(this);
    m_conPage = new Constructor(this);

    m_stackedWidget->addWidget(m_mainMenu);
    m_stackedWidget->addWidget(m_eduPage);
    m_stackedWidget->addWidget(m_setPage);
    m_stackedWidget->addWidget(m_conPage);

    mainLayout->addWidget(m_stackedWidget);

    setWindowTitle("LogicGateSim");
}

void MainWindow::setupConnections(){
    // main menu
    connect(m_mainMenu, &MainMenu::switchToEducationalSection, [this](){
        m_stackedWidget->setCurrentWidget(m_eduPage);
    });

    connect(m_mainMenu, &MainMenu::switchToSettings, [this](){
        m_stackedWidget->setCurrentWidget(m_setPage);
    });

    connect(m_mainMenu, &MainMenu::switchToConstructor, [this](){
        m_stackedWidget->setCurrentWidget(m_conPage);
    });

    // educational section
    connect(m_eduPage, &EducationalSection::switchToMainMenu, [this](){
        m_stackedWidget->setCurrentWidget(m_mainMenu);
    });

    connect(m_setPage, &Settings::switchToMainMenu, [this](){
        m_stackedWidget->setCurrentWidget(m_mainMenu);
    });
    
    // constructor
    connect(m_conPage, &Constructor::switchToMainMenu, [this](){
        m_stackedWidget->setCurrentWidget(m_mainMenu);
    });

    // settings
    connect(m_setPage, &Settings::switchLang, [this](int index) {
        LangManager::instance().setLanguage(index);
        this->applyLanguage(); 
    });

}
