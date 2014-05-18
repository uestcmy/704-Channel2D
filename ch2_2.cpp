#include "ch2_2.h"
#include "ui_ch2_2.h"
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include "QDebug"
#include <QtGui/QApplication>

#define SBC1 0
//#define SBC2  512
#define SBC2  32
#define SBC3 0
#define SBC4  256


#define YP 0.27
socklen_t size_chl3;
sockaddr_in addrSrv_chl3,addrrcv_chl3;
int sockser_chl3;


int pilot_3[1200][2] = {0};
char map1200_3[1800][16];
double data1_3[1800][2] = {0};//complex number real and image
double data2_3[1800][2] = {0};
double absdata_3[1800] = {0};

Ch2_2::Ch2_2(QWidget *parent) :
    QGLWidget(parent)
{
      translate = -6.0;
      xRot = yRot = zRot = 0.0;
      xRot += 90;
      yRot += 90;
      num_p = 300;
      InputManagement();

      size_chl3=sizeof(sockaddr_in);
      sockser_chl3=socket(AF_INET,SOCK_DGRAM,0);
      addrSrv_chl3.sin_addr.s_addr=htonl(INADDR_ANY);
      addrSrv_chl3.sin_family=AF_INET;
      addrSrv_chl3.sin_port=htons(7023);//server : receive port number 7023 c1cc 12
      bind(sockser_chl3,(sockaddr*)&addrSrv_chl3,sizeof(sockaddr));


      cnt_update = 0;
      id1 = startTimer(100);
}



Ch2_2::~Ch2_2()
{

}

void Ch2_2::InputManagement(){
    static double ttt[1000] = {0};
    static double ty1[1000] = {0};
    pdata = &ttt[0];
    pdata2 = &ty1[0];
}

