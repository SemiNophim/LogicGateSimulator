#include "TopicsPage.h"
#include "LanguageManager/LangManager.h"
#include <QDir>
#include <QCoreApplication>
#include <QFileInfo>

TopicsPage::TopicsPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}

void TopicsPage::setupUI() {
    auto *mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto *centralFrame = new QFrame(this);
    centralFrame->setFixedWidth(800);
    centralFrame->setObjectName("centralFrame");
    centralFrame->setStyleSheet(
        "QFrame#centralFrame {"
        "  background-color: #3B4252;"
        "  border-radius: 8px;"
        "  border: none;"
        "}"
    );

    auto *frameLayout = new QVBoxLayout(centralFrame);
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->setSpacing(0);

    auto *innerTopBar = new QWidget(centralFrame);
    innerTopBar->setObjectName("innerTopBar");
    innerTopBar->setStyleSheet(
        "QWidget#innerTopBar {"
        "  background-color: #2E3440;"
        "  border-top-left-radius: 8px;"
        "  border-top-right-radius: 8px;"
        "  border-bottom: 3px solid #2E3440;"
        "}"
    );
    
    auto *topBarLayout = new QHBoxLayout(innerTopBar);
    topBarLayout->setContentsMargins(20, 12, 20, 12);

    titleLabel = new QLabel(innerTopBar);
    titleLabel->setStyleSheet(
        "QLabel {"
        "  font-family: 'Segoe UI';"
        "  font-size: 20px;"
        "  font-weight: bold;"
        "  color: #ffffff;"
        "  background: transparent;"
        "}"
    );
    
    mainMenuButton = new QPushButton(innerTopBar);
    mainMenuButton->setFixedWidth(120);
    mainMenuButton->setStyleSheet(
        "QPushButton {"
        "  font-family: 'Segoe UI';"
        "  background-color: #BF616A;"
        "  color: #ffffff;"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  padding: 8px;"
        "  border-radius: 4px;"
        "  border: 2px solid #2E3440;"
        "}"
        "QPushButton:hover {"
        "  background-color: #D08770;"
        "}"
    );

    auto *scrollArea = new QScrollArea(centralFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet(
        "QScrollArea {"
        "  border: none;"
        "  background-color: transparent;"
        "}"
        "QScrollBar:vertical {"
        "  border: none;"
        "  background: #3B4252;"
        "  width: 8px;"
        "  margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "  background: #4C566A;"
        "  min-height: 20px;"
        "  border-radius: 4px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "  background: #D8DEE9;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "  border: none;"
        "  background: none;"
        "}"
    );

    auto *contentContainer = new QWidget();
    contentContainer->setObjectName("contentContainer");
    contentContainer->setStyleSheet(
        "QWidget#contentContainer {"
        "  background-color: #3B4252;"
        "  border-bottom-left-radius: 8px;"
        "  border-bottom-right-radius: 8px;"
        "}"
    );

    auto *listLayout = new QVBoxLayout(contentContainer);
    listLayout->setContentsMargins(0, 10, 0, 15);
    listLayout->setSpacing(0);

    QString lessonsDirPath = QCoreApplication::applicationDirPath() + "/lessons";
    QDir lessonsDir(lessonsDirPath);
    QStringList filters;
    filters << "*.md";
    lessonsDir.setNameFilters(filters);
    lessonsDir.setSorting(QDir::Name | QDir::LocaleAware);
    QFileInfoList fileList = lessonsDir.entryInfoList();

    startButtons.clear();

    if (fileList.isEmpty()) {
        auto *emptyLabel = new QLabel(contentContainer);
        emptyLabel->setText("Уроки не знайдено в папці:\n" + lessonsDirPath);
        emptyLabel->setStyleSheet(
            "QLabel {"
            "  color: #BF616A;"
            "  font-family: 'Segoe UI';"
            "  font-size: 14px;"
            "  padding: 30px;"
            "}"
        );
        emptyLabel->setAlignment(Qt::AlignCenter);
        listLayout->addWidget(emptyLabel);
    } else {
        for (int i = 0; i < fileList.size(); ++i) {
            QFileInfo fileInfo = fileList.at(i);
            
            auto *rowWidget = new QWidget(contentContainer);
            auto *rowLayout = new QHBoxLayout(rowWidget);
            rowLayout->setContentsMargins(30, 18, 30, 18);
            rowLayout->setSpacing(0);

            if (i < fileList.size() - 1) {
                rowWidget->setStyleSheet(
                    "QWidget {"
                    "  border-bottom: 1px solid #4C566A;"
                    "}"
                );
            }

            auto *lessonTitle = new QLabel(rowWidget);
            lessonTitle->setText(fileInfo.baseName());
            lessonTitle->setStyleSheet(
                "QLabel {"
                "  font-family: 'Segoe UI';"
                "  color: #ffffff;"
                "  font-size: 16px;"
                "  font-weight: bold;"
                "  border: none;"
                "  background: transparent;"
                "}"
            );

            auto *startButton = new QPushButton(rowWidget);
            startButton->setFixedSize(100, 35);
            startButton->setStyleSheet(
                "QPushButton {"
                "  font-family: 'Segoe UI';"
                "  background-color: #434C5E;"
                "  color: #ffffff;"
                "  border: 1px solid #2E3440;"
                "  font-size: 13px;"
                "  font-weight: bold;"
                "  border-radius: 15px;"
                "}"
                "QPushButton:hover {"
                "  background-color: #4C566A;"
                "}"
            );

            startButtons.append(startButton);

            QString absoluteFilePath = fileInfo.absoluteFilePath();
            connect(startButton, &QPushButton::clicked, [this, absoluteFilePath]() {
                emit lessonSelected(absoluteFilePath);
            });

            rowLayout->addWidget(lessonTitle);
            rowLayout->addStretch(1);
            rowLayout->addWidget(startButton);
            
            listLayout->addWidget(rowWidget);
        }
    }

    retranslateUI();

    topBarLayout->addSpacing(120); 
    topBarLayout->addWidget(titleLabel, 1, Qt::AlignCenter);
    topBarLayout->addWidget(mainMenuButton);
    frameLayout->addWidget(innerTopBar);

    listLayout->addStretch(1);
    scrollArea->setWidget(contentContainer);
    frameLayout->addWidget(scrollArea, 1);

    mainLayout->addWidget(centralFrame, 2, 2);
    mainLayout->setRowStretch(1, 1);    
    mainLayout->setRowStretch(3, 1);    
    mainLayout->setColumnStretch(1, 1); 
    mainLayout->setColumnStretch(3, 1); 
}

void TopicsPage::setupConnections() {
    connect(mainMenuButton, &QPushButton::clicked, this, &TopicsPage::switchToMainMenu);
}

void TopicsPage::retranslateUI() {
    auto &lang = LangManager::instance();

    titleLabel->setText(lang.get("topicsTitle"));
    mainMenuButton->setText(lang.get("mainMenuButton"));

    QString startText = lang.get("startButton");
    for (auto *btn : startButtons) {
        btn->setText(startText);
    }
}

