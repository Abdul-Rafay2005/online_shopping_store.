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
#include <QFontDatabase>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    shippingPage(nullptr),
    cartPage(nullptr),
    cartTotal(0.0),
    cartTotalLabel(nullptr)
{
    this->showFullScreen();
    setMenuBar(nullptr);

    // Apply custom font
    QFontDatabase::addApplicationFont(":/resources/fonts/Roboto-Regular.ttf");
    QFont font("Roboto", 12);
    setFont(font);

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

MainWindow::~MainWindow()
{
    // Qt's parent-child relationship handles cleanup
}

void MainWindow::saveOrder(const QString &customerName, const QString &address, const QString &phone,
                           const QList<QPair<QString, double>> &items, double total)
{
    // Create order object
    QJsonObject order;
    order["date"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    order["customer"] = customerName;
    order["address"] = address;
    order["phone"] = phone;
    order["total"] = total;

    // Add items array
    QJsonArray itemsArray;
    for (const auto &item : items) {
        QJsonObject itemObj;
        itemObj["name"] = item.first;
        itemObj["price"] = item.second;
        itemsArray.append(itemObj);
    }
    order["items"] = itemsArray;

    // Read existing orders
    QFile file("orders.json");
    QJsonArray allOrders;

    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        if (doc.isArray()) {
            allOrders = doc.array();
        }
        file.close();
    }

    // Add new order
    allOrders.append(order);

    // Save back to file
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(allOrders);
        file.write(doc.toJson());
        file.close();
    }
}

void MainWindow::viewOrders()
{
    QFile file("orders.json");
    if (!file.exists()) {
        QMessageBox::information(this, "Orders", "No orders have been placed yet.");
        return;
    }

    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        if (doc.isArray()) {
            QString ordersText;
            QJsonArray orders = doc.array();

            for (const QJsonValue &orderVal : orders) {
                QJsonObject order = orderVal.toObject();
                ordersText += QString("Date: %1\nCustomer: %2\nTotal: $%3\n\n")
                                  .arg(order["date"].toString())
                                  .arg(order["customer"].toString())
                                  .arg(order["total"].toDouble(), 0, 'f', 2);
            }

            QMessageBox::information(this, "Order History", ordersText);
        }
    }
}

void MainWindow::showHomePage()
{
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::showShippingPage()
{
    if (!shippingPage) {
        createShippingPage();
    }
    stackedWidget->setCurrentWidget(shippingPage);
}

void MainWindow::showCartPage()
{
    if (!cartPage) {
        createCartPage();
    }
    stackedWidget->setCurrentWidget(cartPage);
}

void MainWindow::placeOrder()
{
    if (!nameInput || !addressInput || !phoneInput) {
        QMessageBox::warning(this, "Error", "Shipping information fields not initialized");
        return;
    }

    if (nameInput->text().isEmpty() || addressInput->text().isEmpty() || phoneInput->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all shipping information fields");
        return;
    }

    if (cartItems.isEmpty()) {
        QMessageBox::warning(this, "Error", "Your cart is empty. Please add items before placing an order.");
        return;
    }

    // Save the order
    saveOrder(nameInput->text(), addressInput->text(), phoneInput->text(), cartItems, cartTotal);

    // Process order
    QString orderSummary = "Order Summary:\n\n";
    for (const auto &item : cartItems) {
        orderSummary += QString("%1 - $%2\n").arg(item.first).arg(item.second, 0, 'f', 2);
    }
    orderSummary += QString("\nTotal: $%1").arg(cartTotal, 0, 'f', 2);
    orderSummary += QString("\n\nShipping to:\n%1\n%2\n%3")
                        .arg(nameInput->text())
                        .arg(addressInput->text())
                        .arg(phoneInput->text());

    QMessageBox::information(this, "Order Placed", "Your order has been placed successfully!\n\n" + orderSummary);

    // Clear cart
    cartItems.clear();
    cartTotal = 0.0;
    updateCartPage();
    showHomePage();
}

void MainWindow::showCategoryPage(const QString &category)
{
    if (categoryPages.contains(category)) {
        stackedWidget->setCurrentWidget(categoryPages[category]);
    } else {
        QMessageBox::warning(this, "Error", "Category page not found");
    }
}

void MainWindow::addToCart()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString productName = button->property("productName").toString();
        double productPrice = button->property("productPrice").toDouble();

        cartItems.append(qMakePair(productName, productPrice));
        cartTotal += productPrice;

        QMessageBox::information(this, "Added to Cart",
                                 QString("%1 added to your cart\nCurrent Total: $%2")
                                     .arg(productName)
                                     .arg(cartTotal, 0, 'f', 2));

        // Update cart page if it's already created
        if (cartPage) {
            updateCartPage();
        }
    }
}

