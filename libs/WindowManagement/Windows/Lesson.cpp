#include "Lesson.h"
#include "LanguageManager/LangManager.h"
#include <QFile>
#include <QTextStream>

Lesson::Lesson(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}

void Lesson::setupUI() {
    auto *mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto *centralFrame = new QFrame(this);
    centralFrame->setFixedWidth(800);
    centralFrame->setMinimumHeight(550);
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

    auto *topBar = new QWidget(centralFrame);
    topBar->setObjectName("topBar");
    topBar->setFixedHeight(50);
    topBar->setStyleSheet(
        "QWidget#topBar {"
        "  background-color: #2E3440;"
        "  border-top-left-radius: 8px;"
        "  border-top-right-radius: 8px;"
        "}"
    );
    auto *topBarLayout = new QHBoxLayout(topBar);
    topBarLayout->setContentsMargins(20, 0, 20, 0);

    backButton = new QPushButton(topBar);
    backButton->setFixedWidth(90);
    backButton->setStyleSheet(
        "QPushButton {"
        "  font-family: 'Segoe UI', Arial, sans-serif;"
        "  background-color: #4C566A;"
        "  color: #ffffff;"
        "  font-size: 13px;"
        "  font-weight: bold;"
        "  padding: 6px;"
        "  border-radius: 4px;"
        "  border: none;"
        "}"
        "QPushButton:hover {"
        "  background-color: #5E81AC;"
        "}"
    );

    lessonTitleLabel = new QLabel(topBar);
    lessonTitleLabel->setStyleSheet(
        "QLabel {"
        "  color: #FFFFFF;"
        "  font-family: 'Segoe UI';"
        "  font-size: 16px;"
        "  font-weight: bold;"
        "}"
    );

    markdownViewer = new QTextBrowser(centralFrame);
    markdownViewer->setOpenExternalLinks(true);
    markdownViewer->setStyleSheet(
        "QTextBrowser {"
        "  background-color: #3B4252;"
        "  color: #FFFFFF;"
        "  border: none;"
        "  font-family: 'Segoe UI', Arial, sans-serif;"
        "  font-size: 15px;"
        "  padding: 25px 30px;"
        "}"
        "QScrollBar:vertical {"
        "  border: none;"
        "  background: #3B4252;"
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

    topBarLayout->addWidget(backButton);
    topBarLayout->addSpacing(20);
    topBarLayout->addStretch(1);
    topBarLayout->addWidget(lessonTitleLabel);
    topBarLayout->addStretch(1);

    frameLayout->addWidget(topBar);
    frameLayout->addWidget(markdownViewer, 1); 

    mainLayout->addWidget(centralFrame, 2, 2);
    mainLayout->setRowStretch(1, 1);
    mainLayout->setRowStretch(3, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(3, 1);
}

void Lesson::setupConnections() {
    connect(backButton, &QPushButton::clicked, this, &Lesson::goBackToTopics);
}

void Lesson::loadLessonMarkdown(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        markdownViewer->setHtml("<p style='color: #BF616A; font-weight: bold;'>Помилка: не вдалося завантажити файл уроку.</p>");
        return;
    }

    QTextStream in(&file);
    QString markdownContent = in.readAll();
    file.close();

    markdownViewer->setMarkdown(markdownContent);
    markdownViewer->moveCursor(QTextCursor::Start);
}

void Lesson::retranslateUI() {
    auto &lang = LangManager::instance();

    backButton->setText(lang.get("backButton"));
    lessonTitleLabel->setText(lang.get("topicsTitle"));
}

