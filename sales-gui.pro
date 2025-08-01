# Tells qmake which Qt modules to use. 'core' and 'gui' are included by default.
QT += widgets

# The name of the final executable
TARGET = SalesApp

# C++ standard
CONFIG += c++11

# The source files needed to build the project
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    saleslogic.cpp

# The header files needed to build the project
HEADERS += \
    mainwindow.h \
    saleslogic.h

# Default install path for the application.
target.path = /usr/local/bin
INSTALLS += target
