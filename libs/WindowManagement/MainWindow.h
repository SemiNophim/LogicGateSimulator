#pragma once
#include <QStackedWidget>
#include <QWidget>

#include "Windows/MainMenu.h"
#include "Windows/EducationalSection.h"
#include "Windows/Settings.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *m_stackedWidget;
    MainMenu *m_mainMenu;
    EducationalSection *m_eduPage;
    Settings *m_setPage;

    void applyLanguage();
};