void Ch2_2::initializeGL()
{
    glClearColor(0.8,0.8,0.8,0.9);//canvas
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


}
void Ch2_2::resizeGL(int w, int h)
{
    glViewport(-5, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //luPerspective(40.0, (GLfloat)w/(GLfloat)h, 2, 30.0);
    //gluPerspective(40,1.33, 2, 30.0);
    //glOrtho (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, -15.0, 15.0);
     //glFrustum (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 1,4, 20.0);
     glFrustum (-1.6 * ( GLfloat ) w / ( GLfloat ) h, 2.6* ( GLfloat ) w / ( GLfloat ) h, -1.2, 1.5,6, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Ⱦ
void Ch2_2::paintGL()
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

    /*
    glBegin(GL_LINE_STRIP); // 用折线绘
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,6},{-2,-1,6},{-2,-1,-4},{2,-1,-4}};
    for(int i = 0 ; i < 4 ; i++){
        L_Adjust(&point2[i+4][2]);
        D_Adjust(&point2[i+4][0]);
    }

    glColor4f(0,0,0,0.2);
    int crr = 6;
    int num_p = 50;
    double step = 10.0/num_p;
    for(int i = 0 ; i < num_p ; i++){
        glVertex3f(point2[crr][0]+2.3, point2[crr][1]+0.2  , point2[crr][2]);
        //point2[crr][0] = 0.3*sin(point2[crr][2])+(qrand() % 10)/100.0;
        point2[crr][2] += step;
    }
    glEnd();
*/


}
void  Ch2_2::Draw_line(){
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,6},{-2,-1,6},{-2,-1,-4},{2,-1,-4}};
    for(int i = 0 ; i < 4 ; i++){
        L_Adjust(&point2[i+4][2]);
        D_Adjust(&point2[i+4][0]);
    }
    glLineWidth(3);

    int crr = 6;
    double step = 10.0/num_p;
    double st = point2[crr][2];

    point2[crr][2]+=1.3;
    glBegin(GL_LINE_STRIP); // 用折线绘
    glColor4f(1,0,0,1);//red 600
    for(int i = 0 ; i < num_p-90 ; i++){
        glVertex3f((*(pdata+i)/5.0-YP)*2, point2[crr][1]+0.1  , point2[crr][2]);
        //point2[crr][0] = 0.3*sin(point2[crr][2])+(qrand() % 10)/100.0;
        point2[crr][2] += step;
    }
    glEnd();


    point2[crr][2] = st;
    point2[crr][2]+=1.3;
    glBegin(GL_LINE_STRIP); // 用折线绘
    glColor4f(0,0,1,1);//blue 0
    for(int i = 0 ; i < num_p-90 ; i++){
        glVertex3f((*(pdata2+i)/5.0-YP)*2, point2[crr][1]+0.1  , point2[crr][2]);
        //point2[crr][0] = 0.3*sin(point2[crr][2])+(qrand() % 10)/100.0;
        point2[crr][2] += step;
    }
    glEnd();
}
void  Ch2_2::Draw_point(){

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

void  Ch2_2::R_Adjust(double *tmp){
    *tmp -= rMove;
}
void  Ch2_2::L_Adjust(double *tmp){
    *tmp += 0.4;
}
void  Ch2_2::D_Adjust(double *tmp){
    *tmp -= 0.3;
}
void Ch2_2::wallplot(){
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,6},{-2,-1,6},{-2,-1,-4},{2,-1,-4}};
    for(int i = 0 ; i < 4 ; i++){
        R_Adjust(&point2[i+4][2]);
        L_Adjust(&point2[i+4][2]);
        D_Adjust(&point2[i+4][0]);
    }

    glColor4f(1, 1, 1,1);
    glVertex3f(point2[4][0], point2[4][1], point2[4][2]-1.7);
    glVertex3f(point2[5][0]+2, point2[5][1], point2[5][2]-1.7);
    glVertex3f(point2[6][0]+2, point2[6][1], point2[6][2]+1.07);
    glVertex3f(point2[7][0], point2[7][1], point2[7][2]+1.07);
    glEnd();
    /*axis*/
    glLineWidth(2);
    //glBegin(GL_LINE_STRIP);
    glBegin(GL_LINE_LOOP);

   // glColor4f(1, 143.0/255.0, 50.0/255.0,1);//orange 0
     glColor4f(0,0,0,1);//orange 0
    glVertex3f(-0.3,-1+0.1,4.65); // up left
    glVertex3f(-0.3,-1+0.1,-2.5);// left,down
    glVertex3f(1.7,-1+0.1,-2.5);//left down
    glVertex3f(1.7,-1+0.1,4.65);//left down
    glEnd();


    for( double i = 0 ; i < 1.5 ; i +=0.225 ){
        glLineWidth(1);
        glBegin(GL_LINE_STRIP);
   // glBegin(GL_LINE_LOOP);
   // glColor4f(1, 143.0/255.0, 50.0/255.0,1);//orange 0
        glColor4f(0,0,0,0.7);//orange 0
        glVertex3f(0+i,-1+0.1,4.65); // up left
        glVertex3f(0+i,-1+0.1,-2.5);// left,down
        glEnd();
    }
    glLineWidth(2);
    glColor4f(1,0,0,1);//orange 0
    renderText(0.3-0.1,-1+0.1,-3,"0dB");
    renderText(0.3+0.225-0.1,-1+0.1,-3,"10dB");
    renderText(0.3+0.45-0.1,-1+0.1,-3,"20dB");
    renderText(0.3+0.675-0.1,-1+0.1,-3,"30dB");
    renderText(0.3+0.9-0.1,-1+0.1,-3,"40dB");



    //legend
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glColor4f(0,0,0,1);
    glVertex3f(point2[4][0]-1.5, point2[4][1]+0.21, point2[4][2]-2);
    glVertex3f(point2[5][0]+2.1, point2[5][1]+0.21, point2[5][2]-2);
    glVertex3f(point2[6][0]+2.1, point2[6][1]+0.21, point2[6][2]+7);
    glVertex3f(point2[7][0]-1.5, point2[7][1]+0.21, point2[7][2]+7);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1, 1, 1,1);
    glVertex3f(point2[4][0]-1.5, point2[4][1]+0.2, point2[4][2]-2);
    glVertex3f(point2[5][0]+2.1, point2[5][1]+0.2, point2[5][2]-2);
    glVertex3f(point2[6][0]+2.1, point2[6][1]+0.2, point2[6][2]+7);
    glVertex3f(point2[7][0]-1.5, point2[7][1]+0.2, point2[7][2]+7);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
