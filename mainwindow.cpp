#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , process(new QProcess(this))
    , stackedWidget(new QStackedWidget(this))
{
    ui->setupUi(this);

    localePage = createLocalePage();
    zonePage = createZonePage();
    userPage = createUserPage();

    stackedWidget->addWidget(localePage); // index 0
    stackedWidget->addWidget(zonePage);   // index 1
    stackedWidget->addWidget(userPage);   // index 2

    setCentralWidget(stackedWidget);
    updateScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ============================
// Page Creation
// ============================


QWidget* MainWindow::createLocalePage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QComboBox *localeSelector = new QComboBox;
    populateLocale(localeSelector);

    QTextEdit *outputText = new QTextEdit;
    outputText->setReadOnly(true);

    QLineEdit *inputLine = new QLineEdit;
    QPushButton *sendBtn = new QPushButton("Send Input");
    QPushButton *startBtn = new QPushButton("Start Script");

    layout->addWidget(new QLabel("Select Locale:"));
    layout->addWidget(localeSelector);
    layout->addWidget(outputText);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(inputLine);
    inputLayout->addWidget(sendBtn);
    layout->addLayout(inputLayout);

    // Create individual navigation buttons
    // QPushButton *backBtn = new QPushButton("Back");
    QPushButton *nextBtn = new QPushButton("Next");


    //connect(backBtn, &QPushButton::clicked, this, &MainWindow::back);
    connect(nextBtn, &QPushButton::clicked, this, &MainWindow::next);

    QHBoxLayout *controlLayout = new QHBoxLayout;
    //controlLayout->addWidget(backBtn);
    controlLayout->addWidget(nextBtn);
    layout->addLayout(controlLayout);

    layout->addWidget(startBtn);

    // Signal-slot connections
    connect(sendBtn, &QPushButton::clicked, this, [=]() {
        process->write((inputLine->text() + "\n").toUtf8());
        inputLine->clear();
    });

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::startScript);

    connect(process, &QProcess::readyReadStandardOutput, this, [=]() {
        outputText->append(QString::fromUtf8(process->readAllStandardOutput()));
    });

    connect(process, &QProcess::readyReadStandardError, this, [=]() {
        outputText->append(QString::fromUtf8(process->readAllStandardError()));
    });

    return page;
}

QWidget* MainWindow::createZonePage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QComboBox *zoneSelector = new QComboBox;
    populateZone(zoneSelector);

    layout->addWidget(new QLabel("Select Time Zone:"));
    layout->addWidget(zoneSelector);

    // Create individual navigation buttons
    QPushButton *backBtn = new QPushButton("Back");
    QPushButton *nextBtn = new QPushButton("Next");

    connect(backBtn, &QPushButton::clicked, this, &MainWindow::back);
    connect(nextBtn, &QPushButton::clicked, this, &MainWindow::next);

    QHBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->addWidget(backBtn);
    controlLayout->addWidget(nextBtn);
    layout->addLayout(controlLayout);

    return page;
}

