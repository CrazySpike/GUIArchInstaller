#include "mainwindow.h"
#include "pages.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) { // , stackedWidget(new QStackedWidget(this)

    setWindowTitle("GUI Arch Installer");

    // Pages internally manages QStackedWidget
    auto *pages = new Pages(this);
    setCentralWidget(pages);
}
