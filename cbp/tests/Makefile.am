## Process this file with automake to produce Makefile.in

TESTS = tests_matrix
check_PROGRAMS = tests_matrix
tests_matrix_SOURCES = tests_main.c tests_matrix.c $(top_builddir)/src/matrix.h
tests_matrix_CFLAGS = -Wall -g3 -std=c99 -I$(top_builddir)/src -I$(top_builddir)/tests
tests_matrix_LDADD = $(top_builddir)/src/libmatrix.a