// glBegin(GL_LINE_LOOP);
// glColor4f(1, 143.0/255.0, 50.0/255.0,1);//orange 0
    glColor4f(1,0,0,1);//orange 0
    glVertex3f(point2[5][0]+2.2, point2[5][1]+0.21, point2[5][2]-2.6);
    glVertex3f(point2[6][0]+2.2, point2[6][1]+0.21, point2[6][2]+7.05);
    glEnd();
    renderText(point2[6][0]+2.17, point2[6][1]+0.21, point2[6][2]+7.55,"Rx 2");

    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
// glBegin(GL_LINE_LOOP);
// glColor4f(1, 143.0/255.0, 50.0/255.0,1);//orange 0
    glColor4f(0,0,1,1);//blue 0
    glVertex3f(point2[5][0]+2.4, point2[5][1]+0.21, point2[5][2]-2.6);
    glVertex3f(point2[6][0]+2.4, point2[6][1]+0.21, point2[6][2]+7.05);
    glEnd();
    renderText(point2[6][0]+2.37, point2[6][1]+0.21, point2[6][2]+7.55,"Rx 1");

}



void Ch2_2::keyPressEvent(QKeyEvent *event)
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

void Ch2_2::timerEvent(QTimerEvent *event){
    glBegin(GL_QUADS);

    glEnable (GL_LINE_SMOOTH );
    glHint (GL_POLYGON_SMOOTH , GL_NICEST);

    //histoPlot1();
    histoPlot2();
    //histoPlot3();
    //histoPlot4();
    //floor
    wallplot();

   char buff[14404*3+10];
    recvfrom(sockser_chl3,&buff,14404*3+10,0,(struct sockaddr *)&addrrcv_chl3,(socklen_t*)&size_chl3);//port :7005

    //qDebug() << "Counter is " << cnt++ << endl;

   //

    for( int i = 0 ; i < 2455 ; i ++){
       int position = i * 6;
       char tmp;
       //swap
       tmp = buff[position];
       buff[position] = buff[position+3];
       buff[position+3] = tmp;
       //swap
       position ++;
       tmp = buff[position];
       buff[position] = buff[position+3];
       buff[position+3] = tmp;
    }//for

    //qDebug() << buff << endl;
    int position = 12; // avoid the header a0aa 3c20 cccc 30
    for( int i = 0 ; i < 1200 ; i++){
        for( int j = 0 ; j <8 ;) {
            map1200_3[i][j++] = buff[position++];
            map1200_3[i][j++] = buff[position++];
            position++;//avoid the comma
       }//for j
    }//for i
    for( int i = 0 ; i < 1200 ; i++){
        data1_3[i][0]=hex2int(map1200_3[i][0],map1200_3[i][1],map1200_3[i][2],map1200_3[i][3]);
        data1_3[i][1]=hex2int(map1200_3[i][4],map1200_3[i][5],map1200_3[i][6],map1200_3[i][7]);
        absdata_3[i] = sqrt(data1_3[i][0]*data1_3[i][0]+data1_3[i][1]*data1_3[i][1]);
        //qDebug() << data1_3[i][0] << data1_3[i][1] <<data2_3[i][0] <<data2_3[i][1] <<endl;
    }//for i




    for( int i = num_p-1 ; i >= 1 ; i-- ){
        *(pdata+i) = *( pdata+i-1);
    }
    //*(pdata) = 2*sin(cnt_update);
    if(log10(absdata_3[SBC2]) < 0){
           *(pdata) = absdata_3[SBC2]/300.0;
     }
     else{

        double aver = 0;
        for( int i = 0 ; i < 8 ; i++ ){
            aver += absdata_3[SBC2+i];
        }
        aver /= 8;
        *(pdata) = log10(aver);
         //  *(pdata) = log10(absdata_3[SBC2]);

     }


     for( int i = num_p-1 ; i >= 1 ; i-- ){
         *(pdata2+i) = *( pdata2+i-1);
     }
     //*(pdata) = 2*sin(cnt_update);
      if(log10(absdata_3[SBC1]) < 0){
            *(pdata2) = absdata_3[SBC1]/300.0;
      }
      else{
            //*(pdata2) = log10(absdata_3[SBC1]);
           double aver = 0;
           for( int i = 0 ; i < 8 ; i++ ){
               aver += absdata_3[SBC1+i];
           }
           aver /= 8;
           *(pdata2) = log10(aver);
       //     double aver = 0;


           qDebug() << " absdata 0 :  " << *(pdata) << "   "<< *(pdata2);


      }
       cnt_update++;
    if(cnt_update >= 100){
        cnt_update -=100;
    }

    updateGL();
    //qDebug()<< "timer event in mygl2 Class!" << endl;
}