void MainWindow::createHomePage()
{
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *homePage = new QWidget();
    homePage->setStyleSheet("background-color: #f9f9f9;");
    scrollArea->setWidget(homePage);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QVBoxLayout *mainLayout = new QVBoxLayout(homePage);

    // Top Bar
    QWidget *topBar = new QWidget();
    QHBoxLayout *topBarLayout = new QHBoxLayout(topBar);
    topBarLayout->setContentsMargins(15, 15, 15, 15);
    topBarLayout->setSpacing(15);

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
        "QPushButton { font-size: 18px; background-color: #2d89ef; color: white; border: none; border-radius: 12px; padding: 12px 20px; text-align: left; }"
        "QPushButton::menu-indicator { subcontrol-position: right center; padding-right: 10px; }"
        "QPushButton:hover { background-color: #1e5dbf; }");

    categoriesMenu->setStyleSheet(
        "QMenu { background-color: #2d89ef; color: white; border: none; }"
        "QMenu::item { padding: 10px; background-color: transparent; }"
        "QMenu::item:selected { background-color: #444444; }");

    searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Search for products...");
    searchBar->setFixedHeight(45);
    searchBar->setStyleSheet(
        "QLineEdit { font-size: 18px; padding: 10px; border: 2px solid #2d89ef; border-radius: 8px; background-color: white; color: black; }"
        "QLineEdit:focus { border: 2px solid #1e5dbf; }");

    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    shippingButton = new QPushButton("Shipping");
    cartButton = new QPushButton("Cart");
    ordersButton = new QPushButton("Orders");

    QList<QPushButton*> topButtons = {shippingButton, cartButton, ordersButton};
    for (QPushButton *btn : topButtons) {
        btn->setFixedSize(120, 45);
        btn->setStyleSheet(
            "QPushButton { font-size: 16px; background-color: #f0f0f0; color: black; border-radius: 8px; border: 1px solid #ccc; }"
            "QPushButton:hover { background-color: #e0e0e0; }");
    }

    connect(shippingButton, &QPushButton::clicked, this, &MainWindow::showShippingPage);
    connect(cartButton, &QPushButton::clicked, this, &MainWindow::showCartPage);
    connect(ordersButton, &QPushButton::clicked, this, &MainWindow::viewOrders);

    // Window controls
    QWidget *windowControls = new QWidget();
    QHBoxLayout *controlsLayout = new QHBoxLayout(windowControls);
    controlsLayout->setContentsMargins(0, 0, 0, 0);
    controlsLayout->setSpacing(0);

    minimizeButton = new QToolButton();
    minimizeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
    minimizeButton->setFixedSize(30, 30);
    minimizeButton->setStyleSheet("QToolButton { border: none; background: transparent; }"
                                  "QToolButton:hover { background-color: #e0e0e0; }");
    connect(minimizeButton, &QToolButton::clicked, this, &QMainWindow::showMinimized);

    maximizeButton = new QToolButton();
    maximizeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    maximizeButton->setFixedSize(30, 30);
    maximizeButton->setStyleSheet("QToolButton { border: none; background: transparent; }"
                                  "QToolButton:hover { background-color: #e0e0e0; }");
    connect(maximizeButton, &QToolButton::clicked, [this]() {
        isMaximized() ? showNormal() : showMaximized();
    });

    closeButton = new QToolButton();
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
    topBarLayout->addWidget(ordersButton);
    topBarLayout->addWidget(windowControls);

    // Home content with featured products
    QWidget *homeContent = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(homeContent);

    QLabel *welcomeLabel = new QLabel("Welcome to our Shopping App!");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 40px; font-weight: bold; color: #2d89ef; margin-bottom: 30px;");
    contentLayout->addWidget(welcomeLabel);

    // Featured Products Section
    QLabel *featuredLabel = new QLabel("Featured Products");
    featuredLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #333; margin: 20px 0;");
    contentLayout->addWidget(featuredLabel);

    // Sample products grid
    QWidget *productsGrid = new QWidget();
    QGridLayout *gridLayout = new QGridLayout(productsGrid);
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(30, 0, 30, 30);

    // Sample products data (name, price)
    QList<QPair<QString, double>> featuredProducts = {
        {"iPhone 13", 799.99},
        {"Samsung Galaxy S22", 749.99},
        {"MacBook Pro", 1299.99},
        {"Sony 4K TV", 899.99},
        {"Apple Watch", 399.99},
        {"AirPods Pro", 249.99}
    };

    for (int i = 0; i < featuredProducts.size(); i++) {
        QWidget *productCard = new QWidget();
        productCard->setStyleSheet("background-color: white; border-radius: 10px; padding: 15px;");
        QVBoxLayout *cardLayout = new QVBoxLayout(productCard);

        QLabel *productImage = new QLabel();
        productImage->setPixmap(QPixmap(":/resources/images/placeholder.png").scaled(150, 150, Qt::KeepAspectRatio));
        productImage->setAlignment(Qt::AlignCenter);

        QLabel *productName = new QLabel(featuredProducts[i].first);
        productName->setStyleSheet("font-size: 16px; font-weight: bold; color: black;"); // Changed to black
        productName->setAlignment(Qt::AlignCenter);

        QLabel *productPrice = new QLabel(QString("$%1").arg(featuredProducts[i].second, 0, 'f', 2));
        productPrice->setStyleSheet("font-size: 14px; color: #2d89ef;");
        productPrice->setAlignment(Qt::AlignCenter);

        QPushButton *addToCart = new QPushButton("Add to Cart");
        addToCart->setProperty("productName", featuredProducts[i].first);
        addToCart->setProperty("productPrice", featuredProducts[i].second);
        addToCart->setStyleSheet(
            "QPushButton { font-size: 14px; background-color: #2d89ef; color: white; border-radius: 5px; padding: 5px; }"
            "QPushButton:hover { background-color: #1e5dbf; }");

        connect(addToCart, &QPushButton::clicked, this, &MainWindow::addToCart);

        cardLayout->addWidget(productImage);
        cardLayout->addWidget(productName);
        cardLayout->addWidget(productPrice);
        cardLayout->addWidget(addToCart);

        gridLayout->addWidget(productCard, i / 3, i % 3);
    }

    contentLayout->addWidget(productsGrid);
    contentLayout->addStretch();

    mainLayout->addWidget(topBar);
    mainLayout->addWidget(homeContent);

    stackedWidget->addWidget(scrollArea);
}

