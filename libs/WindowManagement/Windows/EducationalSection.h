#pragma once

#include <QWidget>
#include <QPushButton>
#include <qtmetamacros.h>

class EducationalSection : public QWidget {
    Q_OBJECT

public:
    explicit EducationalSection(QWidget *parent = nullptr);

    void retranslateUI();

signals:
    void switchToMainMenu();

private slots:
    void onMainMenuButtonClicked();

private:
    QPushButton *mainMenuButton;
};

