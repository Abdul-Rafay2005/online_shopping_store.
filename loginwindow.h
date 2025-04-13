#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void handleLogin();
    void onAgreementChanged(bool checked);

private:
    QLineEdit *userInput;
    QLineEdit *passInput;
    QCheckBox *agreeCheckBox;

};

#endif // LOGINWINDOW_H
