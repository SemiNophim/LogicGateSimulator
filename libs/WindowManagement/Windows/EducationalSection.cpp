#include "EducationalSection.h"
#include <QStackedWidget>
#include <QGridLayout>


#include "Lesson.h"     
#include "TopicsPage.h"

EducationalSection::EducationalSection(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}

void EducationalSection::setupUI() {
    auto *mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0); 

    auto *backgroundWidget = new QWidget(this);
    backgroundWidget->setStyleSheet("background-color: #4A5062;");
    mainLayout->addWidget(backgroundWidget, 1, 1); 

    stackedWidget = new QStackedWidget(this);
    stackedWidget->setStyleSheet("background: transparent;");

    topicsPage = new TopicsPage(stackedWidget);
    lessonPage = new Lesson(stackedWidget);

    stackedWidget->addWidget(topicsPage); 
    stackedWidget->addWidget(lessonPage);  

    mainLayout->addWidget(stackedWidget, 1, 1);
}

void EducationalSection::setupConnections() {
    connect(topicsPage, &TopicsPage::switchToMainMenu, this, &EducationalSection::switchToMainMenu);

    connect(topicsPage, &TopicsPage::lessonSelected, [this](const QString &mdFilePath) {
        lessonPage->loadLessonMarkdown(mdFilePath);
        stackedWidget->setCurrentWidget(lessonPage); 
    });

    connect(lessonPage, &Lesson::goBackToTopics, [this]() {
        stackedWidget->setCurrentWidget(topicsPage); 
    });
}

void EducationalSection::retranslateUI() {
    topicsPage->retranslateUI();
    lessonPage->retranslateUI();
}

