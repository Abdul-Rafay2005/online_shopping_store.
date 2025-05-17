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
#include <QFormLayout>
#include <QMap>
#include <QToolButton>
#include <QPair>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QGraphicsDropShadowEffect>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showHomePage();
    void showShippingPage();
    void showCartPage();
    void placeOrder();
    void showCategoryPage(const QString &category);
    void addToCart();
    void viewOrders();

private:
    void createHomePage();
    void createCategoryPage(const QString &name);
    void createShippingPage();
    void createCartPage();
    void updateCartPage();
    void saveOrder(const QString &customerName, const QString &address, const QString &phone,
                   const QList<QPair<QString, double>> &items, double total);

    // Core layout
    QStackedWidget *stackedWidget;
    QMap<QString, QWidget*> categoryPages;

    // Pages
    QWidget *shippingPage;
    QWidget *cartPage;

    // Shipping form inputs
    QLineEdit *nameInput;
    QLineEdit *addressInput;
    QLineEdit *phoneInput;
    QPushButton *orderButton;

    // Cart functionality
    QVBoxLayout *cartItemsLayout;
    QList<QPair<QString, double>> cartItems;
    double cartTotal;
    QLabel *cartTotalLabel;

    // Top navigation UI
    QLineEdit *searchBar;
    QPushButton *homeButton;
    QPushButton *shippingButton;
    QPushButton *cartButton;
    QPushButton *viewCartButton;
    QPushButton *checkoutButton;
    QPushButton *ordersButton;

    // Window controls
    QToolButton *minimizeButton;
    QToolButton *maximizeButton;
    QToolButton *closeButton;
};

#endif // MAINWINDOW_H
