//
//  OpenGL widget
//
#include "ex17opengl.h"
#include <QtOpenGL>
#include <QMessageBox>
#include "Cube.h"
#include <math.h>
#define Cos(th) cos(M_PI/180*(th))
#define Sin(th) sin(M_PI/180*(th))


//
//  Constructor
//
Ex17opengl::Ex17opengl(QWidget* parent)
    : QGLWidget(parent)
{
   speed = 1;
   trans = 0.5;
   init  = false;
   asp = 1;
   dim = 3;
   fov = 55;
}

//
//  Set projection
//
void Ex17opengl::setTrans(int value)
{
   trans = value;
   //  Request redisplay
   updateGL();
}

//
//  Set object
//
void Ex17opengl::setSpeed(int value)
{
   speed = value;
   //  Request redisplay
   updateGL();
}

//
//  Initialize
//
void Ex17opengl::initializeGL()
{
   if (init) return;
   init = true;

   //  Load shaders
   Shader(shader,"",":/ex17.frag");

   // Cube
   Cube* cube = new Cube();
   cube->scale(5,5,5);

   //  Set object
   obj = cube;

   //  Start 100 fps timer connected to updateGL
   timer.setInterval(10);
   connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
   timer.start();
   time.start();
}

//
//  Set projection when window is resized
//
void Ex17opengl::resizeGL(int width, int height)
{
   //  Window aspect ration
   asp = height ? width / (float)height : 1;
   //  Viewport is whole screen
   glViewport(0,0,width,height);
   //  Set projection
   Projection();
}

//
//  Draw the window
//
void Ex17opengl::paintGL()
{
   //  Wall time (seconds)
   float t = 0.001*time.elapsed();
   float speedX = (float)0.01*speed;
   
   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   //  Set view
   glLoadIdentity();

   //  Apply shader
   shader.bind();
   QVector2D resolution(width(), height());
   shader.setUniformValue("resolution",resolution);
   shader.setUniformValue("time",t);
   shader.setUniformValue("speed",speedX);
   
   //  Draw scene
   glPushMatrix();
   obj->display();
   glPopMatrix();

   //  Release shader
   shader.release();
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);
   
}

//
//  Throw a fatal error and die
//
void Ex17opengl::Fatal(QString message)
{
   QMessageBox::critical(this,"Ex17opengl",message);
   QApplication::quit();
}

//
//  Set OpenGL projection
//
void Ex17opengl::Projection()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (fov)
   {
      float zmin = dim/4;
      float zmax = 4*dim;
      float ydim = zmin*tan(fov*M_PI/360);
      float xdim = ydim*asp;
      glFrustum(-xdim,+xdim,-ydim,+ydim,zmin,zmax);
   }
   else
      glOrtho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}



//
//  Load shader
//
void Ex17opengl::Shader(QGLShaderProgram& shader,QString vert,QString frag)
{
   //  Vertex shader
   if (vert.length() && !shader.addShaderFromSourceFile(QGLShader::Vertex,vert))
      Fatal("Error compiling "+vert+"\n"+shader.log());
   //  Fragment shader
   if (frag.length() && !shader.addShaderFromSourceFile(QGLShader::Fragment,frag))
      Fatal("Error compiling "+frag+"\n"+shader.log());
   //  Link
   if (!shader.link())
      Fatal("Error linking shader\n"+shader.log());
}
