#ifndef Ch2_1_H
#define Ch2_1_H
#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>



namespace Ui {
class Ch2_1;
}

class Ch2_1 : public QGLWidget
{


public:
    explicit Ch2_1(QWidget *parent = 0);
    ~Ch2_1();
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
    int hex2int(char a, char b, char c, char d);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *);
private:
    GLfloat translate, xRot, yRot, zRot,rMove,lMove,uMove,dMove;
    int num_p;
    int cnt;
    double cnt_update;
};

#endif // Ch2_1_H