void MainWindow::createShippingPage()
{
    shippingPage = new QWidget();
    shippingPage->setStyleSheet("background-color: #f9f9f9;");

    QVBoxLayout *mainLayout = new QVBoxLayout(shippingPage);

    // Top bar
    QWidget *topBar = new QWidget();
    QHBoxLayout *topBarLayout = new QHBoxLayout(topBar);
    topBarLayout->setContentsMargins(15, 15, 15, 15);
    topBarLayout->setSpacing(15);

    homeButton = new QPushButton("Home");
    homeButton->setFixedSize(120, 45);
    homeButton->setStyleSheet(
        "QPushButton { font-size: 16px; background-color: #f0f0f0; color: black; border-radius: 8px; border: 1px solid #ccc; }"
        "QPushButton:hover { background-color: #e0e0e0; }");
    connect(homeButton, &QPushButton::clicked, this, &MainWindow::showHomePage);

    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    cartButton = new QPushButton("Cart");
    cartButton->setFixedSize(120, 45);
    cartButton->setStyleSheet(
        "QPushButton { font-size: 16px; background-color: #f0f0f0; color: black; border-radius: 8px; border: 1px solid #ccc; }"
        "QPushButton:hover { background-color: #e0e0e0; }");
    connect(cartButton, &QPushButton::clicked, this, &MainWindow::showCartPage);

    topBarLayout->addWidget(homeButton);
    topBarLayout->addWidget(spacer);
    topBarLayout->addWidget(cartButton);

    // Shipping form
    QWidget *formContainer = new QWidget();
    formContainer->setStyleSheet("background-color: white; border-radius: 10px; padding: 20px;");
    QFormLayout *formLayout = new QFormLayout(formContainer);
    formLayout->setSpacing(15);
    formLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titleLabel = new QLabel("Shipping Information");
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2d89ef;");
    formLayout->addRow(titleLabel);

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Full Name");
    nameInput->setStyleSheet("font-size: 16px; padding: 10px; border: 1px solid #ddd; border-radius: 5px;");
    formLayout->addRow("Name:", nameInput);

    addressInput = new QLineEdit();
    addressInput->setPlaceholderText("Full Address");
    addressInput->setStyleSheet("font-size: 16px; padding: 10px; border: 1px solid #ddd; border-radius: 5px;");
    formLayout->addRow("Address:", addressInput);

    phoneInput = new QLineEdit();
    phoneInput->setPlaceholderText("Phone Number");
    phoneInput->setStyleSheet("font-size: 16px; padding: 10px; border: 1px solid #ddd; border-radius: 5px;");
    formLayout->addRow("Phone:", phoneInput);

    orderButton = new QPushButton("Place Order");
    orderButton->setStyleSheet(
        "QPushButton { font-size: 18px; background-color: #2d89ef; color: white; border-radius: 8px; padding: 12px; }"
        "QPushButton:hover { background-color: #1e5dbf; }");
    orderButton->setFixedHeight(50);
    connect(orderButton, &QPushButton::clicked, this, &MainWindow::placeOrder);
    formLayout->addRow(orderButton);

    mainLayout->addWidget(topBar);
    mainLayout->addWidget(formContainer, 0, Qt::AlignCenter);
    mainLayout->addStretch();

    stackedWidget->addWidget(shippingPage);
}

