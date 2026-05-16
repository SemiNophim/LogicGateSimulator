#pragma once
#include <QWidget>
#include <QPushButton>

class LessonConstructor : public QWidget {
    Q_OBJECT

public:
    explicit LessonConstructor(QWidget *parent = nullptr);

    void retranslateUI();

signals:
    void switchToMainMenu();

private slots:
    void onMainMenuButtonClicked();

private:
    QPushButton *mainMenuButton;

    void setupUI();
    void setupConnections();
};

