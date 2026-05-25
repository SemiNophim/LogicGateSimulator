#include "LessonConstructor.h"
#include "LanguageManager/LangManager.h"

LessonConstructor::LessonConstructor(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}

void LessonConstructor::setupUI() {
    auto *mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto *backgroundWidget = new QWidget(this);
    backgroundWidget->setStyleSheet(
        "QWidget {"
        "  background-color: #4A5062;"
        "}"
    );
    mainLayout->addWidget(backgroundWidget, 1, 1);

    auto *overlayWidget = new QWidget(this);
    auto *centerLayout = new QHBoxLayout(overlayWidget);
    centerLayout->setContentsMargins(50, 0, 50, 0);
    centerLayout->setSpacing(40);

    auto *leftContainer = new QWidget(overlayWidget);
    leftContainer->setFixedWidth(500);
    leftContainer->setFixedHeight(500);

    auto *leftVLayout = new QVBoxLayout(leftContainer);
    leftVLayout->setContentsMargins(0, 0, 0, 0);
    leftVLayout->setSpacing(0);

    auto *leftFrame = new QFrame(leftContainer);
    leftFrame->setObjectName("leftFrame");
    leftFrame->setStyleSheet(
        "QFrame#leftFrame {"
        "  background-color: #3B4252;"
        "  border-top-left-radius: 8px;"
        "  border-top-right-radius: 8px;"
        "  border: none;"
        "}"
    );

    auto *leftFrameLayout = new QVBoxLayout(leftFrame);
    leftFrameLayout->setContentsMargins(20, 15, 20, 20);
    leftFrameLayout->setSpacing(10);

    contentLabel = new QLabel(leftFrame);
    contentLabel->setAlignment(Qt::AlignCenter);
    contentLabel->setStyleSheet(
        "QLabel {"
        "  color: #FFFFFF;"
        "  font-family: 'Segoe UI';"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  background: transparent;"
        "}"
    );

    contentInput = new QTextEdit(leftFrame);
    contentInput->setStyleSheet(
        "QTextEdit {"
        "  background-color: #FFFFFF;"
        "  color: #2E3440;"
        "  border: none;"
        "  border-radius: 4px;"
        "  font-family: 'Segoe UI';"
        "  font-size: 14px;"
        "  padding: 10px;"
        "}"
    );

    auto *bottomBar = new QWidget(leftContainer);
    bottomBar->setFixedHeight(55);
    bottomBar->setStyleSheet(
        "QWidget {"
        "  background-color: #2E3440;"
        "}"
    );

    auto *buttonsLayout = new QHBoxLayout(bottomBar);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(0);

    generateButton = new QPushButton(bottomBar);
    generateButton->setFixedHeight(55);
    generateButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #434C5E;"
        "  color: #FFFFFF;"
        "  font-family: 'Segoe UI';"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  border: none;"
        "}"
        "QPushButton:hover {"
        "  background-color: #4C566A;"
        "}"
    );

    saveButton = new QPushButton(bottomBar);
    saveButton->setFixedHeight(55);
    saveButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #4C566A;"
        "  color: #FFFFFF;"
        "  font-family: 'Segoe UI';"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  border-left: 1px solid #2E3440;"
        "  border-right: 1px solid #2E3440;"
        "  border-top: none;"
        "  border-bottom: none;"
        "}"
        "QPushButton:hover {"
        "  background-color: #5E81AC;"
        "}"
    );

    mainMenuButton = new QPushButton(bottomBar);
    mainMenuButton->setFixedHeight(55);
    mainMenuButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #BF616A;"
        "  color: #FFFFFF;"
        "  font-family: 'Segoe UI';"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  border: none;"
        "}"
        "QPushButton:hover {"
        "  background-color: #D08770;"
        "}"
    );

    auto *rightFrame = new QFrame(overlayWidget);
    rightFrame->setFixedWidth(500);
    rightFrame->setFixedHeight(500);
    rightFrame->setObjectName("rightFrame");
    rightFrame->setStyleSheet(
        "QFrame#rightFrame {"
        "  background-color: #3B4252;"
        "  border-radius: 8px;"
        "  border: none;"
        "}"
    );

    auto *rightFrameLayout = new QVBoxLayout(rightFrame);
    rightFrameLayout->setContentsMargins(20, 15, 20, 20);
    rightFrameLayout->setSpacing(10);

    previewLabel = new QLabel(rightFrame);
    previewLabel->setAlignment(Qt::AlignCenter);
    previewLabel->setStyleSheet(
        "QLabel {"
        "  color: #FFFFFF;"
        "  font-family: 'Segoe UI';"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  background: transparent;"
        "}"
    );

    previewViewer = new QTextBrowser(rightFrame);
    previewViewer->setStyleSheet(
        "QTextBrowser {"
        "  background-color: #2E3440;"
        "  color: #FFFFFF;"
        "  border: none;"
        "  border-radius: 4px;"
        "  font-family: 'Segoe UI';"
        "  font-size: 14px;"
        "  padding: 15px;"
        "}"
        "QScrollBar:vertical {"
        "  border: none;"
        "  background: #2E3440;"
        "  width: 8px;"
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
        "  background: none;"
        "  border: none;"
        "}"
    );

    retranslateUI();

    leftFrameLayout->addWidget(contentLabel);
    leftFrameLayout->addWidget(contentInput);
    leftVLayout->addWidget(leftFrame, 1);

    buttonsLayout->addWidget(generateButton, 1);
    buttonsLayout->addWidget(saveButton, 1);
    buttonsLayout->addWidget(mainMenuButton, 1);
    leftVLayout->addWidget(bottomBar);

    rightFrameLayout->addWidget(previewLabel);
    rightFrameLayout->addWidget(previewViewer);

    centerLayout->addStretch(1);
    centerLayout->addWidget(leftContainer);
    centerLayout->addWidget(rightFrame);
    centerLayout->addStretch(1);

    mainLayout->addWidget(overlayWidget, 1, 1);
}

void LessonConstructor::setupConnections() {
    connect(mainMenuButton, &QPushButton::clicked, 
            this, &LessonConstructor::switchToMainMenu);
}

void LessonConstructor::retranslateUI() {
    auto &lang = LangManager::instance();

    contentLabel->setText(lang.get("constructorContentLabel"));
    previewLabel->setText(lang.get("constructorPreviewLabel"));
    
    generateButton->setText(lang.get("generateButton"));
    saveButton->setText(lang.get("saveLessonButton"));
    mainMenuButton->setText(lang.get("backButton"));
}
