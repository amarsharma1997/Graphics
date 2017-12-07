#include<conio.h>
#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>
int main()
{
 struct date d;
 getdate(&d);
 char *number[12];
 number[0]="12";
 number[1]="1";
 number[2]="2";
 number[3]="3";
 number[4]="4";
 number[5]="5";
 number[6]="6";
 number[7]="7";
 number[8]="8";
 number[9]="9";
 number[10]="10";
 number[11]="11";
 int a=DETECT,b;
 initgraph(&a,&b,"c:\\turboc3\\bgi");
 int i;
 while(!kbhit())
 {
  setcolor(1);
  settextstyle(4,0,4);
  outtextxy(250,200,"CLOCK");
  circle(300,220,200);
  for(i=0;i<12;i++)
  {
   settextstyle(4,0,1);
   float angle;
   angle=(22.0/42.0)*i*1.0;
   int x,y;
   x=300+(210*sin(angle));
   y=210-(210*cos(angle));
   outtextxy(x,y,number[i]);
  }
  struct time t;
  gettime(&t);
  float ah,am,as;
  gotoxy(35,18);
  printf("%d/%d/%d",d.da_day,d.da_mon,d.da_year);
  int h1,h2,m1,m2,s1,s2;
  as=22.0*t.ti_sec/210.0;
  am=(22.0*(t.ti_min+(t.ti_sec/60.0))/210.0);
  ah=(22.0*((t.ti_hour%12)+(t.ti_min/60.0))/42.0);
  h1=300+(120*sin(ah));
  h2=220-(120*cos(ah));
  m1=300+(150*sin(am));
  m2=220-(150*cos(am));
  s1=300+(180*sin(as));
  s2=220-(180*cos(as));
  setcolor(5);
  line(300,220,h1,h2);
  setcolor(3);
  line(300,220,m1,m2);
  setcolor(2);
  line(300,220,s1,s2);
  setcolor(5);
  settextstyle(3,0,2);
  delay(1000);
  outtextxy(450,400,"PINK-HOUR");
  setcolor(3);
  outtextxy(450,420,"BLUE-MINUTE");
  setcolor(2);
  outtextxy(450,440,"GREEN-SECOND");
  setcolor(0);
  line(300,220,h1,h2);
  line(300,220,m1,m2);
  line(300,220,s1,s2);
 }
 getch();
 closegraph();
 return 0;
}
