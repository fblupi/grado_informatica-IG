HEADERS = \
    vertex.h \
    file_ply_stl.h \
    figura.h \
    coche.h \
    torillo.h \
    lata.h \
    jpg_imagen.hpp \
    jpg_jinclude.h \
    jpg_memsrc.hpp \
    jpg_readwrite.hpp \
    material.h \
    textura.h \
    luz.h \
    cubo.h
SOURCES = \
    practica4.cc \
    file_ply_stl.cc \
    figura.cc \
    coche.cc \
    torillo.cc \
    lata.cc \
    jpg_imagen.cpp \
    jpg_memsrc.cpp \
    jpg_readwrite.cpp \
    material.cc \
    textura.cc \
    luz.cc \
    cubo.cc
LIBS += libfreeglut -lopengl32 -lglu32 -luser32 -ljpeg
CONFIG += console
QT += opengl
