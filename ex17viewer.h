#ifndef EX17V_H
#define EX17V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "ex17opengl.h"

class Ex17viewer : public QWidget
{
Q_OBJECT
private:
   QSlider*     speed;
   QSlider*     trans;
   Ex17opengl*  ogl;
private slots:
public:
    Ex17viewer();
};

#endif
