HEADERS = vertex.h \
    file_ply_stl.h \
    jpg_imagen.hpp \
    jpg_jinclude.h \
    jpg_memsrc.hpp \
    jpg_readwrite.hpp
SOURCES = main.cc \
    file_ply_stl.cc \
    jpg_imagen.cpp \
    jpg_memsrc.cpp \
    jpg_readwrite.cpp

LIBS += libfreeglut -lopengl32 -lglu32 -luser32 -ljpeg
CONFIG += console
QT += opengl
