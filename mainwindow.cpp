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
#include <QScrollArea>
#include <QFormLayout>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->showFullScreen();
    setMenuBar(nullptr);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    createHomePage();
    createShippingPage();
    createCartPage();

    createCategoryPage("Mobiles");
    createCategoryPage("Laptops");
    createCategoryPage("TVs");
    createCategoryPage("Smart Watches");
    createCategoryPage("Earpods");
    createCategoryPage("Other Accessories");

    showHomePage();
}

void MainWindow::createHomePage() {
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *homePage = new QWidget();
    homePage->setStyleSheet("background-color: #f0f0f0;");
    scrollArea->setWidget(homePage);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QVBoxLayout *mainLayout = new QVBoxLayout(homePage);

    QWidget *topBar = new QWidget();
    QHBoxLayout *topBarLayout = new QHBoxLayout(topBar);
    topBarLayout->setContentsMargins(10, 10, 10, 10);
    topBarLayout->setSpacing(10);

    QPushButton *categoriesButton = new QPushButton("Categories");
    QMenu *categoriesMenu = new QMenu(categoriesButton);

    QStringList categoryList = {"Mobiles", "Laptops", "TVs", "Smart Watches", "Earpods", "Other Accessories"};
    for (const QString &cat : categoryList) {
        QAction *action = new QAction(cat, categoriesMenu);
        connect(action, &QAction::triggered, this, [=]() {
            showCategoryPage(cat);
        });
        categoriesMenu->addAction(action);
    }

    categoriesButton->setMenu(categoriesMenu);
    categoriesButton->setStyleSheet(
        "QPushButton { font-size: 18px; background-color: #000000; color: white; border: 2px solid #2d89ef;"
        "border-radius: 6px; padding: 10px 20px 10px 10px; text-align: left; }"
        "QPushButton::menu-indicator { subcontrol-position: right center; padding-right: 10px; }"
        "QPushButton:hover { background-color: #444444; }");

    categoriesMenu->setStyleSheet(
        "QMenu { background-color: #000000; color: white; border: 1px solid #2d89ef; }"
        "QMenu::item { padding: 10px; background-color: transparent; }"
        "QMenu::item:selected { background-color: #444444; }");

    searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Search for products...");
    searchBar->setFixedHeight(50);
    searchBar->setStyleSheet(
        "QLineEdit { font-size: 20px; padding: 10px; border: 2px solid #2d89ef; border-radius: 8px;"
        "background-color: white; color: black; }"
        "QLineEdit:focus { border: 2px solid #1e5dbf; }");

    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    shippingButton = new QPushButton("Shipping");
    cartButton = new QPushButton("Cart");

    QList<QPushButton*> topButtons = {shippingButton, cartButton};
    for (QPushButton *btn : topButtons) {
        btn->setFixedSize(120, 40);
        btn->setStyleSheet(
            "QPushButton { font-size: 16px; background-color: #2d89ef; color: white; border-radius: 8px; }"
            "QPushButton:hover { background-color: #1e5dbf; }");
    }

    connect(shippingButton, &QPushButton::clicked, this, &MainWindow::showShippingPage);
    connect(cartButton, &QPushButton::clicked, this, &MainWindow::showCartPage);

    QWidget *windowControls = new QWidget();
    QHBoxLayout *controlsLayout = new QHBoxLayout(windowControls);
    controlsLayout->setContentsMargins(0, 0, 0, 0);
    controlsLayout->setSpacing(0);

    QToolButton *minimizeButton = new QToolButton();
    minimizeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
    minimizeButton->setFixedSize(30, 30);
    minimizeButton->setStyleSheet("QToolButton { border: none; background: transparent; }"
                                  "QToolButton:hover { background-color: #e0e0e0; }");
    connect(minimizeButton, &QToolButton::clicked, this, &QMainWindow::showMinimized);

    QToolButton *maximizeButton = new QToolButton();
    maximizeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    maximizeButton->setFixedSize(30, 30);
    maximizeButton->setStyleSheet("QToolButton { border: none; background: transparent; }"
                                  "QToolButton:hover { background-color: #e0e0e0; }");
    connect(maximizeButton, &QToolButton::clicked, [this]() {
        isMaximized() ? showNormal() : showMaximized();
    });

    QToolButton *closeButton = new QToolButton();
    closeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    closeButton->setFixedSize(30, 30);
    closeButton->setStyleSheet("QToolButton { border: none; background: transparent; }"
                               "QToolButton:hover { background-color: #ff4c4c; color: white; }");
    connect(closeButton, &QToolButton::clicked, this, &QMainWindow::close);

    controlsLayout->addWidget(minimizeButton);
    controlsLayout->addWidget(maximizeButton);
    controlsLayout->addWidget(closeButton);

    topBarLayout->addWidget(categoriesButton);
    topBarLayout->addWidget(searchBar, 1);
    topBarLayout->addWidget(spacer);
    topBarLayout->addWidget(shippingButton);
    topBarLayout->addWidget(cartButton);
    topBarLayout->addWidget(windowControls);

    QLabel *homeContent = new QLabel("HOME PAGE CONTENT");
    homeContent->setAlignment(Qt::AlignCenter);
    homeContent->setStyleSheet("font-size: 36px;");
    homeContent->setMinimumHeight(1200);

    mainLayout->addWidget(topBar);
    mainLayout->addWidget(homeContent);

    stackedWidget->addWidget(scrollArea);
}

