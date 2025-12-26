#include "pages.h"

Pages::Pages(QWidget *parent) : QWidget(parent)
{
    auto *rootLayout = new QVBoxLayout(this);

    stack = new QStackedWidget(this);
    rootLayout->addWidget(stack);

    stack->addWidget(createPage_Locale());        // index 0
    stack->addWidget(createPage_Keyboard());      // index 1
    stack->addWidget(createPage_Zone());          // index 2
    stack->addWidget(createPage_User());          // index 3
    stack->addWidget(createPage_Installation());  // index 4

    stack->setCurrentIndex(Locale);
}

QWidget *Pages::createPage_Locale()
{
    auto *page = new QWidget();
    auto *layout = new QVBoxLayout(page);

    // --- Horizontal split for page ---
    auto *pageRow = new QHBoxLayout();

    // ========== LEFT HALF ==========
    auto *leftPane = new QWidget();
    auto *leftLayout = new QVBoxLayout(leftPane);
    leftLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    leftLayout->setContentsMargins(30, 30, 30, 30);

    auto *title = new QLabel("Language Selection");
    title->setStyleSheet("font-size: 28px; font-weight: bold;");

    auto *desc = new QLabel(
        "Choose the language you would like the application to use.\n\n"
        "This can be changed later in settings."
        );
    desc->setWordWrap(true);
    desc->setStyleSheet("font-size: 14px; color: #CCCCCC;");

    leftLayout->addWidget(title);
    leftLayout->addSpacing(15);
    leftLayout->addWidget(desc);
    leftLayout->addStretch();

    pageRow->addWidget(leftPane, 1);

    // ========== RIGHT HALF ==========
    auto *rightPane = new QWidget();
    auto *rightLayout = new QVBoxLayout(rightPane);
    rightLayout->setContentsMargins(0, 0, 0, 0);

    auto *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    auto *scrollWidget = new QWidget();
    auto *langLayout = new QVBoxLayout(scrollWidget);
    langLayout->setAlignment(Qt::AlignTop);

    for (const auto &entry : languages) {
        auto *btn = createSelectionButtons(entry, Locale);
        langLayout->addWidget(btn);
    }

    scrollArea->setWidget(scrollWidget);
    rightLayout->addWidget(scrollArea);

    pageRow->addWidget(rightPane, 1);

    // --- Add to main layout ---
    layout->addLayout(pageRow, 1);

    return page;
}

QWidget *Pages::createPage_Keyboard()
{
    auto *page = new QWidget();
    auto *layout = new QVBoxLayout(page);

    // --- Horizontal split for page ---
    auto *pageRow = new QHBoxLayout();

    // ========== LEFT HALF ==========
    auto *leftPane = new QWidget();
    auto *leftLayout = new QVBoxLayout(leftPane);
    leftLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    leftLayout->setContentsMargins(30, 30, 30, 30);

    auto *title = new QLabel("Keyboard Layout\n\nSelection");
    title->setStyleSheet("font-size: 28px; font-weight: bold;");

    auto *desc = new QLabel(
        "Choose the keyboard layout you would like the application to use.\n\n"
        "This can be changed later in settings."
        );
    desc->setWordWrap(true);
    desc->setStyleSheet("font-size: 14px; color: #CCCCCC;");

    leftLayout->addWidget(title);
    leftLayout->addSpacing(15);
    leftLayout->addWidget(desc);
    leftLayout->addStretch();

    pageRow->addWidget(leftPane, 1);   // Left 50%

    // --- Bottom bar ---
    auto *bottomBar = new QWidget();
    auto *bottomLayout = new QHBoxLayout(bottomBar);

    auto *backBtn = createNavigationButtons("Back", "#4CAF50");

    bottomLayout->addWidget(backBtn);
    bottomLayout->addStretch();
    bottomBar->setLayout(bottomLayout);

    leftLayout->addWidget(bottomBar, 0);

    connect(backBtn, &QPushButton::clicked, this, [this]() {
        switchPage(Locale);
    });

    // ========== RIGHT HALF ==========
    auto *rightPane = new QWidget();
    auto *rightLayout = new QVBoxLayout(rightPane);
    rightLayout->setContentsMargins(0, 0, 0, 0);

    auto *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    auto *scrollWidget = new QWidget();
    auto *langLayout = new QVBoxLayout(scrollWidget);
    langLayout->setAlignment(Qt::AlignTop);

    for (const auto &entry : keyboardLayouts) {
        auto *btn = createSelectionButtons(entry, Keyboard);
        langLayout->addWidget(btn);
    }

    scrollArea->setWidget(scrollWidget);
    rightLayout->addWidget(scrollArea);

    pageRow->addWidget(rightPane, 1);

    // --- Add to main layout ---
    layout->addLayout(pageRow, 1);

    return page;
}