void MainWindow::createCartPage()
{
    cartPage = new QWidget();
    cartPage->setStyleSheet("background-color: #f9f9f9;");

    QVBoxLayout *mainLayout = new QVBoxLayout(cartPage);

    // Top bar
    QWidget *topBar = new QWidget();
    QHBoxLayout *topBarLayout = new QHBoxLayout(topBar);
    topBarLayout->setContentsMargins(15, 15, 15, 15);
    topBarLayout->setSpacing(15);

    homeButton = new QPushButton("Home");
    homeButton->setFixedSize(120, 45);
    homeButton->setStyleSheet(
        "QPushButton { font-size: 16px; background-color: #f0f0f0; color: black; border-radius: 8px; border: 1px solid #ccc; }"
        "QPushButton:hover { background-color: #e0e0e0; }");
    connect(homeButton, &QPushButton::clicked, this, &MainWindow::showHomePage);

    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    shippingButton = new QPushButton("Shipping");
    shippingButton->setFixedSize(120, 45);
    shippingButton->setStyleSheet(
        "QPushButton { font-size: 16px; background-color: #f0f0f0; color: black; border-radius: 8px; border: 1px solid #ccc; }"
        "QPushButton:hover { background-color: #e0e0e0; }");
    connect(shippingButton, &QPushButton::clicked, this, &MainWindow::showShippingPage);

    topBarLayout->addWidget(homeButton);
    topBarLayout->addWidget(spacer);
    topBarLayout->addWidget(shippingButton);

    // Cart content
    QWidget *cartContainer = new QWidget();
    cartContainer->setStyleSheet("background-color: white; border-radius: 10px; padding: 20px;");
    QVBoxLayout *cartLayout = new QVBoxLayout(cartContainer);

    QLabel *titleLabel = new QLabel("Your Shopping Cart");
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2d89ef;");
    cartLayout->addWidget(titleLabel, 0, Qt::AlignCenter);

    // Cart items container
    QWidget *itemsContainer = new QWidget();
    cartItemsLayout = new QVBoxLayout(itemsContainer);
    cartItemsLayout->setSpacing(10);

    // Initialize cart total label
    cartTotalLabel = new QLabel();
    cartTotalLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    updateCartPage(); // Update with current cart items

    cartLayout->addWidget(itemsContainer);
    cartLayout->addWidget(cartTotalLabel, 0, Qt::AlignRight);

    checkoutButton = new QPushButton("Proceed to Checkout");
    checkoutButton->setStyleSheet(
        "QPushButton { font-size: 18px; background-color: #2d89ef; color: white; border-radius: 8px; padding: 12px; }"
        "QPushButton:hover { background-color: #1e5dbf; }");
    checkoutButton->setFixedHeight(50);
    connect(checkoutButton, &QPushButton::clicked, this, &MainWindow::showShippingPage);
    cartLayout->addWidget(checkoutButton);

    mainLayout->addWidget(topBar);
    mainLayout->addWidget(cartContainer);
    mainLayout->addStretch();

    stackedWidget->addWidget(cartPage);
}

