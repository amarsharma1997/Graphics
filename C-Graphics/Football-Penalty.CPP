#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>
union REGS in,out;

int index=0,i;

void initmouse();
void getmouseposition(int &,int &,int &);
void hidemouse();
void getplayer();
void startplay();
void initializeground();
void initbackground();
void collision(float ,float ,float );
void playshot(float ,float ,int );
void getball(float ,float ,int );
void striker();
void goalkeeper();
void kick();
void choicescreen();
void drawpowerbar();
int powerbarvalue();
int showgoalkeeeffect(int ,int ,float );




void main()
{
 clrscr();
 int a=DETECT,b;
 initgraph(&a,&b,"c:\\turboc3\\bgi");
 start:
 setcolor(15);
 setlinestyle(SOLID_LINE,0,1);
 setfillstyle(SOLID_FILL,9);
 bar(0,0,1000,400);
 settextstyle(1,0,5);
 setfillstyle(SOLID_FILL,2);
 bar(0,400,1000,800);
 line(0,70,1000,70);
 outtextxy(130,10,"THE FOOTBALL KICK");
 setfillstyle(HATCH_FILL,RED);
 fillellipse(500,150,60,30);
 fillellipse(500,250,60,30);
 fillellipse(500,350,60,30);
 settextstyle(3,0,2);
 outtextxy(470,140,"PLAY");
 outtextxy(450,240,"GUIDELINES"); outtextxy(480,340,"QUIT");
 getplayer();
 i=0;
 char choice;
 while(1)
 {
   int j;
   setcolor(9);
   for(j=0;j<3;j++)
   {
    outtextxy(400,140+j*100,"->");
   }
   setcolor(4);
   outtextxy(400,140+i*100,"->");
   while(!kbhit())
   {}
   choice=getch();

   if(choice==72)
   {
    i--;
    if(i<0)
    {
     i=0;
    }
   }
   if(choice==80)
   {
    i++;
    if(i>2)
    {
     i=2;
    }
   }
   if((choice==13))
   {
    playshot(0.0,0.0,index);
    if(i==0)
    {
     startplay();
     goto start;
    }
    else
    {
     break;
    }
   }
 }
 cleardevice();
}




void initmouse()
{
 in.x.ax=1;
 int86(51,&in,&out);
}

void hidemouse()
{
 in.x.ax=2;
 int86(51,&in,&out);
}



void getmouseposition(int &xpos,int &ypos,int &click)
{
 in.x.ax=3;
 int86(51,&in,&out);
 xpos=out.x.cx;
 ypos=out.x.dx;
 click=out.x.bx;
}




void startplay()
{
 int x,y,c,score=0;
 start:
 cleardevice();
 initializeground();
 initbackground();
 getball(320,395,15);
 striker();
 goalkeeper();
 initmouse();
 int i,play=1;
 i=0;
 while(play)
 {
  delay(100);
  if(kbhit())
  {
   char d;
   d=getch();
   if(d==27)
   {
    choicescreen();
    char C;
    getchoice:
    C=getch();
    if((C=='y')||(C=='Y'))
    {
     play=0;
    }
    else if((C=='n')||(C=='N'))
    {
     goto start;
    }
    else
    {
     goto getchoice;
    }
   }
  }
  if(play==1)
  {
   setcolor(15);
   setlinestyle(SOLID_LINE,0,1);
   if(i>=10)
   {
    i=0;
    setcolor(2);
    setfillstyle(SOLID_FILL,2);
    bar(10,425,20,475);
   }
   line(10,470-i*5,20,470-i*5);
   getmouseposition(x,y,c);
   float t;
   if(c==1)
   {
    kick();
    t=1.6-i*0.1;
    showgoalkeeeffect(x,y,t);
    getch();
    startplay();
    c=0;
   }
   i++;
  }
 }
 hidemouse();
 cleardevice();
}




