#!/bin/bash

CC=g++
CPPFLAGS=`pkg-config --cflags glew `
CPPFLAGS="$CPPFLAGS -I../Include"
LDFLAGS=`pkg-config --libs glew `
LDFLAGS="$LDFLAGS -lglut -lX11"

$CC ExercicioBase.cpp BuleUtah.cpp Icosaedro.cpp Mesa.cpp  ogldev_util.cpp  math_3d.cpp world_transform.cpp camera.cpp $CPPFLAGS $LDFLAGS -o ExercicioBase
