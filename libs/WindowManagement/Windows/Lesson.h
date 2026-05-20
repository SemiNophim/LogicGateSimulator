#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>

class Lesson : public QWidget {
    Q_OBJECT

public:
    explicit Lesson(QWidget *parent = nullptr);
    ~Lesson() = default;

    void retranslateUI();
    
    void loadLessonMarkdown(const QString &filePath);

signals:
    void goBackToTopics();   

private:
    void setupUI();
    void setupConnections();

    QPushButton *backButton;
    QLabel *lessonTitleLabel;
    QTextBrowser *markdownViewer;
};

