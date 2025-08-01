#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv); // Manages GUI application-wide resources

    MainWindow w; // Create the main window
    w.show();     // Show the main window

    return a.exec(); // Enters the Qt event loop
}
