#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent):
QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

}

void GLWidget::initializeGL()
{
    this->initializeOpenGLFunctions();
    /*
    glClearColor(0.2, 0.2, 0.2, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    */
}
void paint_link(GLfloat link_w, GLfloat link_h, GLfloat r, GLfloat g, GLfloat b) {
    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex2f(-link_w/2, link_h/2);
    glVertex2f(link_w/2, link_h/2);
    glVertex2f(link_w/2, -link_h/2);
    glVertex2f(-link_w/2, -link_h/2);
    glEnd();
}
void GLWidget::paintGL()
{

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    //glTexCoord2f(0.0f, 0.1f);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(0.0, 1.0, 1.0, 1.0);

    paint_link(link_one[0], link_one[1], 1.0f, 0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-link_two[0]/2, link_one[1]/2, 0.0);
    glRotatef(0.0, 1.0, 1.0, 1.0);

    paint_link(link_two[0], link_two[1], 0.0f, 0.0f, 1.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-link_two[0] - link_three[0]/2, link_one[1]/2, 0.0);
    glRotatef(0.0, 1.0, 1.0, 1.0);

    paint_link(link_three[0], link_three[1], 0.0f, 1.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // rysowanie pierwszego jointa
    glPushMatrix();
    glTranslatef(0, -link_one[1]/2, 0.0);
    GLfloat prev_x = joint[0];
    GLfloat prev_y = joint[1] - joint[2];
    const GLfloat angle = M_PI * 2.0f / joint_steps;
    for (int i = 0; i <= joint_steps; i++) {
        float new_x = joint[2] * sin(angle * i);
        float new_y = -joint[2] * cos(angle * i);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(joint[0], joint[1]);
        glVertex2f(prev_x, prev_y);
        glVertex2f(new_x, new_y);
        glEnd();
        prev_x = new_x;
        prev_y = new_y;
    }
    glPopMatrix();

    // rysowanie drugiego jointa
    glPushMatrix();
    glTranslatef(0, link_one[1]/2, 0.0);
    prev_x = joint[0];
    prev_y = joint[1] - joint[2];
    for (int i = 0; i <= joint_steps; i++) {
        float new_x = joint[2] * sin(angle * i);
        float new_y = -joint[2] * cos(angle * i);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(joint[0], joint[1]);
        glVertex2f(prev_x, prev_y);
        glVertex2f(new_x, new_y);
        glEnd();
        prev_x = new_x;
        prev_y = new_y;
    }
    glPopMatrix();

    glFlush();
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}