int showgoalkeeeffect(int prex,int prey ,float t)
{
 int requirement=0;
 float ballposx,ballposy;
 ballposx=prex;
 ballposy=prey;
 if((ballposx>120)&&(ballposy<520))
 {
  if(ballposy<160)
  {
   requirement=1;
  }
  else
  {
   if(ballposx>320)
   {
    ballposx=ballposx-320;
    ballposx=(pow(ballposx+(60.0*t*t),2)/(240.0*t*t))+320;
   }
   else
   {
    ballposx=320-ballposx;
    ballposx=320-(pow(ballposx+(60.0*t*t),2)/(240.0*t*t));
   }
   ballposy=395-ballposy;
   ballposy=(pow(ballposy+(60.0*t*t),2)/(240.0*t*t));
   if(ballposy>=235)
   {
    ballposy=155.0;
   }
   else
   {
    ballposy=395-ballposy;
   }
   if((ballposx<520)&&(ballposx>120)&&(ballposy==155.00))
   {
    requirement=1;
   }
  }
 }
 if(requirement==1)
 {
  if((ballposx>260)&&(ballposx<380)&&(ballposy>100)&&(ballposy<=160))
  {
   if(ballposx<320)
   {
    initbackground();
    initmouse();
    setcolor(1);
    setfillstyle(SOLID_FILL,1);
    setlinestyle(SOLID_LINE,0,3);
    fillellipse(320,ballposy-56,11,11);
    line(320,ballposy-45,320,ballposy);
    line(320,ballposy-25,260,ballposy-25);
    line(320,ballposy-25,380,ballposy-25);
    line(320,ballposy,260,ballposy);
    line(320,ballposy,320+sqrt(pow(60,2)-pow(160-ballposy,2)),160);
    return 0;
   }
   else if(ballposx>320)
   {
    initbackground();
    initmouse();
    setcolor(1);
    setfillstyle(SOLID_FILL,1);
    fillellipse(320,ballposy-56,11,11);
    setlinestyle(SOLID_LINE,0,3);
    line(320,ballposy-45,320,ballposy);
    line(320,ballposy-25,260,ballposy-25);
    line(320,ballposy-25,380,ballposy-25);
    line(320,ballposy,380,ballposy);
    line(320,ballposy,320-sqrt(pow(60,2)-pow(160-ballposy,2)),160);
    return 0;
   }
   else
   {
    if(ballposy>115)
    {
     initbackground();
     initmouse();
     setcolor(1);
     setfillstyle(SOLID_FILL,1);
     fillellipse(320,44,11,11);
     line(320,55,320,100);
     line(320,75,260,75);
     line(320,75,380,75);
     line(320,100,320,160);
     line(320,100,320,160);
     return 0;
    }
   }
  }
  else if((pow(ballposx-320,2)+pow(ballposy-80,2))<=3600)
  {
   initbackground();
   initmouse();
   setcolor(1);
   setfillstyle(SOLID_FILL,1);
   setlinestyle(SOLID_LINE,0,3);
   fillellipse(320,59,11,11);
   line(320,70,320,115);
   line(320,115,298,160);
   line(320,115,342,160);
   float r,BPx,BPy;
   BPx=320-ballposx;
   BPy=80-ballposy;
   r=sqrt(pow(BPx,2)+pow(BPy,2));
   if(ballposx<=320)
   {
     line(320,80,320.0-(60.0*BPx/r),80.0-(60.0*BPy/r));
     line(320,80,370,104.5);
   }
   else
   {
     line(320,80,320.0-(60.0*BPx/r),80.0-(60.0*BPy/r));
     line(320,80,270,104.5);
   }
   return 0;
  }
  else
  {
   float T=0.0;
   float vreq,v,vh,vl,vhnd,vx,vy;
   float hx,hy,hndx,hndy,thx=0.0,thy=0.0,lx,ly,px,py,THX,THY,lex,ley;
   {
    px=320.0-ballposx;
    if(px<0.0)
    {
     px=ballposx-320.0;
    }
    py=160.0-ballposy;
    if(py<11)
    {
     py=11;
    }
    THX=145.0*px/(sqrt(pow(px,2)+pow(py,2)));
    THY=145.0*py/(sqrt(pow(px,2)+pow(py,2)));
    if(THX<px)
    {
     vx=(px-THX)/t;
     vy=(py-THY)/t;
    }
    else
    {
     vx=0.0;
     vy=0.0;
    }
    vreq=((THX*80.0)/(t*145.0));
    if(vreq+vx>125.0)
    {
     vreq=vreq*t;
     vx=px-THX;
     vy=(py-THY);
    }
    v=vreq*145.0/80.0;
    vh=vreq*116.0/80.0;
    vhnd=vreq*85.0/80.0;
    vl=vreq*60.0/80.0;
    while((px>=thx)||(THX>=thx))
    {
     thx=(v)*T+vx*T;
     thy=vy*T+sqrt(pow(145.0,2)-pow(thx-vx*T,2));
     hx=(vh)*T+vx*T;
     hy=vy*T+sqrt(pow(116.0,2)-pow(hx-vx*T,2));
     hndx=(vhnd)*T+vx*T;
     hndy=vy*T+sqrt(pow(85.0,2)-pow(hndx-vx*T,2));
     lx=(vl)*T+vx*T;
      ly=vy*T+sqrt(pow(60.0,2)-pow(lx-vx*T,2));
     lex=vx*T;
     ley=vy*T;
     initbackground();
     initmouse();
     setcolor(1);
     setfillstyle(SOLID_FILL,1);
     setlinestyle(SOLID_LINE,0,3);
     if(ballposx<=320)
     {
      fillellipse(320.0-hx,160.0-hy,11,11);
      line(320-hx,160-hy,320-lx,160-ly);
      line(320-thx,160-thy,320-hx,160-hy);
      line(320-hndx,160-hndy,380-hndx,160-hndy);
      line(320-lx,160-ly,320-lex,160-ley);
      line(320-lx,160-ly,380-lx,160-ly);
     }
     else
     {
      fillellipse(320.0+hx,160.0-hy,11,11);
      line(320+hx,160-hy,320+lx,160-ly);
      line(320+thx,160-thy,320+hx,160-hy);
      line(320+hndx,160-hndy,260+hndx,160-hndy);
      line(320+lx,160-ly,320+lex,160-ley);
      line(320+lx,160-ly,260+lx,160-ly);
     }
     delay(10);
     T=T+0.1;
    }
   }
   return 0;
  }
 }
}