void MainWindow::updateCartPage()
{
    // Clear existing items
    QLayoutItem *child;
    while ((child = cartItemsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget();
        }
        delete child;
    }

    // Add current cart items
    if (cartItems.isEmpty()) {
        QLabel *emptyLabel = new QLabel("Your cart is currently empty");
        emptyLabel->setStyleSheet("font-size: 18px; color: #666;");
        emptyLabel->setAlignment(Qt::AlignCenter);
        cartItemsLayout->addWidget(emptyLabel);
    } else {
        for (const auto &item : cartItems) {
            QWidget *itemWidget = new QWidget();
            QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);

            QLabel *nameLabel = new QLabel(item.first);
            nameLabel->setStyleSheet("font-size: 16px; color: black;"); // Changed to black

            QLabel *priceLabel = new QLabel(QString("$%1").arg(item.second, 0, 'f', 2));
            priceLabel->setStyleSheet("font-size: 16px; color: #2d89ef;");

            itemLayout->addWidget(nameLabel, 1);
            itemLayout->addWidget(priceLabel);

            cartItemsLayout->addWidget(itemWidget);
        }
    }

    // Update total
    cartTotalLabel->setText(QString("Total: $%1").arg(cartTotal, 0, 'f', 2));
}

void MainWindow::createCategoryPage(const QString &name)
{
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *categoryPage = new QWidget();
    categoryPage->setStyleSheet("background-color: #f9f9f9;");
    scrollArea->setWidget(categoryPage);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QVBoxLayout *mainLayout = new QVBoxLayout(categoryPage);

    // Top bar
    QWidget *topBar = new QWidget();
    QHBoxLayout *topBarLayout = new QHBoxLayout(topBar);
    topBarLayout->setContentsMargins(15, 15, 15, 15);
    topBarLayout->setSpacing(15);

    homeButton = new QPushButton("Home");
    homeButton->setFixedSize(120, 45);
    homeButton->setStyleSheet(
        "QPushButton { font-size: 16px; background-color: #f0f0f0; color: black; border-radius: 8px; border: 1px solid #ccc; }"
        "QPushButton:hover { background-color: #e0e0e0; }");
    connect(homeButton, &QPushButton::clicked, this, &MainWindow::showHomePage);

    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    shippingButton = new QPushButton("Shipping");
    cartButton = new QPushButton("Cart");

    QList<QPushButton*> topButtons = {shippingButton, cartButton};
    for (QPushButton *btn : topButtons) {
        btn->setFixedSize(120, 45);
        btn->setStyleSheet(
            "QPushButton { font-size: 16px; background-color: #f0f0f0; color: black; border-radius: 8px; border: 1px solid #ccc; }"
            "QPushButton:hover { background-color: #e0e0e0; }");
    }

    connect(shippingButton, &QPushButton::clicked, this, &MainWindow::showShippingPage);
    connect(cartButton, &QPushButton::clicked, this, &MainWindow::showCartPage);

    topBarLayout->addWidget(homeButton);
    topBarLayout->addWidget(spacer);
    topBarLayout->addWidget(shippingButton);
    topBarLayout->addWidget(cartButton);

    // Category content
    QLabel *categoryTitle = new QLabel(name);
    categoryTitle->setStyleSheet("font-size: 32px; font-weight: bold; color: #2d89ef;");
    categoryTitle->setAlignment(Qt::AlignCenter);

    // Sample products grid
    QWidget *productsGrid = new QWidget();
    QGridLayout *gridLayout = new QGridLayout(productsGrid);
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(30, 30, 30, 30);

    // Generate category-specific products
    QList<QPair<QString, double>> products;
    if (name == "Mobiles") {
        products = {
            {"iPhone 14 Pro", 999.99},
            {"Samsung Galaxy S23", 899.99},
            {"Google Pixel 7", 699.99},
            {"OnePlus 11", 749.99},
            {"Xiaomi 13", 599.99},
            {"Nothing Phone 2", 599.99}
        };
    } else if (name == "Laptops") {
        products = {
            {"MacBook Pro 14\"", 1999.99},
            {"Dell XPS 15", 1499.99},
            {"HP Spectre x360", 1299.99},
            {"Lenovo ThinkPad X1", 1399.99},
            {"Asus ROG Zephyrus", 1599.99},
            {"Microsoft Surface Laptop 5", 1299.99}
        };
    } else {
        // Default products for other categories
        for (int i = 1; i <= 6; i++) {
            products.append(qMakePair(QString("%1 Product %2").arg(name).arg(i), (i * 100) + 99.99));
        }
    }

    for (int i = 0; i < products.size(); i++) {
        QWidget *productCard = new QWidget();
        productCard->setStyleSheet("background-color: white; border-radius: 10px; padding: 15px;");
        QVBoxLayout *cardLayout = new QVBoxLayout(productCard);

        QLabel *productImage = new QLabel();
        productImage->setPixmap(QPixmap(":/resources/images/placeholder.png").scaled(150, 150, Qt::KeepAspectRatio));
        productImage->setAlignment(Qt::AlignCenter);

        QLabel *productName = new QLabel(products[i].first);
        productName->setStyleSheet("font-size: 16px; font-weight: bold; color: black;"); // Changed to black
        productName->setAlignment(Qt::AlignCenter);

        QLabel *productPrice = new QLabel(QString("$%1").arg(products[i].second, 0, 'f', 2));
        productPrice->setStyleSheet("font-size: 14px; color: #2d89ef;");
        productPrice->setAlignment(Qt::AlignCenter);

        QPushButton *addToCart = new QPushButton("Add to Cart");
        addToCart->setProperty("productName", products[i].first);
        addToCart->setProperty("productPrice", products[i].second);
        addToCart->setStyleSheet(
            "QPushButton { font-size: 14px; background-color: #2d89ef; color: white; border-radius: 5px; padding: 5px; }"
            "QPushButton:hover { background-color: #1e5dbf; }");

        connect(addToCart, &QPushButton::clicked, this, &MainWindow::addToCart);

        cardLayout->addWidget(productImage);
        cardLayout->addWidget(productName);
        cardLayout->addWidget(productPrice);
        cardLayout->addWidget(addToCart);

        gridLayout->addWidget(productCard, i / 3, i % 3);
    }

    mainLayout->addWidget(topBar);
    mainLayout->addWidget(categoryTitle);
    mainLayout->addWidget(productsGrid);

    categoryPages[name] = scrollArea;
    stackedWidget->addWidget(scrollArea);
}
