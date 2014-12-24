HEADERS = \
    vertex.h \
    file_ply_stl.h \
    figura.h
SOURCES = \
    practica2.cc \
    file_ply_stl.cc \
    figura.cc
LIBS += libfreeglut -lopengl32 -lglu32 -luser32
CONFIG += console
QT += opengl
