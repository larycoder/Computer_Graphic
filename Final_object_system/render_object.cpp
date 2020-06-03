#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include <GL/glew.h>//OpenGL Extension Wrangler Library 
#include <GL/glut.h>//Utilities e.g: setting camera view and projection

using namespace std;

// Define class vector
struct Vector3f{
  float x, y, z;
  Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

GLfloat size_1 = 0.5f, size_2 = 4.0f; // size of object
GLfloat angle = 0.0f; // auto-rotate variable
GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 }; // light
GLfloat mat_shininess[] = { 10.0 };

Vector3f Eye(8, 0, 15); // eye position
Vector3f At(5, 0, 11); // at position
Vector3f Target_vector(-3.0 / 5.0, 0.0, -4.0 / 5.0);
Vector3f light_color(1.0, 1.0, 0.0);

// updating value for keyboard triggle
float deltaAngle = 0.0f;
float deltaMove = 0.0f;

// recompute position after triggle
void computePos(float deltaMove){
  Eye.z += deltaMove * Target_vector.z * 0.1f;
  At.z += deltaMove * Target_vector.z * 0.1f;

  Eye.x += deltaMove * Target_vector.x * 0.1f;
  At.x += deltaMove * Target_vector.x * 0.1f;

  Eye.y += deltaMove * Target_vector.y * 0.1f;
  At.y += deltaMove * Target_vector.y * 0.1f;
}

void computeDir(float deltaAngle){
  // recompute x, z
  At.x = Target_vector.x * cos(deltaAngle) - Target_vector.z * sin(deltaAngle) + Eye.x;
  At.z = Target_vector.x * sin(deltaAngle) + Target_vector.z * cos(deltaAngle) + Eye.z;

  Target_vector.x = At.x - Eye.x;
  Target_vector.z = At.z - Eye.z;
  // cout << At.x << At.z;
}

// keyword triggle
void keyword(unsigned char key, int x, int y){
  switch(key){
    case 'q':
      size_1 += 0.5f;
      break;
    case 'e':
      size_1 -= 0.5f;
      break;
    case 'r':
      size_2 += 0.5f;
      break;
    case 't':
      size_2 -= 0.5f;
      break;
    case 'w':
      light_position[1] += 0.5f;
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);
      break;
    case 's':
      light_position[1] -= 0.5f;
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);
      break;
    case 'a':
      light_position[2] += 0.5f;
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);
      break;
    case 'd':
      light_position[2] -= 0.5f;
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);
      break;
    case 'z':
      light_position[0] += 0.5f;
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);
      break;
    case 'x':
      light_position[0] -= 0.5f;
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);
      break;
  }
}

// keyboard triggle
void pressKey(int key, int x, int y){
  switch(key){
    case GLUT_KEY_LEFT: 
      deltaAngle = -0.005f;
      break;
    case GLUT_KEY_RIGHT:
      deltaAngle = 0.005f;
      break;
    case GLUT_KEY_UP:
      deltaMove = 0.5f;
      break;
    case GLUT_KEY_DOWN:
      deltaMove = -0.5f;
      break;
  }
}

void releaseKey(int key, int x, int y) {
	switch (key) {
	  case GLUT_KEY_RIGHT:
      deltaAngle = 0.0f;
      break;
    case GLUT_KEY_LEFT:
      deltaAngle = 0.0f;
      break;
	  case GLUT_KEY_DOWN:
      deltaMove = 0.0f;
      break;
    case GLUT_KEY_UP:
      deltaMove = 0.0f;
      break;
	}
}

// reshape func
void changeSize(int w, int h){
  if(h == 0) h = 1;
  float ratio = (float)w / (float)h;

  // modify coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, ratio, 0.1, 100.0); // set up correct perspective
  glViewport(0, 0, w, h); // set state of user screen
}

void drawCule(){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, 0.0, 1.0, 0.0); // eye, at, up
  glRotatef(0.25 * angle, 0.0f, 0.0f, 1.0f);
  glTranslatef(-size_1 / 2.0, -size_1 / 2.0, -size_1 / 2.0);
  glColor3f(light_color.x, light_color.y, light_color.z);
  glBegin(GL_QUADS);
    // y_1
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(1.0 * size_1, 0.0 * size_1, 0.0 * size_1);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.0 * size_1, 0.0 * size_1, 0.0 * size_1);
    glNormal3f(0.0, -1.0, 0.0);
	  glVertex3f(0.0 * size_1, 0.0 * size_1, 1.0 * size_1);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(1.0 * size_1, 0.0 * size_1, 1.0 * size_1);
    // y_2
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(1.0 * size_1, 1.0 * size_1, 0.0 * size_1);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0.0 * size_1, 1.0 * size_1, 0.0 * size_1);
    glNormal3f(0.0, 1.0, 0.0);
	  glVertex3f(0.0 * size_1, 1.0 * size_1, 1.0 * size_1);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(1.0 * size_1, 1.0 * size_1, 1.0 * size_1);
    // x_1
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0 * size_1, 0.0 * size_1, 0.0 * size_1);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0 * size_1, 1.0 * size_1, 0.0 * size_1);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0 * size_1, 1.0 * size_1, 1.0 * size_1);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0 * size_1, 0.0 * size_1, 1.0 * size_1);
    // x_2
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.0 * size_1, 0.0 * size_1, 0.0 * size_1);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.0 * size_1, 1.0 * size_1, 0.0 * size_1);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.0 * size_1, 1.0 * size_1, 1.0 * size_1);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.0 * size_1, 0.0 * size_1, 1.0 * size_1);
    // z_1
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(1.0 * size_1, 0.0 * size_1, 0.0 * size_1);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(1.0 * size_1, 1.0 * size_1, 0.0 * size_1);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.0 * size_1, 1.0 * size_1, 0.0 * size_1);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.0 * size_1, 0.0 * size_1, 0.0 * size_1);
    // z_2
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(1.0 * size_1, 0.0 * size_1, 1.0 * size_1);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(1.0 * size_1, 1.0 * size_1, 1.0 * size_1);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.0 * size_1, 1.0 * size_1, 1.0 * size_1);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.0 * size_1, 0.0 * size_1, 1.0 * size_1);
  glEnd();
}

