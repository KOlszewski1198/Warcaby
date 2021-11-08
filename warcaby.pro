TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    interfejs.cpp \
    plansza.cpp \
    statystyki_ranking.cpp \
    zapisz_wczytaj_cofnij.cpp

HEADERS += \
    interfejs.h \
    plansza.h \
    statystyki_ranking.h \
    zapisz_wczytaj_cofnij.h
