HEADERS = user_code.h \
    vertex.h \
    file_ply_stl.h
SOURCES = user_code.cc \
    practica1.cc \
    file_ply_stl.cc
LIBS += libfreeglut -lopengl32 -lglu32 -luser32
CONFIG += console
QT += opengl
