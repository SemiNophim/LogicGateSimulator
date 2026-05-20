#pragma once

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>

#include "Lesson.h"
#include "TopicsPage.h"

class EducationalSection : public QWidget {
    Q_OBJECT

public:
    explicit EducationalSection(QWidget *parent = nullptr);

    void retranslateUI();

signals:
    void switchToMainMenu();

private:
    QStackedWidget *stackedWidget;
    TopicsPage *topicsPage;
    Lesson *lessonPage;

    void setupUI();
    void setupConnections();
};

