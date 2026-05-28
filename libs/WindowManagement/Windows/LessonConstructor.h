#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QTextEdit>
#include <QTextBrowser>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class LessonConstructor : public QWidget {
    Q_OBJECT

public:
    explicit LessonConstructor(QWidget *parent = nullptr);
    ~LessonConstructor() = default;

    void retranslateUI();

signals:
    void switchToMainMenu();

private slots:
    void onGenerateButtonClicked();
    void onSaveButtonClicked();
    void onNetworkReplyReceived(QNetworkReply *reply);
private:
    void setupUI();
    void setupConnections();
    QString loadApiKey();

    QPushButton *generateButton;
    QPushButton *saveButton;
    QPushButton *mainMenuButton;

    QLabel *contentLabel;
    QLabel *previewLabel;

    QTextEdit *contentInput;
    QTextBrowser *previewViewer;

    QNetworkAccessManager *networkManager;
};