QWidget *Pages::createPage_Zone()
{
    auto *page = new QWidget();
    auto *layout = new QVBoxLayout(page);

    // --- Horizontal split for page ---
    auto *pageRow = new QHBoxLayout();

    // ========== LEFT HALF ==========
    auto *leftPane = new QWidget();
    auto *leftLayout = new QVBoxLayout(leftPane);
    leftLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    leftLayout->setContentsMargins(30, 30, 30, 30);

    auto *title = new QLabel("Country/Region\nSelection");
    title->setStyleSheet("font-size: 28px; font-weight: bold;");

    auto *desc = new QLabel(
        "Choose the country/region you would like the application to use.\n\n"
        "This can be changed later in settings."
        );
    desc->setWordWrap(true);
    desc->setStyleSheet("font-size: 14px; color: #CCCCCC;");

    leftLayout->addWidget(title);
    leftLayout->addSpacing(15);
    leftLayout->addWidget(desc);
    leftLayout->addStretch();

    pageRow->addWidget(leftPane, 1);

    // --- Bottom bar ---
    auto *bottomBar = new QWidget();
    auto *bottomLayout = new QHBoxLayout(bottomBar);

    auto *backBtn = createNavigationButtons("Back", "#4CAF50");

    bottomLayout->addWidget(backBtn);
    bottomLayout->addStretch();
    bottomBar->setLayout(bottomLayout);

    leftLayout->addWidget(bottomBar, 0);

    connect(backBtn, &QPushButton::clicked, this, [this]() {
        switchPage(Keyboard);
    });

    // ========== RIGHT HALF ==========
    auto *rightPane = new QWidget();
    auto *rightLayout = new QVBoxLayout(rightPane);
    rightLayout->setContentsMargins(0, 0, 0, 0);

    auto *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    zoneScrollWidget = new QWidget();
    zoneListLayout = new QVBoxLayout(zoneScrollWidget);
    zoneListLayout->setAlignment(Qt::AlignTop);

    scrollArea->setWidget(zoneScrollWidget);
    rightLayout->addWidget(scrollArea);

    pageRow->addWidget(rightPane, 1);

    populateZoneList(ZoneCategories);

    // --- Add to main layout ---
    layout->addLayout(pageRow, 1);

    return page;
}

