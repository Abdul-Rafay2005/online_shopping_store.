#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void showHomePage();
    void showShippingPage();
    void showCartPage();
    void placeOrder();

private:
    void createCategoryPage(const QString &name);
    void showCategoryPage(const QString &name);
    QMap<QString, QWidget*> categoryPages;


private:
    // UI elements
    QLineEdit *searchBar;
    QPushButton *homeButton;
    QPushButton *shippingButton;
    QPushButton *cartButton;
    QPushButton *viewCartButton;
    QPushButton *checkoutButton;

    // NEW: Shipping input fields
    QLineEdit *nameInput;
    QLineEdit *addressInput;
    QLineEdit *phoneInput;
    QPushButton *orderButton;

    // Page navigation
    QStackedWidget *stackedWidget;
    void createHomePage();
    void createShippingPage();
    void createCartPage();

    // Window controls
    void createWindowControls(QWidget *parent);
};

#endif // MAINWINDOW_H