void drawCule2(){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, 0.0, 1.0, 0.0); // eye, at, up
  glRotatef(angle, 0.0f, 0.0f, 1.0f);
  glTranslatef(-5.0f, 5.0f, 0.0f);
  glRotatef(angle, 0.0f, 0.0f, 1.0f);
  glTranslatef(-size_2 / 2.0, -size_2 / 2.0, -size_2 / 2.0);
  glColor3f(0.0, 1.0, 0.0);

  glBegin(GL_QUADS);
    // y_1
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(1.0 * size_2, 0.0 * size_2, 0.0 * size_2);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.0 * size_2, 0.0 * size_2, 0.0 * size_2);
    glNormal3f(0.0, -1.0, 0.0);
	  glVertex3f(0.0 * size_2, 0.0 * size_2, 1.0 * size_2);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(1.0 * size_2, 0.0 * size_2, 1.0 * size_2);
    // y_2
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(1.0 * size_2, 1.0 * size_2, 0.0 * size_2);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0.0 * size_2, 1.0 * size_2, 0.0 * size_2);
    glNormal3f(0.0, 1.0, 0.0);
	  glVertex3f(0.0 * size_2, 1.0 * size_2, 1.0 * size_2);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(1.0 * size_2, 1.0 * size_2, 1.0 * size_2);
    // x_1
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0 * size_2, 0.0 * size_2, 0.0 * size_2);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0 * size_2, 1.0 * size_2, 0.0 * size_2);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0 * size_2, 1.0 * size_2, 1.0 * size_2);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0 * size_2, 0.0 * size_2, 1.0 * size_2);
    // x_2
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.0 * size_2, 0.0 * size_2, 0.0 * size_2);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.0 * size_2, 1.0 * size_2, 0.0 * size_2);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.0 * size_2, 1.0 * size_2, 1.0 * size_2);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.0 * size_2, 0.0 * size_2, 1.0 * size_2);
    // z_1
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(1.0 * size_2, 0.0 * size_2, 0.0 * size_2);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(1.0 * size_2, 1.0 * size_2, 0.0 * size_2);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.0 * size_2, 1.0 * size_2, 0.0 * size_2);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.0 * size_2, 0.0 * size_2, 0.0 * size_2);
    // z_2
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(1.0 * size_2, 0.0 * size_2, 1.0 * size_2);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(1.0 * size_2, 1.0 * size_2, 1.0 * size_2);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.0 * size_2, 1.0 * size_2, 1.0 * size_2);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.0 * size_2, 0.0 * size_2, 1.0 * size_2);
  glEnd();
}

void drawAxes(){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, 0.0, 1.0, 0.0); // eye, at, up
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINES);
	  glVertex3f(0.0f, 0.0f, -4.0f);
	  glVertex3f(0.0f, 0.0f, 4.0f);
  glEnd();
}

void drawAtPoint(){
  GLUquadric *quad;
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, 0.0, 1.0, 0.0); // eye, at, up
  glTranslatef(At.x, At.y, At.z);
  glColor3f(1.0, 0.0, 0.0);
  glutWireSphere(0.01, 100, 100);
}

void drawSphere(){

  GLUquadric *quad;
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, 0.0, 1.0, 0.0); // eye, at, up
  glTranslatef(light_position[0], light_position[1], light_position[2]);
  glColor3f(1.0, 1.0, 1.0);
  glutWireSphere(0.1, 50, 50);
}

// function to draw object
void drawObjects(GLvoid){
  // load object in 3D space
  angle -= 1.0f; // rotate velocity

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  /*--------- Obj 1 -------------*/
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  // GLfloat mat_specular_2[] = { 0.0, 1.0, 0.0, 1.0 };
  GLfloat color2[] = {1.0, 1.0, 0.0, 1.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color2);
  // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular_2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
  drawCule();

  /*--------- Obj 2 -------------*/
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  GLfloat mat_specular_1[] = { 0.0, 1.0, 0.0, 1.0 };
  GLfloat color1[] = {1.0, 1.0, 0.0, 1.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular_1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
  drawCule2();
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  
  drawAxes();
  drawAtPoint();
  drawSphere();
}

// render function
void renderScene(void){
  if(deltaMove) computePos(deltaMove);
  if(deltaAngle) computeDir(deltaAngle);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  drawObjects();
  glutSwapBuffers();
}

// create window - work with X system
void initGL(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Lighting");

  glShadeModel(GL_SMOOTH);

  // setup function call
  glutDisplayFunc(renderScene);
  glutIdleFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutSpecialFunc(pressKey);
  glutSpecialUpFunc(releaseKey);
  glutKeyboardFunc(keyword);

  glEnable(GL_DEPTH_TEST); // z-culling
  // glEnable(GL_CULL_FACE); // face-culling

  glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}
}

int main(int argc, char **argv){
  initGL(argc, argv);
  glutMainLoop();
  return 0;
}