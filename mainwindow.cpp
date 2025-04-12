#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Make window full screen
    this->showFullScreen();

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Set white background
    central->setStyleSheet("background-color: snow ;");

    // === Top-center Search Bar ===
    QLineEdit *searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Search for products...");
    searchBar->setFixedHeight(50);
    searchBar->setStyleSheet("font-size: 20px; padding: 10px; border: 1px solid #ccc; border-radius: 8px;");

    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addStretch();
    searchLayout->addWidget(searchBar);
    searchLayout->addStretch();

    // === Bottom-left Buttons ===
    QPushButton *homeBottomButton = new QPushButton("Home");
    QPushButton *cartButton = new QPushButton("Cart");
    QPushButton *shippingButton = new QPushButton("Shipping");

    QList<QPushButton*> buttons = {homeBottomButton, cartButton, shippingButton};
    for (QPushButton *btn : buttons) {
        btn->setFixedSize(150, 50);
        btn->setStyleSheet("font-size: 18px; background-color: #2d89ef; color: white; border-radius: 8px;");
    }

    QHBoxLayout *bottomLeftLayout = new QHBoxLayout();
    bottomLeftLayout->addWidget(homeBottomButton);
    bottomLeftLayout->addWidget(cartButton);
    bottomLeftLayout->addWidget(shippingButton);
    bottomLeftLayout->setSpacing(20);
    bottomLeftLayout->setAlignment(Qt::AlignLeft);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addLayout(bottomLeftLayout);
    bottomLayout->addStretch();

    // === Main Layout ===
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addLayout(searchLayout);
    mainLayout->addStretch(); // Placeholder for central content
    mainLayout->addLayout(bottomLayout);
}
