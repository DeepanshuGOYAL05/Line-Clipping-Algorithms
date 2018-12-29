#include <stdio.h>
#include <GL/freeglut.h>
#include <math.h>
int xmin=200,xmax=600;
int ymin=200,ymax=600;

void myinit()
{
 glLoadIdentity();
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0,800,0,700);
 glClearColor(1,1,1,1);
 glClear(GL_COLOR_BUFFER_BIT);
}

void display()
{
    glColor3f(0,0,1);
     glRasterPos2i(150,650);
     glutBitmapString(GLUT_BITMAP_HELVETICA_18,"Press 1 for point clipping 2 for line clipping");
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin,ymin);
    glVertex2i(xmax,ymin);
    glVertex2i(xmax,ymax);
    glVertex2i(xmin,ymax);
    glEnd();

    glFlush();
}

void pointclipping(int x,int y)
{
    glColor3f(0,1,0);
    if((x>xmin && x<xmax) && (y>ymin && y<ymax))
    {    glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
        printf("point plotted\n");
    }
    else
        printf("point clipped\n");
}
void lineclipping(int x1,int y1,int x2,int y2)
{
    int dx=x2-x1;
    int dy=y2-y1;
    int p[4],q[4];

    p[0]=-1*dx;
    p[1]=dx;
    p[2]=-1*dy;
    p[3]=dy;
    q[0]=x1-xmin;
    q[1]=xmax-x1;
    q[2]=y1-ymin;
    q[3]=ymax-y1;
     float t1=0;
    float t2=1;
    float temp;

    int i;
    int x1f,y1f,x2f,y2f;

    for(i=0;i<4;i++)
    {
        if(p[i]==0)
        {
            if(q[i]<0)
             {printf("Line not inside");}
            else
             { if(dx==0)
                 {
                     x1f=x1;
                     x2f=x2;
                     y1f=(ymin>y1)?ymin:y1;
                     y2f=(ymax<y2)?ymax:y2;
                 }
               else if(dy==0)
               {
                       y1f=y1;
                     y2f=y2;
                     x1f=(xmin>x1)?xmin:x1;
                     x2f=(xmax<x2)?xmax:x2;
               }
             }
             break;
        }
        else if(p[i]<0)
        {
            temp=(float)q[i]/p[i];
            if(t1<temp)
                t1=temp;
        }
        else if(p[i]>0)
        {
            temp=(float)q[i]/p[i];
            if(t2>temp)
                t2=temp;    
        }

    }

    if(i>3)
    {
        if(t1>t2)
            {
                printf("line not inside\n");
                return;}
        else
            {x1f=x1+t1*dx;
             y1f=y1+t1*dy;
             x2f=x1+t2*dx;
             y2f=y1+t2*dy;}
    }

    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex2i(x1f,y1f);
    glVertex2i(x2f,y2f);
    glEnd();
}

int (*(sort_inc)(int t[][2],int size))[2]
{
    int swapx,swapy,i,j;
    for (i = 0; i < size; i++)
    {
    for (j = i +1; j < size; ++j)
    {
        if (t[i][0] > t[j][0])
        {
            swapx = t[i][0];
            t[i][0] = t[j][0];
            t[j][0] = swapx;
            swapy = t[i][1];
            t[i][1] = t[j][1];
            t[j][1] = swapy;
        }
     }
    }
    return t;
}

int (*(sort_dec)(int t[][2],int size))[2]
{
    int swapx,swapy,i,j;
    for (i = 0; i < size; i++)
    {
    for (j = i +1; j < size; ++j)
    {
        if (t[i][0] < t[j][0])
        {
            swapx = t[i][0];
            t[i][0] = t[j][0];
            t[j][0] = swapx;
            swapy = t[i][1];
            t[i][1] = t[j][1];
            t[j][1] = swapy;
        } } }
    return t;
}
void keypress(unsigned char key,int x,int y)
{
    switch(key)
        {
            case 27:exit(0);
            break;
            case '1':printf("Enter coordinates:\n");
                int px,py;
                scanf("%d %d",&px,&py);
                pointclipping(px,py);
            break;
            case '2':printf("Enter coordinates of start point :\n");
                int x1,x2,y1,y2;
                
                scanf("%d %d",&x1,&y1);
                printf("Enter coordinates of end point :\n");
                scanf("%d %d",&x2,&y2);
                lineclipping(x1,y1,x2,y2);
            break;
}
    glutPostRedisplay();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    int choice;
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 
    glutInitWindowSize(800,700);
     glutInitWindowPosition(100,20);
     glutCreateWindow("Clipping");
     myinit();
     glutDisplayFunc(display);
    glutKeyboardFunc(keypress);   
    glutMainLoop();
    return 0;
}
