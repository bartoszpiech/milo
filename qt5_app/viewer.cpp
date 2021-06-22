#include "viewer.h"
#include "mainwindow.h"

int *q0, *q1, *q2, *q3;

using namespace std;

Viewer::Viewer(QWidget* parent): QGLViewer(parent) {}

/*!
 * \brief Funkcja rysująca poszczególne kamiona manipulatora
 * \param size_x - szerokość w osi OX,
 * \param size_y - szerokość w osi OY,
 * \param size_z - długość ramienia,
 * \param r - parametr odpowiadający za kolor czerwony  <0-1>,
 * \param g - parametr odpowiadający za kolor zielony   <0-1>,
 * \param b - parametr odpowiadający za kolor niebieski <0-1>,
 */
void draw_link(GLfloat size_x, GLfloat size_y, GLfloat size_z,
			   GLfloat r, GLfloat g, GLfloat b) {
    glPushMatrix();
    glScalef(size_x, size_y, size_z);

	glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);    glVertex3f(0.5, -0.5, -0.5);
    glColor3f(r, g, b);    glVertex3f(0.5, 0.5, -0.5);
    glColor3f(r, g, b);    glVertex3f(-0.5, 0.5, -0.5);
    glColor3f(r, g, b);    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();


	glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    // right
	glNormal3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    // left
	glNormal3f(-1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    // top
	glNormal3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex3f(0.5,  0.5, 0.5);  //setGridIsDrawn();

    glVertex3f(0.5,  0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glPopMatrix();
}
/*
void draw_link(GLfloat size_x, GLfloat size_y, GLfloat size_z,
			   GLfloat r, GLfloat g, GLfloat b) {
    glPushMatrix();
    glScalef(size_x, size_y, size_z);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);    glVertex3f(0.5, -0.5, -0.5);
    glColor3f(0.0, 1.0, 0.0);    glVertex3f(0.5, 0.5, -0.5);
    glColor3f(0.0, 0.0, 1.0);    glVertex3f(-0.5, 0.5, -0.5);
    glColor3f(1.0, 1.0, 1.0);    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    // right
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    // left
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    // top
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5,  0.5, 0.5);
    glVertex3f(0.5,  0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // bottom
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glPopMatrix();
}
*/

void Viewer::draw() {

    //drawAxis();
	/*
	float link_0_x = 1.0, link_0_y = 0.5, link_0_z = 1.0;
	float link_1_x = 0.2, link_1_y = 0.2, link_1_z = 1.0;
	float link_2_x = 0.2, link_2_y = 0.2, link_2_z = 1.0;
	*/
	float link_0_x = 0.15, link_0_y = 0.15, link_0_z = 2.0;
	float link_1_x = 0.15, link_1_y = 0.15, link_1_z = 1.5;
	float link_2_x = 0.3, link_2_y = 0.3, link_2_z = 0.1;

	//float q1 = 0, q2 = 0, q3 = 0;

    //drawAxis();
    //glRotatef(90, 0.0, 1.0, 0.0);
    //glRotatef(-90, 1.0, 0.0, 0.0);
	/*
	*/
    glScalef(0.5, 0.5, 0.5);

	/*
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);    glVertex3f(-5, 0, 5);
    glColor3f(1.0, 1.0, 1.0);    glVertex3f(5, 0, 5);
    glColor3f(0.1, 0.1, 0.1);    glVertex3f(5, 0, -5);
    glColor3f(0.1, 0.1, 0.1);    glVertex3f(-5, 0, -5);
    glEnd();
	*/
    glRotatef((float)*q0, 0.0, 0, 1.0);
    glRotatef((float)*q1, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, link_0_z / 2);
    draw_link(link_0_x, link_0_y, link_0_z, 0.8, 0.0, 0.0);

    glTranslatef(0.0, 0.0, link_0_z / 2);
    glRotatef((float)*q2, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, link_1_z / 2);
    draw_link(link_1_x, link_1_y, link_1_z, 0.0, 0.8, 0.0);

    glTranslatef(0.0, 0.0, link_1_z / 2);
    glRotatef((float)*q3, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, link_2_z / 2);
    draw_link(link_2_x, link_2_y, link_2_z, 0.0, 0.0, 0.8);
	/*
	drawAxis();
    const float nbSteps = 200.0;
  glBegin(GL_QUAD_STRIP);
  for (int i=0; i<nbSteps; ++i)
    {
      const float ratio = i/nbSteps;
      const float angle = 21.0*ratio;
      const float c = cos(angle);
      const float s = sin(angle);
      const float r1 = 1.0 - 0.8f*ratio;
      const float r2 = 0.8f - 0.8f*ratio;
      const float alt = ratio - 0.5f;
      const float nor = 0.5f;
      const float up = sqrt(1.0-nor*nor);
      glColor3f(1.0-ratio, 0.2f , ratio);
      glNormal3f(nor*c, up, nor*s);
      glVertex3f(r1*c, alt, r1*s);
      glVertex3f(r2*c, alt+0.05f, r2*s);
    }
  glEnd();
  */

}

void Viewer::init() {
  // Restore previous viewer state.
  restoreStateFromFile();

   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);




  //GLfloat light[] = { 10.0, 1.0, 1.0, 0.0 };
  //glLightfv(GL_LIGHT0, GL_POSITION, light);

  /*
  setSceneRadius(3);
  camera()->lookAt(qglviewer::Vec(0,0,0));
  */
  camera()->setPosition(qglviewer::Vec(0,0,5));
  camera()->lookAt(qglviewer::Vec(0,0,0));

  setGridIsDrawn();

  startAnimation();

  // Opens help window
  // help();
}

void Viewer::animate() {
}


MainPageViewer::MainPageViewer(QWidget* parent): Viewer(parent) {}
void MainPageViewer::draw() {
    float link_0_x = 0.15, link_0_y = 0.15, link_0_z = 2.0;
    float link_1_x = 0.15, link_1_y = 0.15, link_1_z = 1.5;
    float link_2_x = 0.3, link_2_y = 0.3, link_2_z = 0.1;

    glScalef(0.5, 0.5, 0.5);

    glRotatef(q1, 0.0, 0, 1.0);
    glRotatef(q0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, link_0_z / 2);
    draw_link(link_0_x, link_0_y, link_0_z, 0.8, 0.0, 0.0);

    glTranslatef(0.0, 0.0, link_0_z / 2);
    glRotatef(q2, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, link_1_z / 2);
    draw_link(link_1_x, link_1_y, link_1_z, 0.0, 0.8, 0.0);

    glTranslatef(0.0, 0.0, link_1_z / 2);
    glRotatef(q3, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, link_2_z / 2);
    draw_link(link_2_x, link_2_y, link_2_z, 0.0, 0.0, 0.8);
}

void MainPageViewer::animate() {
    //this->q0++;
    this->q1++;
    this->q2++;
    this->q3++;
}
