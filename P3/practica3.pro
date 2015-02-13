HEADERS = \
    vertex.h \
    file_ply_stl.h \
    figura.h \
    coche.h \
    torillo.h \
    torilloV2.h
SOURCES = \
    practica3.cc \
    file_ply_stl.cc \
    figura.cc \
    coche.cc \
    torillo.cc \
    torilloV2.cc
LIBS += libfreeglut -lopengl32 -lglu32 -luser32
CONFIG += console
QT += opengl
