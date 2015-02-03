HEADERS = vertex.h \
    file_ply_stl.h
SOURCES = main.cc \
    file_ply_stl.cc
LIBS += libfreeglut -lopengl32 -lglu32 -luser32
CONFIG += console
QT += opengl
