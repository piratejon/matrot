## Process this file with automake to produce Makefile.in

lib_LIBRARIES = libmatrix.a
libmatrix_a_SOURCES = matrix.c matrix.h

bin_PROGRAMS = matrix
matrix_SOURCES = matrix_main.c
matrix_CFLAGS = -std=c99 -Wall -g3
matrix_LDADD = libmatrix.a -lm

