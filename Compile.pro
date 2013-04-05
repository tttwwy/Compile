TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    scanner.cpp \
    lalr.cpp

HEADERS += \
    scanner.h \
    lalr.h \
    element.h \
    rule.h \
    define.h \
    grammar.h \
    generator.h \
    elementset.h \
    item.h \
    ItemSet.h

