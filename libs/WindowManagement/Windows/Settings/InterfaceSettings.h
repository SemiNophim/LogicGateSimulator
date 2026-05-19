#pragma once
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QFrame>

class InterfaceSettings : public QFrame {
    Q_OBJECT
public:
    explicit InterfaceSettings(const QString &baseStyle, QWidget *parent = nullptr);
    void retranslateUI();

signals:
    void backToSettingsMenu(); 
    void languageChanged(int index);

private slots:
    void onBackButtonClicked();
    void onLangChanged(int index);

private:
    QString m_baseStyle;
    QComboBox *langBox;
    QPushButton *backButton;
    QPushButton *changeLangButton;

    void setupUI();
    void setupConnections();
};

