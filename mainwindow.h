#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>      // Add this for QLineEdit
#include <QPushButton>    // Add this for QPushButton
#include <QLabel>         // Add this for QLabel
#include <QScrollArea>    // Add this for QScrollArea
#include <QHBoxLayout>    // Add this for QHBoxLayout
#include <QVBoxLayout>    // Add this for QVBoxLayout

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void showHomePage();
    void showShippingPage();
    void showCartPage();

private:
    // UI elements
    QLineEdit *searchBar;
    QPushButton *homeButton;
    QPushButton *shippingButton;
    QPushButton *cartButton;
    QPushButton *viewCartButton;
    QPushButton *checkoutButton;

    // Page navigation
    QStackedWidget *stackedWidget;
    void createHomePage();
    void createShippingPage();
    void createCartPage();

    // Window controls
    void createWindowControls(QWidget *parent);
};

#endif // MAINWINDOW_H