void goalkeeper()
{
 setcolor(1);
 setfillstyle(SOLID_FILL,1);
 fillellipse(320,59,11,11);
 line(320,70,320,115);
 line(320,80,260,80);
 line(320,80,380,80);
 line(320,115,298,160);
 line(320,115,342,160);
}





void choicescreen()
{
 cleardevice();
 settextstyle(1,0,3);
 setcolor(15);
 outtextxy(200,200,"Do You Want To Exit?");
 outtextxy(250,220,"Press Y or N");
}









void kick()
{
 float fp1=290,fp2=410;
 for(;fp1<305;fp1+=5)
 {
  setcolor(6);
  setlinestyle(SOLID_LINE,0,3);
  line(310,370,fp1,fp2);
  delay(10);
  setcolor(2);
  line(310,370,fp1,fp2);
 }
}





void striker()
{
 setcolor(6);
 setfillstyle(SOLID_FILL,6);
 fillellipse(290,250,15,18);
 setlinestyle(SOLID_LINE,0,3);
 line(290,268,290,330);
 line(290,290,260,240);
 line(290,290,310,350);
 line(290,330,275,415);
 line(290,330,310,370);
 line(310,370,290,410);
}





void getball(float ballpath1,float ballpath2,int radius)
{
 setcolor(RED);
 circle(ballpath1,ballpath2,12);
 setcolor(0);
 setfillstyle(XHATCH_FILL,15);
 fillellipse(ballpath1,ballpath2,12,12);
}






void getplayer()
{
 setfillstyle(SOLID_FILL,RED);
 setcolor(RED);
 circle(70,440,10);
 fillellipse(70,440,10,10);
 setcolor(15);
 setfillstyle(SOLID_FILL,15);
 fillellipse(45,350,13,17);
 setlinestyle(SOLID_LINE,1,3);
 line(45,363,45,402);
 line(45,370,30,390);
 line(45,370,63,385);
 line(45,402,50,450);
 line(45,402,35,450);
 setcolor(0);
 settextstyle(1,0,2);
 outtextxy(50,330,".");
 settextstyle(1,0,1);
 outtextxy(48,335,"-");
 outtextxy(48,337,"_");
}





void playshot(float ux,float uy,int INDEX)
{
 float pathx,pathy,dist,height,t=0.0,T=0.0,foot1=35,foot2=445;
 if(INDEX==0)
 {
  dist=330;
  height=140+i*100;
  height=437-height;
 }
 uy=dist*sqrt(5/(dist-height));
 ux=uy;
 T=dist/ux;
 while(foot1<57)
 {
  setcolor(2);
  setlinestyle(SOLID_LINE,0,3);
  line(45,402,foot1,450);
  delay(1);
  foot1=foot1+2;
  foot2=foot2+1;
  if(foot2>=450)
  {
   foot2=foot2-1;
  }
  setcolor(15);
  line(45,402,foot1,foot2);
  line(45,402,35,450);
  delay(1);
 }
 t=0.0;
 int color;
 while(t<=T)
 {
  pathx=70+ux*t;
  pathy=439-uy*t+5*t*t;
  setfillstyle(SOLID_FILL,RED);
  setcolor(RED);
  circle(pathx,pathy,10);
  fillellipse(pathx,pathy,10,10);
  delay(1);
  if(pathy<=390)
  {
   color=9;
   setfillstyle(SOLID_FILL,9);
   bar(70,380,250,400);
  }
  else
  {
   color=2;
  }
  setcolor(color);
  setfillstyle(SOLID_FILL,color);
  circle(pathx,pathy,10);
  fillellipse(pathx,pathy,10,10);
  t=t+.3;
 }
  collision(ux,pathx,pathy);
}





