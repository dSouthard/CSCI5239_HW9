//
//  Ex17viewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include "ex17viewer.h"

//
//  Constructor
//
Ex17viewer::Ex17viewer()
{
   //  Set window title
   setWindowTitle(tr("HW9: Advanced Shaders [D. Southard]"));

   //  Create new OpenGL widget
   ogl = new Ex17opengl;

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("Clouds");

   //  Center position
   speed = new QSlider(Qt::Horizontal);
   speed->setRange(0,100);

   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,4,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("Cloud Speed"),1,1);
   layout->addWidget(speed,1,2);
   layout->addWidget(quit,5,1);
   //  Manage resizing
   layout->setColumnStretch(0,50);
   layout->setColumnMinimumWidth(0,50);
   layout->setRowStretch(7,50);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(speed,SIGNAL(valueChanged(int)) , ogl,SLOT(setSpeed(int)));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));
}

