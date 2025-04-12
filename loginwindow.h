#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void handleLogin();

private:
    QLineEdit *userInput;
    QLineEdit *passInput;
};

#endif // LOGINWINDOW_H
