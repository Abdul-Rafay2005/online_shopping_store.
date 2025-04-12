#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QMenuBar>
#include <QToolButton>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Make window full screen
    this->showFullScreen();

    // Remove default menu bar
    setMenuBar(nullptr);

    // Create central widget
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    central->setStyleSheet("background-color: snow;");

    // === Window Controls (Top-Right) ===
    QWidget *windowControls = new QWidget();
    QHBoxLayout *controlsLayout = new QHBoxLayout(windowControls);
    controlsLayout->setContentsMargins(0, 0, 0, 0);
    controlsLayout->setSpacing(0);

    // Minimize button
    QToolButton *minimizeButton = new QToolButton();
    minimizeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
    minimizeButton->setFixedSize(30, 30);
    minimizeButton->setStyleSheet("QToolButton { border: none; background: transparent; }"
                                  "QToolButton:hover { background-color: #e0e0e0; }");
    connect(minimizeButton, &QToolButton::clicked, this, &QMainWindow::showMinimized);

    // Maximize/Restore button
    QToolButton *maximizeButton = new QToolButton();
    maximizeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    maximizeButton->setFixedSize(30, 30);
    maximizeButton->setStyleSheet("QToolButton { border: none; background: transparent; }"
                                  "QToolButton:hover { background-color: #e0e0e0; }");
    connect(maximizeButton, &QToolButton::clicked, [this]() {
        if (isMaximized()) {
            showNormal();
        } else {
            showMaximized();
        }
    });

    // Close button
    QToolButton *closeButton = new QToolButton();
    closeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    closeButton->setFixedSize(30, 30);
    closeButton->setStyleSheet("QToolButton { border: none; background: transparent; }"
                               "QToolButton:hover { background-color: #ff4c4c; color: white; }");
    connect(closeButton, &QToolButton::clicked, this, &QMainWindow::close);

    controlsLayout->addWidget(minimizeButton);
    controlsLayout->addWidget(maximizeButton);
    controlsLayout->addWidget(closeButton);

    // === Search Bar (Visible Box with White Text) ===
    QLineEdit *searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Search for products...");
    searchBar->setFixedHeight(50);
    searchBar->setStyleSheet(
        "QLineEdit {"
        "  font-size: 20px;"
        "  padding: 10px;"
        "  border: 2px solid #2d89ef;"  // Blue border
        "  border-radius: 8px;"
        "  background-color: white;"    // White background
        "  color: black;"               // Black placeholder text
        "}"
        "QLineEdit:focus {"
        "  border: 2px solid #1e5dbf;" // Darker blue when focused
        "}"
        "QLineEdit QAbstractItemView {" // Style for dropdown suggestions
        "  background: white;"
        "  color: black;"
        "}"
        );

    // === Top Bar Layout (Search + Window Controls) ===
    QHBoxLayout *topBarLayout = new QHBoxLayout();
    topBarLayout->addWidget(searchBar, 1); // Takes remaining space
    topBarLayout->addWidget(windowControls);

    // === Bottom Buttons ===
    QPushButton *homeButton = new QPushButton("Home");
    QPushButton *shippingButton = new QPushButton("Shipping");
    QPushButton *cartButton = new QPushButton("Cart");

    // Style all buttons consistently
    QList<QPushButton*> buttons = {homeButton, shippingButton, cartButton};
    for (QPushButton *btn : buttons) {
        btn->setFixedSize(150, 50);
        btn->setStyleSheet(
            "QPushButton {"
            "  font-size: 18px;"
            "  background-color: #2d89ef;"
            "  color: white;"
            "  border-radius: 8px;"
            "}"
            "QPushButton:hover { background-color: #1e5dbf; }"
            );
    }

    // Bottom layout with specific button positions
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(homeButton);               // Home on far left
    bottomLayout->addStretch();                       // Space between
    bottomLayout->addWidget(shippingButton);          // Shipping in middle
    bottomLayout->addStretch();                       // Space between
    bottomLayout->addWidget(cartButton);              // Cart on far right (replaces quit)

    // === Main Layout ===
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addLayout(topBarLayout);
    mainLayout->addStretch(); // Placeholder for central content
    mainLayout->addLayout(bottomLayout);
}