QWidget* MainWindow::createUserPage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QTextEdit *outputText = new QTextEdit;
    outputText->setReadOnly(true);

    QLineEdit *username = new QLineEdit;
    QLineEdit *password = new QLineEdit;
    QLineEdit *passwordAgain = new QLineEdit;
    QLineEdit *inputLine = new QLineEdit;
    QPushButton *sendBtn = new QPushButton("Send Input");
    QPushButton *startBtn = new QPushButton("Start Script");

    QHBoxLayout *usernameLayout = new QHBoxLayout;
    usernameLayout->addWidget(new QLabel("Enter Username:"));
    usernameLayout->addWidget(username);
    layout->addLayout(usernameLayout);

    QHBoxLayout *passwordLayout = new QHBoxLayout;
    passwordLayout->addWidget(new QLabel("Enter Password:"));
    layout->addLayout(passwordLayout);
    passwordLayout->addWidget(password);

    QHBoxLayout *passwordLayoutAgain = new QHBoxLayout;
    passwordLayoutAgain->addWidget(new QLabel("Enter Password Again:"));
    layout->addLayout(passwordLayoutAgain);
    passwordLayoutAgain->addWidget(passwordAgain);

    layout->addWidget(outputText);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(inputLine);
    inputLayout->addWidget(sendBtn);
    layout->addLayout(inputLayout);

    // Create individual navigation buttons
    QPushButton *backBtn = new QPushButton("Back");
    QPushButton *nextBtn = new QPushButton("Next");

    nextBtn->setEnabled(false);

    connect(backBtn, &QPushButton::clicked, this, &MainWindow::back);
    connect(nextBtn, &QPushButton::clicked, this, &MainWindow::next);

    QHBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->addWidget(backBtn);
    controlLayout->addWidget(nextBtn);
    layout->addLayout(controlLayout);

    layout->addWidget(startBtn);

    // Hide password text
    password->setEchoMode(QLineEdit::Password);
    passwordAgain->setEchoMode(QLineEdit::Password);

    // === SIGNAL VALIDATION LOGIC ===

    // Validator lambda for enabling "Next"
    auto validateFields = [=]() {
        bool valid = !username->text().isEmpty()
        && !password->text().isEmpty()
            && (password->text() == passwordAgain->text());
        nextBtn->setEnabled(valid);
    };

    // Connect all three input fields to validator
    connect(username, &QLineEdit::textChanged, this, validateFields);
    connect(password, &QLineEdit::textChanged, this, validateFields);
    connect(passwordAgain, &QLineEdit::textChanged, this, validateFields);

    // Signal-slot connections
    connect(sendBtn, &QPushButton::clicked, this, [=]() {
        process->write((inputLine->text() + "\n").toUtf8());
        inputLine->clear();
    });

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::startScript);

    connect(process, &QProcess::readyReadStandardOutput, this, [=]() {
        outputText->append(QString::fromUtf8(process->readAllStandardOutput()));
    });

    connect(process, &QProcess::readyReadStandardError, this, [=]() {
        outputText->append(QString::fromUtf8(process->readAllStandardError()));
    });

    return page;
}

// ============================
// ComboBox Populators
// ============================

void MainWindow::populateLocale(QComboBox *combo)
{
    combo->clear();

    const auto locales = QLocale::matchingLocales(
        QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);

    QSet<QString> seen;

    for (const QLocale &locale : locales)
    {
        QString code = locale.name();
        if (locale.language() == QLocale::C || seen.contains(code))
        {
            continue;
        }

        seen.insert(code);

        QString label = QString("%1 (%2)")
                            .arg(QLocale::languageToString(locale.language()),
                                 QLocale::territoryToString(locale.territory()));

        combo->addItem(label, code);
    }

    QLocale sys = QLocale::system();
    QString sysLabel = QString("%1 (%2)")
                           .arg(QLocale::languageToString(sys.language()),
                                QLocale::territoryToString(sys.territory()));

    int idx = combo->findText(sysLabel);
    if (idx >= 0)
    {
        combo->setCurrentIndex(idx);
    }
}

void MainWindow::populateZone(QComboBox *combo)
{
    combo->clear();

    const auto zoneIds = QTimeZone::availableTimeZoneIds();
    for (const QByteArray &id : zoneIds)
    {
        QTimeZone tz(id);
        if (tz.isValid())
        {
            QString label = QString::fromUtf8(id) + " — " + tz.comment();
            combo->addItem(label, QString::fromUtf8(id));
        }
    }

    QTimeZone sysZone = QTimeZone::systemTimeZone();
    int idx = combo->findData(QString::fromUtf8(sysZone.id()));
    if (idx >= 0)
    {
        combo->setCurrentIndex(idx);
    }
}

// ============================
// Navigation + Logic
// ============================

void MainWindow::updateScreen()
{
    switch (currentScreen)
    {
    case LOCALE:
        stackedWidget->setCurrentWidget(localePage);
        break;
    case ZONE:
        stackedWidget->setCurrentWidget(zonePage);
        break;
    case USER:
        stackedWidget->setCurrentWidget(userPage);
        break;
    }
}

void MainWindow::back()
{
    if (currentScreen == ZONE)
    {
        currentScreen = LOCALE;
    }
    else if (currentScreen == USER)
    {
        currentScreen = ZONE;
    }

    updateScreen();
    qDebug() << "Back to screen:" << currentScreen;
}

void MainWindow::next()
{
    if (currentScreen == LOCALE)
    {
        currentScreen = ZONE;
    }
    else if (currentScreen == ZONE)
    {
        currentScreen = USER;
    }

    updateScreen();
    qDebug() << "Next to screen:" << currentScreen;
}

void MainWindow::startScript()
{
    QString scriptPath = "/Users/bwr/Desktop/Scripts/test.sh";
    process->start("/bin/bash", QStringList() << scriptPath);

    if (!process->waitForStarted()) {
        qDebug() << "Script failed to start";
    }
}
