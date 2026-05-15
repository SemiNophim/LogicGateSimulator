#pragma once
#include <QWidget>
#include <QPushButton>


class MainMenu : public QWidget {
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);

    void retranslateUI();

signals:
    void switchToEducationalSection();
    void switchToConstructor();
    void switchToSettings();

private slots:
    void onEducationalSectionButtonClicked();
    void onConstructorButtonClicked();
    void onSettingsButtonClicked();

private:
    QPushButton *educationalSectionButton;
    QPushButton *constructorButton;
    QPushButton *settingsButton;

    void setupUI();
    void setupConnections();
};