void Ch2_2::histoPlot2(){
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

int Ch2_2::hex2int(char a,char b,char c,char d){
    /*
      *   eg. ff to 1111 1111
      */

    //qDebug() << "abcd is : " << a << b << c << d << endl;
    int deca = 0,decb = 0,decc = 0,decd = 0;
    if( a >= 'a' && a <= 'f' ){
        deca  = 10 + a -'a';
    }else{
        deca = a - '0';
    }//else

    if( b >= 'a' && b <= 'f' ){
       decb  = 10 + b -'a';
    }else{
        decb = b - '0';
    }//else

    if( c >= 'a' && c <= 'f' ){
        decc  = 10 + c -'a';
    }else{
        decc = c - '0';
    }//else

    if( d >= 'a' && d <= 'f' ){
       decd  = 10 + d -'a';
    }else{
        decd = d - '0';
    }//else

  //qDebug() << "dec abcd is : " << deca << decb << decc << decd << endl;

   int num[16] = {0};
   num[12] = deca % 2;
   deca /= 2;
   num[13] = deca % 2;
   deca /= 2;
   num[14] = deca % 2;
   deca /= 2;
   num[15] = deca % 2;
   deca /= 2;

   num[8] = decb % 2;
   decb /= 2;
   num[9] = decb % 2;
   decb /= 2;
   num[10] = decb % 2;
   decb /= 2;
   num[11] = decb % 2;
   decb /= 2;

   num[4] = decc % 2;
   decc /= 2;
   num[5] = decc % 2;
   decc /= 2;
   num[6] = decc % 2;
   decc /= 2;
   num[7] = decc % 2;
   decc /= 2;

   num[0] = decd % 2;
   decd /= 2;
   num[1] = decd % 2;
   decd /= 2;
   num[2] = decd % 2;
   decd /= 2;
   num[3] = decd % 2;
   decd /= 2;

   int flag = 1;
   if(num[15] == 1){
        flag = -1;
        for( int i = 0 ; i < 15 ; i++ ){
            num[i] = 1 - num[i];
        }
        num[0] ++;
        for( int i = 0 ; i <15 ; i++ ){
            if( num[i] > 1){
                num[i] = 0;
                num[i+1]++;
            }//if
        }
   }
   int res = 0;
   int base = 1;
   for( int i = 0 ; i < 15 ; i++ ){
       res += num[i] *base;
       base *= 2;
   }


   //for i
  // qDebug() << "16 bit is : "  << num[15] << num[14] << num[13] << num[12] << num[11] << num[10] << num[9] << num[8]<< num[7] << num[6]<< num[5] << num[4]<< num[3] << num[2]<< num[1] << num[0] << endl;
   res *= flag;
   //qDebug() << res << endl;
    return res;
}
