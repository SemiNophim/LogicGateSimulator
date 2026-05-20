#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>

class TopicsPage : public QWidget {
    Q_OBJECT

public:
    explicit TopicsPage(QWidget *parent = nullptr);
    ~TopicsPage() = default;

    void retranslateUI();

signals:
    void switchToMainMenu();
    void lessonSelected(const QString &mdFilePath);

private:
    void setupUI();
    void setupConnections();

    QPushButton *mainMenuButton;
    QLabel *titleLabel;
    QList<QPushButton*> startButtons;
};

