#pragma once

#include <QWidget>
#include <QPushButton>
#include <QComboBox>

class Settings : public QWidget {
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);

    void retranslateUI();

signals:
    void switchToMainMenu();
    void switchLang(int langIndex);

private slots:
    void onMainMenuButtonClicked();
    void onChangeLangButtonClicked();

private:
    QPushButton *mainMenuButton;
    QPushButton *changeLangButton;
    QComboBox *langBox;
};

