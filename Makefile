# 
# Small makefile for Tex
#


Noel: main.o Bone.o Cadeau.o Forest.o Ground.o Robot.o Texture.o 
	g++ -o Noel main.o Bone.o Cadeau.o Forest.o Ground.o Robot.o Texture.o -L/usr/X11R6/lib -lGL -lGLEW -lGLU -lglut -lm
all: Noel
