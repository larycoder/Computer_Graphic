---
# pandoc slice.md -t beamer -o slice.pdf --slide-level=2
title:
- Two Box and One Source light
subtitle:
- Computer Graphic
author:
- Le Nhu Chu Hiep
- Pham Phan Bach
- Nguyen Duy Anh
date: \today{}
institute:
- University of Science And Technology of Hanoi
theme:
- Ilmenau
colortheme:
- default
toc:
- true
---

# Introduction: Objects System
## Introduction: Objects System
### Computer Graphic
* Game
* System Simulation

### OpenGL
* Standard Specification, Not Library
* GLEW, GLUT
* Immediate and core-profiles -> context
* Mesa

# Objective
## Objective
### Objective
* The simple objects system
* Elements controller
* Scalable world
* OpenGL studying

# Method
## Method
### Window X API
* glutInit
* glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA)
* glutInitWindowPosition
* glutInitWindowSiz
* glutCreateWindow

### Function call Register
* glutDisplayFunc
* glutIdleFunc
* glutReshapeFunc
* glutSpecialFunc, glutSpecialUpFunc, glutKeyboardFunc

## Method
### Setup Parameter
* glEnable
* glMatrixMode
* glLoadIdentity
* gluLookAt, glRotatef, glTranslatef
* gluPerspective, glViewport
* glClearColor, glClear, glutSwapBuffers

## Method
### GL loop
* glutMainLoop

### Special function
* glBegin, glEnd
* glNormal3f, glVertex3f

# Conclusion
## Conclusion
### What we done !
* Draw Primitive object and sphere
* Controll some proporties
* Enable lighting mode

### What we haven't done !
* Texturelize object
* Import model from file
* Sharding object
* Triggle object collision

## Conclusion
### Will we be continue improve system
* YES and NO ! It can be updated as the hobby project
* BUT Im busy now, so It is delay infinite

# Demo


