#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QTextBrowser>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

class LessonConstructor : public QWidget {
    Q_OBJECT

public:
    explicit LessonConstructor(QWidget *parent = nullptr);
    ~LessonConstructor() = default;

    void retranslateUI();

signals:
    void switchToMainMenu();

private:
    void setupUI();
    void setupConnections();

    QPushButton *generateButton;
    QPushButton *saveButton;
    QPushButton *mainMenuButton;

    QLabel *contentLabel;
    QLabel *previewLabel;

    QTextEdit *contentInput;
    QTextBrowser *previewViewer;
};