void collision(float VELOCITY,float PATHX,float PATHY)
{
  float v1,v2,PATH1,t=0.0,T;
  v2=0.66*VELOCITY;
  v1=2.66*VELOCITY;
  T=40/v1;
  while(t<=T)
  {
   PATHX=PATHX-v2*5.0*t;
   PATHY=PATHY+125.0*t*t;
   PATH1=400+v1*t;
   setfillstyle(SOLID_FILL,RED);
   setcolor(RED);
   circle(PATHX,PATHY,10);
   fillellipse(PATHX,PATHY,10,10);
   setcolor(4);
   outtextxy(PATH1,140+i*100,"->");
   delay(.05);
   setcolor(9);
   setfillstyle(SOLID_FILL,9);
   circle(PATHX,PATHY,10);
   fillellipse(PATHX,PATHY,10,10);
   outtextxy(PATH1,140+i*100,"->");
   t=t+0.1;
  }
}









void initializeground()
{
 setcolor(2);
 setfillstyle(SOLID_FILL,2);
 bar(0,160,1000,800);
 setcolor(15);
 setlinestyle(SOLID_LINE,0,3);
 line(50,160,0,190);
 line(590,160,640,190);
 line(0,350,1000,350);
 setfillstyle(SOLID_FILL,15);
 fillellipse(320,400,5,5);
}





void initbackground()
{
 setcolor(RED);
 setfillstyle(SOLID_FILL,RED);
 bar(0,50,1000,120);
 setcolor(2);
 setfillstyle(SOLID_FILL,2);
 bar(0,120,1000,160);
 setcolor(YELLOW);
 settextstyle(4,0,5);
 outtextxy(20,60,"THE");
 outtextxy(200,60,"FOOTBALL");
 outtextxy(520,60,"KICK");
 setcolor(9);
 setfillstyle(SOLID_FILL,9);
 bar(0,0,1000,50);
 setcolor(15);
 line(0,160,1000,160);
 setlinestyle(SOLID_LINE,0,3);
 line(130,10,130,160);
 line(510,10,510,160);
 line(130,10,510,10);
 line(160,10,160,140);
 line(480,10,480,140);
 line(160,140,130,160);
 line(480,140,510,160);
 line(160,140,480,140);
 setlinestyle(SOLID_LINE,0,1);
 int in,x1,y1,x2,y2;
 x1=160;
 y1=10;
 x2=160;
 y2=10;
 while(1)
 {
  if(x1>480)
  {
   x1=480;
   y1+=10;
  }
  if(y2>140)
  {
   y2=140;
   x2+=10;
  }
  if(x2>480)
  {
   break;
  }
  line(x1,y1,x2,y2);
  x1+=10;
  y2+=10;
 }
 x1=480;
 y1=10;
 x2=480;
 y2=10;
 while(1)
 {
  if(x1<160)
  {
   x1=160;
   y1+=10;
  }
  if(y2>140)
  {
   y2=140;
   x2-=10;
  }
  if(x2<160)
  {
   break;
  }
  line(x1,y1,x2,y2);
  x1-=10;
  y2+=10;
 }
 x1=130;
 y1=10;
 x2=130;
 y2=10;
 while(1)
 {
  if(x1>160)
  {
   x1=160;
   y1+=10;
  }
  if(y2>160)
  {
   y2=160;
  }
  if(y1>140)
  {
   break;
  }
  line(x1,y1,x2,y2);
  x1+=10;
  y2+=10;
 }
 x1=510;
 y1=10;
 x2=510;
 y2=10;
 while(1)
 {
  if(x1<480)
  {
   x1=480;
   y1+=10;
  }
  if(y2>160)
  {
   y2=160;
  }
  if(y1>140)
  {
   break;
  }
  line(x1,y1,x2,y2);
  x1-=10;
  y2+=10;
 }
 x1=160;
 y1=10;
 x2=160;
 y2=10;
 in=0;
 while(1)
 {
  if(x1<130)
  {
   x1=130;
   y1+=10;
  }
  if(y2>140)
  {in++;
   y2=140+in*3;
   x2-=in*2;
   if(x2<130)
   {
    x2=130;
   }
  }
  if(y1>160)
  {
   break;
  }
  line(x1,y1,x2,y2);
  x1-=10;
  y2+=10;
 }
 x1=480;
 y1=10;
 x2=480;
 y2=10;
 in=0;
 while(1)
 {
  if(x1>510)
  {
   x1=510;
   y1+=10;
  }
  if(y2>140)
  {
   in++;
   y2=140+in*3;
   x2+=in*2;
   if(x2>510)
   {
    x2=510;
   }
  }
  if(y1>160)
  {
   break;
  }
  line(x1,y1,x2,y2);
  x1+=10;
  y2+=10;
 }
}