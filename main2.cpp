#include <iostream>
#include <string>
#include <math.h>
#include "laclase.h"

const float G=(6.67)*(pow(10,-11.0));
const float Mt=(5.9736)*(pow(10,24.0));
const float Rt=(6.378)*(pow(10,6.0));
const float R=287.06;
const float L=(6.5)*(pow(10,-3.0));
const float go=9.81;
const float To=288.15;
const float Po=101325;


//Prototipos de funciones
float mf(float,float,float,float); //mass fuel
float mc(float,float); //masa cohete
float E(float,float); //Empuje de el cohete en funcion de mass fuel 
float g(float); //gravedad 
float Fa(float,float,float,float); //Fuerza de rozamiento 
float rho(float); //Densidad del aire en funcion de la altura
float Ft(float,float,float,float); //FUERZA TOTAL
float at(float,float); //ACETELACION DE EL COHETE



/*
NOTACION:
LLamare v(t)=y'(t)
Llamare at(t)=y''(t)
*/



//Funcion principal
int main(){
Naves cohete1,cohete2,cohete3;
//Ingresamos todos los atributos de cada cohete:
cohete1.Eo=(3)*(pow(10,7.0));
cohete1.TSFC=(3.248)*(pow(10,-4.0));
cohete1.CD=61.27;
cohete1.A=201.06;
cohete1.mo=(1.1)*(pow(10,5.0));
cohete1.mfo=(1.5)*(pow(10,6.0));

cohete2.Eo=(2.7)*(pow(10,7.0));
cohete2.TSFC=(2.248)*(pow(10,-4.0));
cohete2.CD=61.27;
cohete2.A=201.06;
cohete2.mo=(1.1)*(pow(10,5.0));
cohete2.mfo=(1.5)*(pow(10,6.0));

cohete3.Eo=(2.5)*(pow(10,7.0));
cohete3.TSFC=(2.248)*(pow(10,-4.0));
cohete3.CD=70.25;
cohete3.A=215.00;
cohete3.mo=(1.8)*(pow(10,5.0));
cohete3.mfo=(2.1)*(pow(10,6.0));
///


/////////////////////////////////
/////////////////////////////////
//EL SIGUIENTE CODIGO ES PARA COHETE 1
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////


/////////Inicio de el metodo de Euler para encontrar posicion y velocidad en funcion de el tiempo:
int n=1000;
float t=0;
float dt=(30*60)/(n);
int yini=0; //sera una variable auxiliar para guardar el valor de y.
float tc1f;  //Tiempo que le toma al cohete 1 regresar a el suelo
float tc1hm; //Tiempo que le toma al cohete 1 alcanzar la altura maxima
float yc1max; //Altura maxima de el cohete 1
FILE* elfi;
elfi=fopen("datos1.txt","wt");
fprintf(elfi,"%.3f,%.3f,%.3f \n",t,cohete1.y,cohete1.v);
for(int i=0;i<n && cohete1.y>=0;i++)
{
yini=cohete1.y;
cohete1.y=cohete1.y+(dt)*(cohete1.v);
cohete1.v=cohete1.v+(dt)*(at(Ft(E(mf(i*dt,cohete1.TSFC,cohete1.mfo,cohete1.Eo),cohete1.Eo),Fa(yini,cohete1.CD,cohete1.A,cohete1.v),mc(cohete1.mo,mf(i*dt,cohete1.TSFC,cohete1.mfo,cohete1.Eo)),g(yini)),mc(cohete1.mo,mf(i*dt,cohete1.TSFC,cohete1.mfo,cohete1.Eo))));

fprintf(elfi,"%.3f,%.3f,%.3f \n",i*dt,cohete1.y,cohete1.v);
tc1f=i*dt;
}
fclose(elfi);


//////////CALCULO DE LA YMAX
cohete1.y=0;
cohete1.v=0;
int band1=0;
for(int i=0;i<n && band1==0;i++)
{
yini=cohete1.y;
cohete1.y=cohete1.y+(dt)*(cohete1.v);
cohete1.v=cohete1.v+(dt)*(at(Ft(E(mf(i*dt,cohete1.TSFC,cohete1.mfo,cohete1.Eo),cohete1.Eo),Fa(yini,cohete1.CD,cohete1.A,cohete1.v),mc(cohete1.mo,mf(i*dt,cohete1.TSFC,cohete1.mfo,cohete1.Eo)),g(yini)),mc(cohete1.mo,mf(i*dt,cohete1.TSFC,cohete1.mfo,cohete1.Eo))));

if(cohete1.v<0){
    band1=1;
    yc1max=yini;
    tc1hm=i*dt;

}

}

float tco=(cohete1.mfo)/((cohete1.TSFC)*(cohete1.Eo)); //Tiempo en el cual se le acaba el combustible

std::cout<<"El cohete 1 alcanzo la altura Ymax= "<<yc1max<<" m  en el tiempo thmax= "<<tc1hm<<" s.  Y regreso de nuevo al suelo en el tiempo tf= "<<tc1f<<" s.   Y se le acabo el combustible en el tiempo tof= "<<tco<<" s."<<std::endl;


	
//GENERADOR DE GRAFICA POSICION TIEMPO
	FILE* ficheroc11;
    ficheroc11 = fopen("graficador11.txt", "wt");
    fputs("set terminal jpeg\n", ficheroc11);
    fputs("set datafile separator ','\n", ficheroc11);
	fputs("set title 'Cohete 1: Altura en funcion de el tiempo'\n", ficheroc11);
	fputs("set xlabel 'Tiempo t'\n", ficheroc11);
	fputs("set ylabel 'Altura y'\n", ficheroc11);
	fputs("set grid\n", ficheroc11);
	fputs("set output 'graficacohete11.jpeg'\n", ficheroc11);
    fputs("plot 'datos1.txt' using 1:2 with linespoints pt 1 ps 1 ",ficheroc11);    
    fclose(ficheroc11);
system("gnuplot graficador11.txt");

//GENERADOR DE GRAFICA VELOCIDAD TIEMPO
	FILE* ficheroc12;
    ficheroc12 = fopen("graficador12.txt", "wt");
    fputs("set terminal jpeg\n", ficheroc12);
    fputs("set datafile separator ','\n", ficheroc12);
	fputs("set title 'Cohete 1: Velocidad en funcion de el tiempo'\n", ficheroc12);
	fputs("set xlabel 'Tiempo t'\n", ficheroc12);
	fputs("set ylabel 'Velocidad'\n", ficheroc12);
	fputs("set grid\n", ficheroc12);
	fputs("set output 'graficacohete12.jpeg'\n", ficheroc12);
    fputs("plot 'datos1.txt' using 1:3 with linespoints pt 1 ps 1 ",ficheroc12);    
    fclose(ficheroc12);
system("gnuplot graficador12.txt");

//GENERADOR DE GRAFICA VELOCIDAD POSICION
	FILE* ficheroc13;
    ficheroc13 = fopen("graficador13.txt", "wt");
    fputs("set terminal jpeg\n", ficheroc13);
    fputs("set datafile separator ','\n", ficheroc13);
	fputs("set title 'Cohete 1: Velocidad y Posicion'\n", ficheroc13);
	fputs("set xlabel 'Posicion'\n", ficheroc13);
	fputs("set ylabel 'Velocidad'\n", ficheroc13);
	fputs("set grid\n", ficheroc13);
	fputs("set output 'graficacohete13.jpeg'\n", ficheroc13);
    fputs("plot 'datos1.txt' using 2:3 with linespoints pt 1 ps 1 ",ficheroc13);    
    fclose(ficheroc13);
system("gnuplot graficador13.txt");














/////////////////////////////////
/////////////////////////////////
//EL SIGUIENTE CODIGO ES PARA COHETE 2
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////


elfi=fopen("datos2.txt","wt");
fprintf(elfi,"%.3f,%.3f,%.3f \n",t,cohete2.y,cohete2.v);
for(int i=0;i<n && cohete2.y>=0;i++)
{
yini=cohete2.y;
cohete2.y=cohete2.y+(dt)*(cohete2.v);
cohete2.v=cohete2.v+(dt)*(at(Ft(E(mf(i*dt,cohete2.TSFC,cohete2.mfo,cohete2.Eo),cohete2.Eo),Fa(yini,cohete2.CD,cohete2.A,cohete2.v),mc(cohete2.mo,mf(i*dt,cohete2.TSFC,cohete2.mfo,cohete2.Eo)),g(yini)),mc(cohete2.mo,mf(i*dt,cohete2.TSFC,cohete2.mfo,cohete2.Eo))));

fprintf(elfi,"%.3f,%.3f,%.3f \n",i*dt,cohete2.y,cohete2.v);
tc1f=i*dt;
}
fclose(elfi);


//////////CALCULO DE LA YMAX
cohete2.y=0;
cohete2.v=0;
band1=0;
for(int i=0;i<n && band1==0;i++)
{
yini=cohete2.y;
cohete2.y=cohete2.y+(dt)*(cohete2.v);
cohete2.v=cohete2.v+(dt)*(at(Ft(E(mf(i*dt,cohete2.TSFC,cohete2.mfo,cohete2.Eo),cohete2.Eo),Fa(yini,cohete2.CD,cohete2.A,cohete2.v),mc(cohete2.mo,mf(i*dt,cohete2.TSFC,cohete2.mfo,cohete2.Eo)),g(yini)),mc(cohete2.mo,mf(i*dt,cohete2.TSFC,cohete2.mfo,cohete2.Eo))));


if(cohete2.v<0){
    band1=1;
    yc1max=yini;
    tc1hm=i*dt;

}

}


tco=(cohete2.mfo)/((cohete2.TSFC)*(cohete2.Eo));
std::cout<<"El cohete 2 alcanzo la altura Ymax= "<<yc1max<<" m  en el tiempo thmax= "<<tc1hm<<" s.  Y regreso de nuevo al suelo en el tiempo tf= "<<tc1f<<" s.   Y se le acabo el combustible en el tiempo tof= "<<tco<<" s."<<std::endl;


	
//GENERADOR DE GRAFICA POSICION TIEMPO
	
    ficheroc11 = fopen("graficador21.txt", "wt");
    fputs("set terminal jpeg\n", ficheroc11);
    fputs("set datafile separator ','\n", ficheroc11);
	fputs("set title 'Cohete 2: Altura en funcion de el tiempo'\n", ficheroc11);
	fputs("set xlabel 'Tiempo t'\n", ficheroc11);
	fputs("set ylabel 'Altura y'\n", ficheroc11);
	fputs("set grid\n", ficheroc11);
	fputs("set output 'graficacohete21.jpeg'\n", ficheroc11);
    fputs("plot 'datos2.txt' using 1:2 with linespoints pt 1 ps 1 ",ficheroc11);    
    fclose(ficheroc11);
system("gnuplot graficador21.txt");

//GENERADOR DE GRAFICA VELOCIDAD TIEMPO
	
    ficheroc12 = fopen("graficador22.txt", "wt");
    fputs("set terminal jpeg\n", ficheroc12);
    fputs("set datafile separator ','\n", ficheroc12);
	fputs("set title 'Cohete 2: Velocidad en funcion de el tiempo'\n", ficheroc12);
	fputs("set xlabel 'Tiempo t'\n", ficheroc12);
	fputs("set ylabel 'Velocidad'\n", ficheroc12);
	fputs("set grid\n", ficheroc12);
	fputs("set output 'graficacohete22.jpeg'\n", ficheroc12);
    fputs("plot 'datos2.txt' using 1:3 with linespoints pt 1 ps 1 ",ficheroc12);    
    fclose(ficheroc12);
system("gnuplot graficador22.txt");

//GENERADOR DE GRAFICA VELOCIDAD POSICION
	
    ficheroc13 = fopen("graficador23.txt", "wt");
    fputs("set terminal jpeg\n", ficheroc13);
    fputs("set datafile separator ','\n", ficheroc13);
	fputs("set title 'Cohete 2: Velocidad y Posicion'\n", ficheroc13);
	fputs("set xlabel 'Posicion'\n", ficheroc13);
	fputs("set ylabel 'Velocidad'\n", ficheroc13);
	fputs("set grid\n", ficheroc13);
	fputs("set output 'graficacohete23.jpeg'\n", ficheroc13);
    fputs("plot 'datos2.txt' using 2:3 with linespoints pt 1 ps 1 ",ficheroc13);    
    fclose(ficheroc13);
system("gnuplot graficador23.txt");





























/////////////////////////////////
/////////////////////////////////
//EL SIGUIENTE CODIGO ES PARA COHETE 3
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////

elfi=fopen("datos3.txt","wt");
fprintf(elfi,"%.3f,%.3f,%.3f \n",t,cohete3.y,cohete3.v);
for(int i=0;i<n && cohete3.y>=0;i++)
{
yini=cohete3.y;
cohete3.y=cohete3.y+(dt)*(cohete3.v);
cohete3.v=cohete3.v+(dt)*(at(Ft(E(mf(i*dt,cohete3.TSFC,cohete3.mfo,cohete3.Eo),cohete3.Eo),Fa(yini,cohete3.CD,cohete3.A,cohete3.v),mc(cohete3.mo,mf(i*dt,cohete3.TSFC,cohete3.mfo,cohete3.Eo)),g(yini)),mc(cohete3.mo,mf(i*dt,cohete3.TSFC,cohete3.mfo,cohete3.Eo))));

fprintf(elfi,"%.3f,%.3f,%.3f \n",i*dt,cohete3.y,cohete3.v);
tc1f=i*dt;
}
fclose(elfi);


//////////CALCULO DE LA YMAX
cohete3.y=0;
cohete3.v=0;
band1=0;
for(int i=0;i<n && band1==0;i++)
{
yini=cohete3.y;
cohete3.y=cohete3.y+(dt)*(cohete3.v);
cohete3.v=cohete3.v+(dt)*(at(Ft(E(mf(i*dt,cohete3.TSFC,cohete3.mfo,cohete3.Eo),cohete3.Eo),Fa(yini,cohete3.CD,cohete3.A,cohete3.v),mc(cohete3.mo,mf(i*dt,cohete3.TSFC,cohete3.mfo,cohete3.Eo)),g(yini)),mc(cohete3.mo,mf(i*dt,cohete3.TSFC,cohete3.mfo,cohete3.Eo))));

if(cohete3.v<0){
    band1=1;
    yc1max=yini;
    tc1hm=i*dt;

}

}

tco=(cohete3.mfo)/((cohete3.TSFC)*(cohete3.Eo));
std::cout<<"El cohete 3 alcanzo la altura Ymax= "<<yc1max<<" m  en el tiempo thmax= "<<tc1hm<<" s.  Y regreso de nuevo al suelo en el tiempo tf= "<<tc1f<<" s.   Y se le acabo el combustible en el tiempo tof= "<<tco<<" s."<<std::endl;


	
//GENERADOR DE GRAFICA POSICION TIEMPO
	
    ficheroc11 = fopen("graficador31.txt", "wt");
    fputs("set terminal jpeg\n", ficheroc11);
    fputs("set datafile separator ','\n", ficheroc11);
	fputs("set title 'Cohete 3: Altura en funcion de el tiempo'\n", ficheroc11);
	fputs("set xlabel 'Tiempo t'\n", ficheroc11);
	fputs("set ylabel 'Altura y'\n", ficheroc11);
	fputs("set grid\n", ficheroc11);
	fputs("set output 'graficacohete31.jpeg'\n", ficheroc11);
    fputs("plot 'datos3.txt' using 1:2 with linespoints pt 1 ps 1 ",ficheroc11);    
    fclose(ficheroc11);
system("gnuplot graficador31.txt");

//GENERADOR DE GRAFICA VELOCIDAD TIEMPO
	
    ficheroc12 = fopen("graficador32.txt", "wt");
    fputs("set terminal jpeg\n", ficheroc12);
    fputs("set datafile separator ','\n", ficheroc12);
	fputs("set title 'Cohete 3: Velocidad en funcion de el tiempo'\n", ficheroc12);
	fputs("set xlabel 'Tiempo t'\n", ficheroc12);
	fputs("set ylabel 'Velocidad'\n", ficheroc12);
	fputs("set grid\n", ficheroc12);
	fputs("set output 'graficacohete32.jpeg'\n", ficheroc12);
    fputs("plot 'datos3.txt' using 1:3 with linespoints pt 1 ps 1 ",ficheroc12);    
    fclose(ficheroc12);
system("gnuplot graficador32.txt");

//GENERADOR DE GRAFICA VELOCIDAD POSICION
	
    ficheroc13 = fopen("graficador33.txt", "wt");
    fputs("set terminal jpeg\n", ficheroc13);
    fputs("set datafile separator ','\n", ficheroc13);
	fputs("set title 'Cohete 3: Velocidad y Posicion'\n", ficheroc13);
	fputs("set xlabel 'Posicion'\n", ficheroc13);
	fputs("set ylabel 'Velocidad'\n", ficheroc13);
	fputs("set grid\n", ficheroc13);
	fputs("set output 'graficacohete33.jpeg'\n", ficheroc13);
    fputs("plot 'datos3.txt' using 2:3 with linespoints pt 1 ps 1 ",ficheroc13);    
    fclose(ficheroc13);
system("gnuplot graficador33.txt");










/////////////////////////////////
/////////////////////////////////
//EL SIGUIENTE CODIGO ES PARA GRAFICAR COSAS EXTRA
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////



//GENERADOR DE GRAFICA POSICIONES TIEMPO
	
    ficheroc11 = fopen("graficadorex1.txt", "wt");
    fputs("set terminal jpeg\n", ficheroc11);
    fputs("set datafile separator ','\n", ficheroc11);
	fputs("set title 'Cohetes: Alturas en funcion de el tiempo'\n", ficheroc11);
	fputs("set xlabel 'Tiempo t'\n", ficheroc11);
	fputs("set ylabel 'Altura y'\n", ficheroc11);
	fputs("set grid\n", ficheroc11);
	fputs("set output 'graficacoheteex1.jpeg'\n", ficheroc11);
    fputs("plot 'datos3.txt' using 1:2, 'datos2.txt' using 1:2, 'datos1.txt' using 1:2 with linespoints pt 1 ps 1 ",ficheroc11);    
    fclose(ficheroc11);
system("gnuplot graficadorex1.txt");


ficheroc11 = fopen("graficadorex2.txt", "wt");
    fputs("set terminal jpeg\n", ficheroc11);
    fputs("set datafile separator ','\n", ficheroc11);
	fputs("set title 'Cohetes: Velocidades en funcion de el tiempo'\n", ficheroc11);
	fputs("set xlabel 'Tiempo t'\n", ficheroc11);
	fputs("set ylabel 'Velocidad y'\n", ficheroc11);
	fputs("set grid\n", ficheroc11);
	fputs("set output 'graficacoheteex2.jpeg'\n", ficheroc11);
    fputs("plot 'datos3.txt' using 1:3, 'datos2.txt' using 1:3, 'datos1.txt' using 1:3 with linespoints pt 1 ps 1 ",ficheroc11);    
    fclose(ficheroc11);
system("gnuplot graficadorex2.txt");


ficheroc11 = fopen("graficadorex3.txt", "wt");
    fputs("set terminal jpeg\n", ficheroc11);
    fputs("set datafile separator ','\n", ficheroc11);
	fputs("set title 'Cohetes: Velocidades y Posiciones'\n", ficheroc11);
	fputs("set xlabel 'Posicion y'\n", ficheroc11);
	fputs("set ylabel 'Velocidad y'\n", ficheroc11);
	fputs("set grid\n", ficheroc11);
	fputs("set output 'graficacoheteex3.jpeg'\n", ficheroc11);
    fputs("plot 'datos3.txt' using 2:3, 'datos2.txt' using 2:3, 'datos1.txt' using 2:3 with linespoints pt 1 ps 1 ",ficheroc11);    
    fclose(ficheroc11);
system("gnuplot graficadorex3.txt");



};



//DEFICICION DE LAS FUNCIONES A UTILIZAR
float mf(float t,float TSFC,float mfo,float Eo)
{

    if(t<(mfo)/((TSFC)*(Eo))){
        return (-1)*(TSFC)*(Eo)+(mfo);

    }else{
        return 0;
    }
    

};

float mc(float mo, float mf)
{
    return mo+mf;
};

float E(float mf,float Eo)  //En vez de utilizar una bandera para cuando se acabara el combustible, utilice esta funcion.
{
    if(mf>0){
        return Eo;

    }else{
        return 0;
    }

}

float g(float y)
{
    return ((G*Mt)/(pow((Rt+y),2.0)));
}

float rho(float y) //depende de y(t)
{

    if(y<(To/L)){
        return (((Po)/((R)*(To)))*(pow(1-((L*y)/(To)),(go)/(R*L))));
    }else{
        return 0;
    }
    
}

float Fa(float y,float CD,float A,float v)   //v es la velocidad
{
    return ((1/2)*(rho(y))*(CD)*(A)*(v)*(abs(v)));

}

float Ft(float E,float Fa,float mc,float g)
{
    return E-Fa-(mc)*(g);
}

float at(float Ft,float mc)
{
    return (Ft)/(mc);
}