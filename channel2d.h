#ifndef CHANNEL2D_H
#define CHANNEL2D_H
#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>



namespace Ui {
class Channel2D;
}

class Channel2D : public QGLWidget
{

    
public:
    explicit Channel2D(QWidget *parent = 0);
    ~Channel2D();
    void wallplot();


    void timerEvent(QTimerEvent *event);
    int id1;
    double *pdata;
    double *pdata2;
    void InputManagement();
    void histoPlot2();
    void Key_Adjust(double *tmp);
    void R_Adjust(double *tmp);
    void L_Adjust(double *tmp);
    void D_Adjust(double *tmp);
    void Draw_point();
    void Draw_line();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *);
private:
    GLfloat translate, xRot, yRot, zRot,rMove,lMove,uMove,dMove;
    int num_p;
    double cnt_update;
};

#endif // CHANNEL2D_H
