#include "loginwindow.h"
#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QKeyEvent>
#include <QGraphicsDropShadowEffect>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Secure Login");
    resize(800, 500);
    setStyleSheet("background-color: #eaeef1;");

    // Left panel - Welcome side
    QWidget *welcomeWidget = new QWidget();
    welcomeWidget->setStyleSheet("background-color: #2e3a59; border-top-left-radius: 20px; border-bottom-left-radius: 20px;");

    QLabel *welcomeText = new QLabel("Welcome Back!");
    welcomeText->setStyleSheet("color: white; font-size: 32px; font-weight: bold;");
    welcomeText->setAlignment(Qt::AlignCenter);

    QLabel *descText = new QLabel("Login to continue to your dashboard.");
    descText->setStyleSheet("color: #ddd; font-size: 16px;");
    descText->setAlignment(Qt::AlignCenter);
    descText->setWordWrap(true);

    QVBoxLayout *welcomeLayout = new QVBoxLayout(welcomeWidget);
    welcomeLayout->setContentsMargins(20, 20, 20, 20);  // Fixed deprecated setMargin
    welcomeLayout->addStretch();
    welcomeLayout->addWidget(welcomeText);
    welcomeLayout->addSpacing(10);
    welcomeLayout->addWidget(descText);
    welcomeLayout->addStretch();

    // Right panel - Form side
    QLabel *userLabel = new QLabel("Username:");
    QLabel *passLabel = new QLabel("Password:");
    userLabel->setStyleSheet("font-size: 16px; color: #333;");
    passLabel->setStyleSheet("font-size: 16px; color: #333;");

    userInput = new QLineEdit();
    passInput = new QLineEdit();
    passInput->setEchoMode(QLineEdit::Password);
    userInput->setMinimumHeight(40);
    passInput->setMinimumHeight(40);
    userInput->setStyleSheet("border-radius: 10px; padding: 8px; font-size: 14px; background-color: #ffffff; border: 1px solid #ccc;");
    passInput->setStyleSheet("border-radius: 10px; padding: 8px; font-size: 14px; background-color: #ffffff; border: 1px solid #ccc;");

    userInput->setFocus();
    userInput->installEventFilter(this);
    passInput->installEventFilter(this);

    QPushButton *loginButton = new QPushButton("Login");
    loginButton->setFixedHeight(40);
    loginButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #2e3a59;"
        "  color: white;"
        "  font-size: 16px;"
        "  border-radius: 10px;"
        "}"
        "QPushButton:hover { background-color: #1d263e; }"
        );

    agreeCheckBox = new QCheckBox("I agree to the Terms and Conditions");
    agreeCheckBox->setStyleSheet("font-size: 13px; color: #555; padding-left: 5px;");
    connect(agreeCheckBox, &QCheckBox::toggled, this, &LoginWindow::onAgreementChanged);

    QLabel *termsLabel = new QLabel("Terms & Conditions:");
    termsLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #2e3a59;");
    QLabel *termPoints = new QLabel(
        "• Your activities may be monitored.\n"
        "• Unauthorized access is strictly prohibited.\n"
        "• Keep your credentials confidential.\n"
        "• Admin may revoke access at any time.\n"
        "• Respect the privacy and rights of others."
        );
    termPoints->setStyleSheet("font-size: 13px; color: #444;");
    termPoints->setWordWrap(true);

    QPushButton *quitButton = new QPushButton("Quit");
    quitButton->setFixedSize(80, 30);
    quitButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #ff4c4c;"
        "  color: white;"
        "  font-size: 14px;"
        "  border-radius: 5px;"
        "}"
        "QPushButton:hover { background-color: #cc0000; }"
        );
    connect(quitButton, &QPushButton::clicked, this, &QWidget::close);

    QVBoxLayout *formLayout = new QVBoxLayout();
    formLayout->setContentsMargins(30, 30, 30, 30);  // Fixed deprecated setMargin
    formLayout->addWidget(userLabel);
    formLayout->addWidget(userInput);
    formLayout->addWidget(passLabel);
    formLayout->addWidget(passInput);
    formLayout->addSpacing(10);
    formLayout->addWidget(loginButton);
    formLayout->addWidget(agreeCheckBox);
    formLayout->addSpacing(10);
    formLayout->addWidget(termsLabel);
    formLayout->addWidget(termPoints);
    formLayout->addSpacing(10);
    formLayout->addWidget(quitButton, 0, Qt::AlignRight);

    QWidget *formWidget = new QWidget();
    formWidget->setLayout(formLayout);
    formWidget->setStyleSheet("background-color: #f6f7fa; border-top-right-radius: 20px; border-bottom-right-radius: 20px;");

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);  // Fixed deprecated setMargin
    mainLayout->addWidget(welcomeWidget, 2);
    mainLayout->addWidget(formWidget, 3);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
}

bool LoginWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            if (obj == userInput) {
                passInput->setFocus();
                return true;
            } else if (obj == passInput) {
                handleLogin();
                return true;
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void LoginWindow::handleLogin() {
    if (!agreeCheckBox->isChecked()) {
        QMessageBox::warning(this, "Terms Required", "You must agree to the Terms and Conditions to login.");
        return;
    }

    QString username = userInput->text();
    QString password = passInput->text();

    if (username == "admin" && password == "1234") {
        MainWindow *mainWin = new MainWindow();
        mainWin->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Invalid username or password!");
        userInput->clear();
        passInput->clear();
        userInput->setFocus();
    }
}

void LoginWindow::onAgreementChanged(bool checked) {
    agreeCheckBox->setStyleSheet(
        QString("font-size: 13px; color: %1; padding-left: 5px;")
            .arg(checked ? "#2e3a59" : "#555")
        );
}
