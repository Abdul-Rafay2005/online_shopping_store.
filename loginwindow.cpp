#include "loginwindow.h"
#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QKeyEvent>
#include <QCheckBox>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Login");
    showFullScreen();
    setStyleSheet("background-color: #f0f0f0;");

    QLabel *titleLabel = new QLabel("HAPPY SHOPPING");
    titleLabel->setStyleSheet("color: #333; font-size: 36px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);

    QLabel *userLabel = new QLabel("Username:");
    QLabel *passLabel = new QLabel("Password:");
    userLabel->setStyleSheet("color: #333; font-size: 18px;");
    passLabel->setStyleSheet("color: #333; font-size: 18px;");

    userInput = new QLineEdit();
    passInput = new QLineEdit();
    passInput->setEchoMode(QLineEdit::Password);
    userInput->setMinimumHeight(40);
    passInput->setMinimumHeight(40);
    userInput->setStyleSheet("color: black; background: white; font-size: 16px; border-radius: 5px; padding: 5px; border: 1px solid #ccc;");
    passInput->setStyleSheet("color: black; background: white; font-size: 16px; border-radius: 5px; padding: 5px; border: 1px solid #ccc;");

    userInput->setFocus();
    userInput->installEventFilter(this);
    passInput->installEventFilter(this);

    QPushButton *loginButton = new QPushButton("Login");
    loginButton->setFixedSize(120, 40);
    loginButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #2d89ef;"
        "  color: white;"
        "  font-size: 16px;"
        "  border-radius: 5px;"
        "}"
        "QPushButton:hover { background-color: #1e5dbf; }"
        );

    QLabel *termsLabel = new QLabel("Terms & Conditions:");
    termsLabel->setStyleSheet("font-weight: bold; font-size: 16px; color: #222;");

    QLabel *termPoints = new QLabel(
        "• All user activities are monitored.\n"
        "• No unauthorized access allowed.\n"
        "• Admin reserves the right to revoke access.\n"
        "• Login information must be kept secure."
        );
    termPoints->setStyleSheet("font-size: 14px; color: #444;");
    termPoints->setWordWrap(true);

    agreeCheckBox = new QCheckBox("I agree to the Terms and Conditions");
    agreeCheckBox->setStyleSheet(
        "QCheckBox {"
        "  font-size: 14px;"
        "  color: #222;"
        "  border: 1px solid black;"
        "  padding: 5px;"
        "}"
        );
    connect(agreeCheckBox, &QCheckBox::toggled, this, &LoginWindow::onAgreementChanged);

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
    formLayout->addWidget(userLabel);
    formLayout->addWidget(userInput);
    formLayout->addWidget(passLabel);
    formLayout->addWidget(passInput);
    formLayout->addWidget(loginButton, 0, Qt::AlignHCenter);
    formLayout->addSpacing(20);
    formLayout->addWidget(termsLabel);
    formLayout->addWidget(termPoints);
    formLayout->addWidget(agreeCheckBox);
    formLayout->setSpacing(15);

    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->addWidget(titleLabel);
    centerLayout->addSpacing(30);
    centerLayout->addLayout(formLayout);
    centerLayout->setAlignment(Qt::AlignCenter);

    QLabel *namesLabel = new QLabel("Developed by: Abdul Rafay, Syed Nabeel, Adnan Anwar");
    namesLabel->setStyleSheet("color: #555; font-size: 14px;");
    namesLabel->setAlignment(Qt::AlignLeft);

    QHBoxLayout *namesLayout = new QHBoxLayout();
    namesLayout->addWidget(namesLabel);
    namesLayout->addStretch();

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addStretch();
    bottomLayout->addWidget(quitButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(centerLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(namesLayout);
    mainLayout->addLayout(bottomLayout);

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
        QMessageBox msgBox;
        msgBox.setWindowTitle("Terms Required");
        msgBox.setText("You must agree to the Terms and Conditions to login.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet("QLabel { color: white; } QMessageBox { background-color: black; } QPushButton { min-width: 80px; }");
        msgBox.exec();
        return;
    }

    QString username = userInput->text();
    QString password = passInput->text();

    if (username == "admin" && password == "1234") {
        MainWindow *mainWin = new MainWindow();
        mainWin->show();
        this->close();
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Invalid username or password!");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet("QLabel { color: white; } QMessageBox { background-color: black; } QPushButton { min-width: 80px; }");
        msgBox.exec();

        userInput->clear();
        passInput->clear();
        userInput->setFocus();
    }
}

void LoginWindow::onAgreementChanged(bool checked) {
    if (checked) {
        agreeCheckBox->setStyleSheet(
            "QCheckBox {"
            "  font-size: 14px;"
            "  color: #222;"
            "  border: 1px solid #2d89ef;"
            "  padding: 5px;"
            "}"
            );
    } else {
        agreeCheckBox->setStyleSheet(
            "QCheckBox {"
            "  font-size: 14px;"
            "  color: #222;"
            "  border: 1px solid black;"
            "  padding: 5px;"
            "}"
            );
    }
}