void MainWindow::createShippingPage() {
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *shippingPage = new QWidget();
    shippingPage->setStyleSheet("background-color: #f0f0f0;");
    scrollArea->setWidget(shippingPage);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout *layout = new QVBoxLayout(shippingPage);

    QToolButton *backButton = new QToolButton();
    backButton->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));
    backButton->setToolTip("Back to Home");
    backButton->setIconSize(QSize(30, 30));
    backButton->setStyleSheet("QToolButton { background: transparent; border: none; margin: 10px; }"
                              "QToolButton:hover { background-color: #dddddd; border-radius: 6px; }");
    connect(backButton, &QToolButton::clicked, this, &MainWindow::showHomePage);

    layout->addWidget(backButton, 0, Qt::AlignLeft);

    QLabel *shippingLabel = new QLabel("SHIPPING DETAILS");
    shippingLabel->setAlignment(Qt::AlignCenter);
    shippingLabel->setStyleSheet("font-size: 32px; margin: 20px; color: black;");
    layout->addWidget(shippingLabel);

    QFormLayout *formLayout = new QFormLayout();

    nameInput = new QLineEdit();
    addressInput = new QLineEdit();
    phoneInput = new QLineEdit();

    nameInput->setPlaceholderText("Enter your full name");
    addressInput->setPlaceholderText("Enter your shipping address");
    phoneInput->setPlaceholderText("Enter your phone number");

    QList<QLineEdit*> inputs = {nameInput, addressInput, phoneInput};
    for (QLineEdit *input : inputs) {
        input->setStyleSheet("QLineEdit { font-size: 18px; padding: 8px; border: 2px solid #ccc;"
                             "border-radius: 6px; background-color: white; color: black; }"
                             "QLineEdit:focus { border: 2px solid #2d89ef; }");
    }

    formLayout->addRow(new QLabel("<font color='black'>Name:</font>"), nameInput);
    formLayout->addRow(new QLabel("<font color='black'>Address:</font>"), addressInput);
    formLayout->addRow(new QLabel("<font color='black'>Phone:</font>"), phoneInput);
    layout->addLayout(formLayout);

    QPushButton *submitButton = new QPushButton("Submit Order");
    submitButton->setFixedSize(200, 50);
    submitButton->setStyleSheet("QPushButton { font-size: 18px; background-color: #2d89ef;"
                                "color: white; border-radius: 8px; }"
                                "QPushButton:hover { background-color: #1e5dbf; }");

    connect(submitButton, &QPushButton::clicked, this, &MainWindow::placeOrder);

    layout->addSpacing(30);
    layout->addWidget(submitButton, 0, Qt::AlignCenter);

    stackedWidget->addWidget(scrollArea);
}

void MainWindow::createCartPage() {
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *cartPage = new QWidget();
    cartPage->setStyleSheet("background-color: #f0f0f0;");
    scrollArea->setWidget(cartPage);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout *layout = new QVBoxLayout(cartPage);

    QToolButton *backButton = new QToolButton();
    backButton->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));
    backButton->setToolTip("Back to Home");
    backButton->setIconSize(QSize(30, 30));
    backButton->setStyleSheet("QToolButton { background: transparent; border: none; margin: 10px; }"
                              "QToolButton:hover { background-color: #dddddd; border-radius: 6px; }");
    connect(backButton, &QToolButton::clicked, this, &MainWindow::showHomePage);

    QLabel *cartLabel = new QLabel("CART PAGE CONTENT");
    cartLabel->setAlignment(Qt::AlignCenter);
    cartLabel->setStyleSheet("font-size: 36px;");
    cartLabel->setMinimumHeight(1200);

    layout->addWidget(backButton, 0, Qt::AlignLeft);
    layout->addWidget(cartLabel);

    stackedWidget->addWidget(scrollArea);
}

void MainWindow::createCategoryPage(const QString &name) {
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *page = new QWidget();
    page->setStyleSheet("background-color: #f0f0f0;");
    scrollArea->setWidget(page);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout *layout = new QVBoxLayout(page);

    QToolButton *backButton = new QToolButton();
    backButton->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));
    backButton->setToolTip("Back to Home");
    backButton->setIconSize(QSize(30, 30));
    backButton->setStyleSheet("QToolButton { background: transparent; border: none; margin: 10px; }"
                              "QToolButton:hover { background-color: #dddddd; border-radius: 6px; }");
    connect(backButton, &QToolButton::clicked, this, &MainWindow::showHomePage);
    layout->addWidget(backButton, 0, Qt::AlignLeft);

    QLabel *label = new QLabel(name.toUpper() + " PAGE");
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 36px;");
    label->setMinimumHeight(800);
    layout->addWidget(label);

    categoryPages[name] = scrollArea;
    stackedWidget->addWidget(scrollArea);
}

void MainWindow::showHomePage() {
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::showShippingPage() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showCartPage() {
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::showCategoryPage(const QString &category) {
    if (categoryPages.contains(category)) {
        stackedWidget->setCurrentWidget(categoryPages[category]);
    }
}

void MainWindow::placeOrder() {
    QString name = nameInput->text();
    QString address = addressInput->text();
    QString phone = phoneInput->text();

    if (name.isEmpty() || address.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "Incomplete Details", "Please fill in all the fields before submitting the order.");
        return;
    }

    QMessageBox::information(this, "Order Placed", "Thank you for your order!\n\nShipping To:\n" + name + "\n" + address + "\nPhone: " + phone);

    nameInput->clear();
    addressInput->clear();
    phoneInput->clear();

    showHomePage();
}