QWidget *Pages::createPage_User()
{
    auto *page = new QWidget();
    auto *layout = new QVBoxLayout(page);

    auto *middleBar = new QWidget();
    auto *middleLayout = new QVBoxLayout(middleBar);
    middleLayout->setContentsMargins(10, 10, 10, 10);
    middleLayout->setSpacing(15);

    // Create username label + entry
    auto *usernameLabel = new QLabel("Username:");
    auto *usernameEdit = new QLineEdit();
    usernameEdit->setPlaceholderText("Enter your username");

    // Create password label + entry
    auto *passwordLabel = new QLabel("Password:");
    auto *passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("Enter your password");
    passwordEdit->setEchoMode(QLineEdit::Password);

    // Create password label + entry again
    auto *passwordLabelAgain = new QLabel("Re-enter Password:");
    auto *passwordEditAgain = new QLineEdit();
    passwordEditAgain->setPlaceholderText("Re-enter your password");
    passwordEditAgain->setEchoMode(QLineEdit::Password);

    // Create the add button
    auto *addButton = createNavigationButtons("Add", "#4CAF50");

    // Connect the add button
    // connect(addButton, &QPushButton::clicked, this, [this]() {
    //     buildPage(Page4_Installation);
    // });

    // Add widgets to the layout in order
    middleLayout->addWidget(usernameLabel);
    middleLayout->addWidget(usernameEdit);
    middleLayout->addWidget(passwordLabel);
    middleLayout->addWidget(passwordEdit);
    middleLayout->addWidget(passwordLabelAgain);
    middleLayout->addWidget(passwordEditAgain);
    middleLayout->addWidget(addButton, 0, Qt::AlignHCenter);
    middleBar->setLayout(middleLayout);

    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    layout->addWidget(middleBar, 0, Qt::AlignVCenter);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    auto *bottomBar = new QWidget();
    auto *bottomLayout = new QHBoxLayout(bottomBar);
    bottomLayout->setContentsMargins(10, 10, 10, 10);
    bottomLayout->setSpacing(15);

    auto *backBtn = createNavigationButtons("Back", "#4CAF50");
    auto *nextBtn = createNavigationButtons("Next", "#4CAF50");
    layout->addWidget(nextBtn);

    bottomLayout->addWidget(backBtn);
    bottomLayout->addWidget(nextBtn);
    bottomBar->setLayout(bottomLayout);

    layout->addWidget(bottomBar, 0, Qt::AlignBottom); // Fixed at bottom

    connect(backBtn, &QPushButton::clicked, this, [this]() {
        switchPage(Zone);
    });
    connect(nextBtn, &QPushButton::clicked, this, [this]() {
        getLocale();
        switchPage(Installation);
    });

    return page;
}

QWidget *Pages::createPage_Installation()
{
    auto *page = new QWidget();
    auto *layout = new QVBoxLayout(page);

    auto *bottomBar = new QWidget();
    auto *bottomLayout = new QHBoxLayout(bottomBar);
    bottomLayout->setContentsMargins(10, 10, 10, 10);
    bottomLayout->setSpacing(15);

    auto *backBtn = createNavigationButtons("Back", "#4CAF50");
    auto *finishBtn = createNavigationButtons("Finish", "#4CAF50");
    layout->addWidget(finishBtn);

    bottomLayout->addWidget(backBtn);
    bottomLayout->addWidget(finishBtn);
    bottomBar->setLayout(bottomLayout);

    layout->addWidget(bottomBar, 0, Qt::AlignBottom); // Fixed at bottom

    connect(backBtn, &QPushButton::clicked, this, [this]() {
        switchPage(User);
    });
    connect(finishBtn, &QPushButton::clicked, this, [this]() {
        writeToEnv();
        qDebug() << locale;
    });

    return page;
}

void Pages::switchPage(PageType type)
{
    stack->setCurrentIndex(type);
}

void Pages::populateZoneList(ZoneListMode type)
{
    // Remove old buttons
    QLayoutItem *item;
    while ((item = zoneListLayout->takeAt(0)) != nullptr) {
        if (item->widget())
            item->widget()->deleteLater();
        delete item;
    }

    // Add new buttons
    switch (type) {
        case ZoneCategories: {
            for (const auto &entry : timeZoneCategories) {
                auto *btn = createFilterButtons(entry);
                zoneListLayout->addWidget(btn);
            }
            break;
        }
        case ZoneFiltered: {
            auto *backBtn = new QPushButton(" <--- Back", this);
            backBtn->setStyleSheet(
                "QPushButton {"
                "  background-color: #3E4751;"
                "  color: #C7D4E2;"
                "  font-weight: bold;"
                "  padding: 10px;"
                "}"
                "QPushButton:hover {"
                "  background-color: #C7D4E2;"
                "  color: #3E4751;"
                "}"
                );
            backBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

            zoneListLayout->addWidget(backBtn);

            connect(backBtn, &QPushButton::clicked, this, [this]() {
                qDebug() << "Going back to filter selection";
                populateZoneList(ZoneCategories);
            });

            for (const auto &entry : std::as_const(filteredZones)) {
                auto *btn = createSelectionButtons(entry, Zone);
                zoneListLayout->addWidget(btn);
            }
            break;
        }
        default:
            qWarning() << "Failed to populate zone list";
            break;
    }

    zoneListLayout->addStretch();
}

