#include "InterfaceSettings.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QComboBox>
#include <QPushButton>
#include <QListView>
#include "LanguageManager/LangManager.h"

InterfaceSettings::InterfaceSettings(const QString &baseStyle, QWidget *parent) 
    : QFrame(parent), m_baseStyle(baseStyle) {
    setupUI();
    retranslateUI();
    setupConnections();
}

void InterfaceSettings::setupUI() {
    this->setFixedWidth(320);
    this->setContentsMargins(0, 0, 0, 0);

    this->setStyleSheet(m_baseStyle + 
        "QComboBox {"
        "  background-color: #434C5E;"
        "  color: #ffffff;"
        "  border: 3px solid #2E3440;"
        "  border-top: none;"
        "  border-radius: 0px;"
        "  padding: 0px 5px;"
        "  height: 45px;"
        "  margin: 0px;"
        "  font-size: 16px;"
        "  font-weight: bold;"
        "}"
        "QComboBox QAbstractItemView {"
        "  background-color: #3C4252;"
        "  color: #ffffff;"
        "  selection-background-color: #434C5E;"
        "  border: 2px solid #2E3440;"
        "  margin: 0px;"
        "}"
        "QPushButton {"
        "  margin: 0px;"
        "}"
    );

    auto *menuLayout = new QVBoxLayout(this);
    menuLayout->setContentsMargins(0, 0, 0, 0); 
    menuLayout->setSpacing(0); 

    langBox = new QComboBox(this);
    langBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    langBox->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    langBox->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    auto &langManager = LangManager::instance();
    for(int i = 0; i < langManager.languageCount(); i++){
        langBox->addItem(langManager.getLanguageName(i));
    }
    langBox->setCurrentIndex(langManager.currentIndex());

    changeLangButton = new QPushButton(this);

    backButton = new QPushButton(this);

    menuLayout->addWidget(langBox);
    menuLayout->addWidget(changeLangButton);
    menuLayout->addWidget(backButton);

    menuLayout->addStretch(1);
}

void InterfaceSettings::setupConnections() {
    connect(backButton, &QPushButton::clicked,
            this, &InterfaceSettings::onBackButtonClicked);

    connect(changeLangButton, &QPushButton::clicked, [this]() {
        this->onLangChanged(langBox->currentIndex());
    });
}

void InterfaceSettings::onBackButtonClicked() {
    emit backToSettingsMenu();
}

void InterfaceSettings::onLangChanged(int index) {
    auto &langManager = LangManager::instance();
    if (index != langManager.currentIndex()) {
        langManager.setLanguage(index); 
        emit languageChanged(index);
    }
}

void InterfaceSettings::retranslateUI() {
    auto &lang = LangManager::instance();
    backButton->setText(lang.get("backButton")); 
    changeLangButton->setText(lang.get("changeLangButton"));
}

