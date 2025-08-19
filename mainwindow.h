#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QStackedWidget>
#include <QTimeZone>

enum Screen {LOCALE, ZONE, USER};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QStackedWidget *stackedWidget;
    QWidget *localePage;
    QWidget *zonePage;
    QWidget *userPage;

    QProcess *process;
    Screen currentScreen{LOCALE};

    QWidget* createLocalePage();
    QWidget* createZonePage();
    QWidget* createUserPage();

    void populateLocale(QComboBox *combo);
    void populateZone(QComboBox *combo);

    void updateScreen();
    void back();
    void next();

    void startScript();
};

#endif // MAINWINDOW_H
