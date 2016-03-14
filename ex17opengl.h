//
//  OpenGL Ex17opengl Widget
//

#ifndef EX17OPENGL_H
#define EX17OPENGL_H

#include <QtOpenGL>
#include <QString>
#include <QVector>
#include "Object.h"

class Ex17opengl : public QGLWidget
{
Q_OBJECT
private:
   bool    init;      //  Initialized
   float   speed;
   float   trans;
   int     fov;       //  Field of view
   double  dim;       //  Display size
   double  asp;       //  Sceen aspect ratio
   Object* obj;       //  Object
   QGLShaderProgram shader; //  Shaders
   QTimer           timer;     //  Timer for animations
   QElapsedTimer    time;      //  Track elapsed time
public:
   Ex17opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
    void setSpeed(int value);                  //  Slot to light position
    void setTrans(int value);                   //  Slot to light elevation (%)
signals:
protected:
    void initializeGL();                   //  Initialize widget
    void resizeGL(int width, int height);  //  Resize widget
    void paintGL();                        //  Draw widget
private:
   void Fatal(QString message);            //  Error handler
   void Projection();                      //  Update projection
   void Shader(QGLShaderProgram& shader,QString vert,QString frag);  //  Create shader
};

#endif
