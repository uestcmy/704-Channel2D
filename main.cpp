#include <QApplication>
#include <ch2_1.h>
#include <ch2_2.h>
#include <qfile.h>

#include <QDebug>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <GL/glut.h>
//#define SHOW
#define DEBUG84
#define CHANNEL
#define LEN 9000
#define LENGTH_OF_CORE 84
//#define SOCKET
int flag = 199;

void search_core_data(char *buff);
void search_core_data2(char *buff);
int continueflag = 0;
int rest_num_comma = 0;
char out[LEN*5];
int outposition = 0;
int core_data_state = 0;//initail

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    qDebug() << "This is in the MAIN class,the flag is : "<< flag << endl;





     QFile file("./dataout/data2.txt");
     if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
         qDebug() << file.errorString();
     //char str[] = "Hello world!\n";


/*
     MultiWindow mw1;
     mw1.resize(600,500);
     mw1.show();
     mw1.setWindowTitle("Channel from port:7005 7006");
*/
/*

     ChannelH11 w1;
     w1.resize(800,600);
     w1.show();
     w1.setWindowTitle("Channel Gain");

     Channel2D w21;
     w21.resize(800,400);
     w21.show();
     w21.setWindowTitle("Channel 2D");

     Ch2_1 w22;
     w22.resize(800,400);
     w22.show();
     w22.setWindowTitle("Subcarrier 1");

     Ch2_2 w23;
     w23.resize(800,400);
     w23.show();
     w23.setWindowTitle("Subcarrier 2");
*/
     Ch2_2 w23;
     w23.setGeometry(5,300,600,300);
     w23.show();
     w23.setWindowTitle("UE 1 Rx1,2 sub0 sub 32 port:7023");
    return app.exec();

}



void search_core_data(  char* buff ){
    int i;
    int find = 0;//consider that there is no header?
    for( i = 0 ; i < LEN - 10 ; i++ ){
        //search the header of the core-frame
        //if( buff[i] == 'a' && buff[i+1] == 'a' && buff[i+2] == ',' && buff[i+3] == 'a' && buff[i+4] == '0'&& buff[i+5] == ','  && buff[i+6] == '2' && buff[i+7] == '0' && buff[i+8] == ',' && buff[i+9] == '3' && buff[i+10] == 'c'){ // && buff[i+6] == '2' && buff[i+7] == '0' && buff[i+8] == ',' && buff[i+9] == '3' && buff[i+10] == 'c'

#ifdef DEBUG84
        if(buff[i] == 'a' && buff[i+1] == 'a' && buff[i+2] == ',' && buff[i+3] == 'a' && buff[i+4] == '0' && buff[i+5] == ',' && buff[i+6] == '2' && buff[i+7] == '8' && buff[i+8] == ',' && buff[i+9] == '4' && buff[i+10] == '0'){
#endif

#ifdef DEBUG14404

        if(buff[i] == 'a' && buff[i+1] == 'a' && buff[i+2] == ',' && buff[i+3] == 'a' && buff[i+4] == '0' && buff[i+5] == ',' && buff[i+6] == '2' && buff[i+7] == '0' && buff[i+8] == ',' && buff[i+9] == '3' && buff[i+10] == 'c'){
#endif
            //qDebug() << buff <<endl;//the length is LEN ,  very long ...
            //qDebug() << "-------------------------------------------------------------------------------------------------" << endl;
            find = 1;
            break;
        }
    }//for
    if( find == 0 ){
        return ;
    }
    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;
    outposition = 0;
    for( int j = i ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if
        if( buff[j] ==',' && buff[j+2] == ',' ){

        }//if
        if( buff[j] == ',' ){
            cnt_comma ++;
        }

        if( cnt_comma == LENGTH_OF_CORE ){
           rest_num_comma = 0;
           continueflag = 0;
           break;
        }
        else if( j == LEN){
            rest_num_comma = LENGTH_OF_CORE - cnt_comma;
            continueflag = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<"FIRST :" <<bottle <<endl;
    strcat(out,bottle);
}

void search_core_data2(  char* buff ){ // continue to send the data

    char bottle[LEN] = {0};
    int cnt = 0;
    int cnt_comma = 0;

    for( int j = 0 ;  ; j++){
        if( buff[j] != '-' && buff[j] != '\n'){
            bottle[cnt++]  = buff[j];
            //out[outposition++] = buff[j];
        }//if
        if( buff[j] == ',' ){
            cnt_comma ++;
            rest_num_comma --;
        }
        if( rest_num_comma == 0){// the end of the later frame
            continueflag = 0;
            //qDebug() << "rest is zero."<<endl;
            break;
        }
        else if( rest_num_comma > 0 && j == LEN){
            continueflag = 1; //there is still some frames in the later buffer
            break;
        }
    }//for j
    //qDebug() <<" (next)" <<bottle ;
    strcat(out,bottle);
}

