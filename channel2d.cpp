#include "channel2d.h"
#include "ui_channel2d.h"
#include <math.h>
Channel2D::Channel2D(QWidget *parent) :
    QGLWidget(parent)
{
      translate = -6.0;
      xRot = yRot = zRot = 0.0;
      xRot += 90;
      yRot += 90;
      num_p = 300;
      InputManagement();
      cnt_update = 0;
      id1 = startTimer(50);
}



Channel2D::~Channel2D()
{

}

void Channel2D::InputManagement(){
    static double ttt[1000] = {0};
    pdata = &ttt[0];
}

void Channel2D::initializeGL()
{
    glClearColor(0.8,0.8,0.8,0);//canvas
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


}
void Channel2D::resizeGL(int w, int h)
{
    glViewport(-5, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //luPerspective(40.0, (GLfloat)w/(GLfloat)h, 2, 30.0);
    //gluPerspective(40,1.33, 2, 30.0);
    //glOrtho (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, -15.0, 15.0);
     glFrustum (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 1,4, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Ⱦ
void Channel2D::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glTranslatef(0.0, 0.0, translate);// translate is included in <QKeyEvent>
    glTranslatef(0.0, -0.5, 0.3);// translate is included in <QKeyEvent>

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
    glBegin(GL_QUADS);

    glEnable (GL_LINE_SMOOTH );
    glHint (GL_POLYGON_SMOOTH , GL_NICEST);

    //histoPlot1();
    //histoPlot2();
    //histoPlot3();
    //histoPlot4();
    //floor
    wallplot();
    glEnd();



    //Draw_point();
    Draw_line();
}
void  Channel2D::Draw_line(){
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,6},{-2,-1,6},{-2,-1,-4},{2,-1,-4}};
    for(int i = 0 ; i < 4 ; i++){
        L_Adjust(&point2[i+4][2]);
        D_Adjust(&point2[i+4][0]);
    }
    glLineWidth(3);

    double step = 10.0/num_p;
    int crr = 6;

    glBegin(GL_LINE_STRIP); // 用折线绘
    glColor4f(1, 0, 0,1);
    for(int i = 0 ; i < num_p ; i++){
        glVertex3f(*(pdata+i)/10.0, point2[crr][1]+0.1  , point2[crr][2]);
        //point2[crr][0] = 0.3*sin(point2[crr][2])+(qrand() % 10)/100.0;
        point2[crr][2] += step;
    }
    glEnd();
}
void  Channel2D::Draw_point(){

    glColor4f(1, 0, 0,1);
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,6},{-2,-1,6},{-2,-1,-4},{2,-1,-4}};
    double del = 0.1;
    for(int i = 0 ; i < 4 ; i++){
        L_Adjust(&point2[i+4][2]);
        D_Adjust(&point2[i+4][0]);
    }

    glBegin(GL_QUADS);
    glColor4f(1, 0, 0,1);
    //double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,6},{-2,-1,6},{-2,-1,-4},{2,-1,-4}};
    //double del = 0.1;

    int crr = 5;
    glVertex3f(point2[crr][0], point2[crr][1]+0.01, point2[crr][2]);
    glVertex3f(point2[crr][0], point2[crr][1]+0.01, point2[crr][2]-del);
    glVertex3f(point2[crr][0]+del, point2[crr][1]+0.01, point2[crr][2]-del);
    glVertex3f(point2[crr][0]+del, point2[crr][1]+0.01, point2[crr][2]);
    glEnd();

    int num_p = 50;
    double step = 10.0/num_p;
    crr = 6;
    for(int i = 0 ; i <= num_p ; i++){
        glBegin(GL_QUADS);
        glColor4f(1, 0, 0,1);
        glVertex3f(point2[crr][0], point2[crr][1]+0.01, point2[crr][2]);
        glVertex3f(point2[crr][0], point2[crr][1]+0.01, point2[crr][2]-del);
        glVertex3f(point2[crr][0]+del, point2[crr][1]+0.01, point2[crr][2]-del);
        glVertex3f(point2[crr][0]+del, point2[crr][1]+0.01, point2[crr][2]);
        point2[crr][2] += step;
        glEnd();
    }
}

void  Channel2D::R_Adjust(double *tmp){
    *tmp -= rMove;
}
void  Channel2D::L_Adjust(double *tmp){
    *tmp += 0.4;
}
void  Channel2D::D_Adjust(double *tmp){
    *tmp -= 0.3;
}
void Channel2D::wallplot(){
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,6},{-2,-1,6},{-2,-1,-4},{2,-1,-4}};
    for(int i = 0 ; i < 4 ; i++){
        R_Adjust(&point2[i+4][2]);
        L_Adjust(&point2[i+4][2]);
        D_Adjust(&point2[i+4][0]);
    }

    glColor4f(0, 0, 0,0.2);
    glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
    glVertex3f(point2[5][0], point2[5][1], point2[5][2]);
    glVertex3f(point2[6][0], point2[6][1], point2[6][2]);
    glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
}



void Channel2D::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up :
        xRot += 10;
        break;
    case Qt::Key_Left :
        yRot += 10;
        break;
    case Qt::Key_Right :
        zRot += 10;
        break;
    case Qt::Key_Down :
        xRot -= 10;
        break;
    case Qt::Key_L :
        rMove += 0.1;
        break;
    case Qt::Key_H :
        lMove += 0.1;
        break;
    }
    updateGL();
    QGLWidget::keyPressEvent(event);
}

void Channel2D::timerEvent(QTimerEvent *event){
    glBegin(GL_QUADS);

    glEnable (GL_LINE_SMOOTH );
    glHint (GL_POLYGON_SMOOTH , GL_NICEST);

    //histoPlot1();
    histoPlot2();
    //histoPlot3();
    //histoPlot4();
    //floor
    wallplot();
    glEnd();


    for( int i = num_p-1 ; i >= 1 ; i-- ){
        *(pdata+i) = *( pdata+i-1);
    }
    *(pdata) = 2*sin(cnt_update);
    cnt_update++;
    if(cnt_update >= 100){
        cnt_update -=100;
    }

    updateGL();
    //qDebug()<< "timer event in mygl2 Class!" << endl;
}

void Channel2D::histoPlot2(){
    double point[8][3] = {{0.5-0.05,1,-2},{0.5-0.05,1,-3+0.05},{-0.5,1,-3+0.05},{-0.5,1,-2},
                          {0.5-0.05,-1,-2},{0.5-0.05,-1,-3+0.05},{-0.5,-1,-3+0.05},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};

    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
        point[i][1] += (delta[rand1]/10);
        if( point[i][1] > 1){
            point[i][1] -= 0.1;
        }
        if(point[i][1] < 0 ){
            point[i][1] += 0.1;
        }
    }

    for( int i = 0 ; i < 8 ; i++ ){
        point[i][2] += 2;

    }
    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(0.698039,0.227451,0.937255);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(0.698039,0.227451,0.937255);
      //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(0.507843, 0.13333, 0.745098);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(0.507843, 0.13333, 0.745098);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(0.603922, 0.196078, 0.803922);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(0.603922, 0.196078, 0.803922);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}