QPushButton *Pages::createNavigationButtons(const QString &text, const QString &color) {
    auto *btn = new QPushButton(text, this);
    btn->setStyleSheet(QString(
                           "QPushButton {"
                           " background-color: %1;"
                           " color: white;"
                           " font-size: 18px;"
                           " padding: 10px;"
                           " border-radius: 8px;"
                           " margin: 5px;"
                           " }").arg(color));
    return btn;
}

QPushButton *Pages::createFilterButtons(const QString &entry)
{
    auto *btn = new QPushButton(entry);
    btn->setStyleSheet(
        "QPushButton {"
        "  background-color: #3E4751;"
        "  color: #C7D4E2;"
        "  font-weight: bold;"
        "  padding: 10px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #C7D4E2;"
        "  color: #3E4751;"
        "}"
        );
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    connect(btn, &QPushButton::clicked, this, [this, entry]() {
        qDebug() << "Filtering zones for:" << entry;
        filteredZones = filterZones(entry);
        populateZoneList(ZoneFiltered);
    });

    return btn;
}

QPushButton *Pages::createSelectionButtons(const QPair<QString, QString> &entry, PageType type)
{
    auto *btn = new QPushButton(entry.first);
    btn->setStyleSheet(
        "QPushButton {"
        "  background-color: #3E4751;"
        "  color: #C7D4E2;"
        "  font-weight: bold;"
        "  padding: 10px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #C7D4E2;"
        "  color: #3E4751;"
        "}"
    );
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    switch (type) {
        case Locale:
            connect(btn, &QPushButton::clicked, this, [this, entry]() {
                lang = entry.second;
                qDebug() << lang;
                switchPage(Keyboard);
            });
            break;
        case Keyboard:
            connect(btn, &QPushButton::clicked, this, [this, entry]() {
                keyboard = entry.second;
                qDebug() << keyboard;
                switchPage(Zone);
            });
            break;
        case Zone:
            connect(btn, &QPushButton::clicked, this, [this, entry]() {
                zone = entry.first;
                country = entry.second;
                qDebug() << zone;
                qDebug() << country;
                switchPage(User);
            });
            break;
        default:
            qWarning() << "Failed to switch pages";
            break;
    }

    return btn;
}

QVector<QPair<QString, QString>> Pages::filterZones(const QString &entry)
{
    QVector<QPair<QString, QString>> result;

    QStringMatcher matcher(entry);

    for (const auto &entry : timeZones) {
        if (matcher.indexIn(entry.first) != -1)
        {
            result.push_back(entry);
        }
    }

    return result;
}

void Pages::getLocale()
{
    const QStringList filterLang = localeCodes.filter(lang);

    const QStringList filterCountry = filterLang.filter(country);

    if (!filterCountry.isEmpty())
        locale = filterCountry.first();
    else
        locale = filterLang.first();
}

void Pages::writeToEnv()
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << file.errorString();
        return;
    }

    QByteArray text = file.readAll();

    text.replace(QByteArray("locale"), locale.toUtf8());
    text.replace(QByteArray("keymap"), keyboard.toUtf8());
    text.replace(QByteArray("zoneinfo"), zone.toUtf8());


    file.seek(0);
    file.write(text);

    file.close();
}
