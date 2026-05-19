#pragma once

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QStackedWidget>
#include <QFrame>

#include "Settings/InterfaceSettings.h"

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
    void onChangeLangButtonClicked(int index);

private:
    QPushButton *mainMenuButton;
    QPushButton *interfaceButton;
    QPushButton *constructorButton;
    QPushButton *controlsButton;
    QComboBox *langBox;

    InterfaceSettings *interfaceSettingsPage;
    QStackedWidget *stackedWidget;
    QFrame *mainSettingsPanel;

    void setupUI();
    void setupConnections();
    void applyLanguage();
};

