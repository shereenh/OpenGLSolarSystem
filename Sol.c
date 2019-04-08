#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define ARROW 1
/*
	1.Random Star Generator
	2.Sirius-Regulus-Bellatrix stars
	3.Shooting Star Generator
	4.Orbit Generation-given radius
	5.Spaceship
	6.Sphere Generator
	7.Text Generator
	8.Menu Implementation
*/

void dispTex();
int u;		//u=0 if ring of planet, u=1 if spaceship
//RANDOM STARS BEGIN-------------------------------------------------
typedef struct 
{
	GLfloat sx;
	GLfloat sy;
	char c;
}sta;
sta s[109];
static int i=0;
void chquad()
{
	int j;
	float x,y;
	x=(float)(rand()%10);
	y=(float)(rand()%10);
	j=rand()%4;
	switch(j)
	{
	case 0: s[i].sx=x; s[i].sy=y; i++; break;
	case 1: s[i].sx=-x; s[i].sy=y; i++; break;
	case 2: s[i].sx=x; s[i].sy=-y; i++; break;
	case 3: s[i].sx=-x; s[i].sy=-y; i++; break;
	}
}
void star()
{
	int k,amt=100,amtbig=9;
	
	for(k=0;k<amt;k++)
	{
	chquad();
	s[i].c='s';
	}
	
	for(k=0;k<amtbig;k++)
	{
	chquad();
	s[i].c='b';
	}
}
void dispstar()
{
	
	star();	
	glEnable(GL_COLOR_MATERIAL);
	for(i=0;i<109;i++)
	{
	if(s[i].c=='s')
	{
		glPointSize(0.5);
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_POINTS);
		glVertex3f(s[i].sx,s[i].sy,-50.0);
		glEnd();
	}
	if(s[i].c=='b')
	{
		glPointSize(2.5);
		glColor3f(1.0,1.0,0.0);
		glBegin(GL_POINTS);
		glVertex3f(s[i].sx,s[i].sy,-50.0);
		glEnd();
	}
	}
	glDisable(GL_COLOR_MATERIAL);
}

//RANDOM STARS END
//SRB BEGINS------------------------------------------------------
void moon();
void srb()
{	
	
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0,1.0,1.0);			//sirius
	glPushMatrix();
		glTranslated(-5.0,5.0,0.0);
		glScaled(0.1,0.1,0.1);
		moon();
	glPopMatrix();
	glColor3f(0.0,0.0,1.0);			//regulus
	glPushMatrix();
		glTranslated(8.0,7.0,0.0);
		glScaled(0.1,0.1,0.1);
		moon();
	glPopMatrix();	
	glColor3f(1.0,0.0,1.0);
	glPushMatrix();				//bellatrix
		glTranslated(2.0,-5.0,0.0);
		glScaled(0.08,0.08,0.08);
		moon();
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);

}
//SRB ENDS
//SHOOTING STAR BEGINS---------------------------------------------
static GLdouble theta1=0.0;	//shooting star
static GLdouble theta2=0.0;	//rotation about itself

void shstardraw()
{
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0,1.0,1.0);		//streak
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.2,0.3,-6.0);
		glVertex3f(0.0,0.0,-6.0);
		glVertex3f(-2.0,2.0,-6.0);
	glEnd();
	glColor3f(0.9,0.9,0.0);
	glBegin(GL_TRIANGLES);
		glVertex3f(0,0.5,-6.0);
		glVertex3f(-0.5,0.0,-6.0);
		glVertex3f(0.5,0.0,-6.0);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5,0.4,-6.0);
		glVertex3f(0,-0.1,-6.0);
		glVertex3f(0.5,0.4,-6.0);
	glEnd();
	
	glDisable(GL_COLOR_MATERIAL);
}
void dispshstar()
{	
	glPushMatrix();
		glTranslated(8.0,0.0,0.0);
		glRotated(theta1,0,0,1);
		glTranslated(-5.0,0.0,0.0);
		glScaled(0.5,0.5,0.5);
		shstardraw();	
	glPopMatrix();	
}
//SHOOTING STAR ENDS
//ORBIT BEGINS----------------------------------------------------------
void orb(GLfloat rad,GLfloat psiz,int seg)
{
	glEnable(GL_COLOR_MATERIAL);
	int i;
	glColor3f(0.5,0.5,0.5);
	glPointSize(psiz);
    glBegin(GL_POINTS);
    for(i = 0; i < 100; i++)
    {
        float x,z,theta = 2.0*3.1415926f*(float)i/(float)seg;

        x = rad * cosf(theta);
        z = rad * sinf(theta);

        glVertex3f(x,0,z);

    }
    glEnd();
	glDisable(GL_COLOR_MATERIAL);
}
void ring(GLfloat rad,GLfloat psiz)
{
	glEnable(GL_COLOR_MATERIAL);
	GLfloat x,z,theta;
	if(u==0)
	glColor3f(1.0,1.0,1.0);
	else
	glColor3f(0.2,0.1,0.1);
	glPointSize(psiz);
	glBegin(GL_POINTS);
	for(theta=0;theta<360;theta++){
	x=rad*cos(theta); z=rad*sin(theta);
	glVertex3f(x,0,z);
	}
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
}
//ORBIT ENDS
//SPACESHIP BEGINS-------------------------------------------------------
void moon();
void spaceship()
{
		u=1;	
		glEnable(GL_COLOR_MATERIAL);
		glPushMatrix();
			
			glTranslated(-9.0,0.0,0.0);
			glRotated(theta1,0,0,1);
			glTranslated(5.0,0.0,0.0);
			glColor3f(0.2,0.1,0.1);	
			glScaled(0.17,0.11,0.17);
			moon();
				glScaled(1.0,0.1,1.0);	//sphere scaled to ring
		ring(1.2,4.0);
		glPopMatrix();
		glDisable(GL_COLOR_MATERIAL);
}
//SPACESHIP ENDS
//SPHERE BEGINS------------------------------------------------------

typedef float point3[4];
static GLdouble theta=0.0;	//fast planets

static GLdouble theta3=0.0;	//slow planets
static GLdouble theta4=-360.0;		//clockwise rotation
/*
id=0 sun
id=1 mercury
id=2 venus
id=3 earth
id=4 moon
id=5 mars
id=6 jupiter
id=7 saturn
id=8 uranus
id=9 neptune
*/
point3 v[4]={{0.0,0.0,1.0},{0.0,0.942809,-0.333333},{-0.816497,-0.471405,-0.333333},{0.816497,-0.471405,-0.333333}};

void tri(point3 a,point3 b,point3 c)
{
	glBegin(GL_POLYGON);
	glNormal3fv(a);
	glVertex3fv(a);
	 glNormal3fv(b);
	glVertex3fv(b);
	glNormal3fv(c);
	 glVertex3fv(c);
	glEnd();
}

void norm(point3 p)
{
	double sqrt();
	float d=0.0;
	int i;
	for(i=0;i<3;i++) d+=p[i]*p[i];
	d=sqrt(d);
	if(d>0.0) for(i=0;i<3;i++) p[i]/=d;
}
void divv(point3 a,point3 b,point3 c,int m)
{
	point3 v1,v2,v3;
	int j;
	if(m>0)
	{
	for(j=0;j<3;j++) v1[j]=a[j]+b[j];
	norm(v1);
	for(j=0;j<3;j++) v2[j]=a[j]+c[j];
	norm(v2);
	for(j=0;j<3;j++) v3[j]=c[j]+b[j];
	norm(v3);
	divv(a,v2,v1,m-1);
	divv(b,v3,v2,m-1);
	divv(c,v1,v3,m-1);
	divv(v1,v2,v3,m-1);
	}
	else
	tri(a,b,c);
}

void tetra()
{
	divv(v[0],v[1],v[2],4);
	divv(v[3],v[2],v[1],4);
	divv(v[0],v[3],v[1],4);
	divv(v[0],v[2],v[3],4);
}
	
void sun()	
{
	glEnable(GL_COLOR_MATERIAL);
	
	GLfloat mat_amb0[]={1.0,0.0,0.0,1.0};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb0);

	tetra();
	glDisable(GL_COLOR_MATERIAL);
	
}

void mercury()	
{
	glEnable(GL_COLOR_MATERIAL);

	GLfloat mat_amb1[]={1.0,0.0,1.0,1.0};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb1);
	
	tetra();
	glDisable(GL_COLOR_MATERIAL);
	
}
void venus() 
{
	glEnable(GL_COLOR_MATERIAL);

	GLfloat mat_amb2[]={1.0,0.0,1.0,1.0};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb2);
	
	tetra();
	glDisable(GL_COLOR_MATERIAL);
	
}
void earth()	
{
	glEnable(GL_COLOR_MATERIAL);

	GLfloat mat_amb3[]={0.0,1.0,0.0,1.0};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb3);
	
	tetra();
	glDisable(GL_COLOR_MATERIAL);
	
}
void moon()	
{
	glEnable(GL_COLOR_MATERIAL);

	GLfloat mat_amb4[]={1.0,0.0,0.0,1.0};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb4);
	
	tetra();
	glDisable(GL_COLOR_MATERIAL);
	
}
void mars()	
{
	glEnable(GL_COLOR_MATERIAL);

	GLfloat mat_amb5[]={1.0,0.0,0.0,1.0};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb5);
	
	tetra();
	glDisable(GL_COLOR_MATERIAL);
	
}
void jupiter()	
{
	glEnable(GL_COLOR_MATERIAL);

	GLfloat mat_amb6[]={0.978,0.379,0.344,1.0};
	 
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb6);
	
	tetra();
	glDisable(GL_COLOR_MATERIAL);
	
}
void saturn()	
{
	glEnable(GL_COLOR_MATERIAL);

	GLfloat mat_amb7[]={1.0,0.0,0.0,1.0};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb7);

	tetra();
	glDisable(GL_COLOR_MATERIAL);
	
}
void uranus()	
{
	glEnable(GL_COLOR_MATERIAL);

	GLfloat mat_amb8[]={0.0,0.0,1.0,1.0};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb8);
	
	tetra();
	glDisable(GL_COLOR_MATERIAL);
	
}
void neptune()	
{
	glEnable(GL_COLOR_MATERIAL);

	GLfloat mat_amb9[]={1.0,0.0,0.0,1.0};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb9);
	tetra();
	glDisable(GL_COLOR_MATERIAL);
	
}

void dispplan()
{
	u=0;
	orb(2.0,0.5,50);
	orb(3.0,0.5,55);
	orb(3.5,0.5,60);
	orb(4.0,0.5,70);
	orb(6.0,1.0,90);
	orb(7.0,1.0,100);
	orb(8.0,1.0,100);
	orb(9.0,1.0,100);
	
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
		glScaled(1.3,1.3,1.3);
		glRotated(180.0,0,1,0);
		sun();
	glPopMatrix();
	glPushMatrix();
		glRotated(theta,0,1,0); //rotate earth about sun
		glTranslated(-3.5,0,0);
		glRotated(theta2,0,1,0);  //rotate earth about itself
		glColor3f(0.059,0.019,0.938);
		glScaled(0.35,0.35,0.35);  //earth
		earth();
		glColor3f(1.0,1.0,1.0);
		glTranslated(1.0,0.0,1.0);
		glScaled(0.17,0.17,0.17);
		moon();
	glPopMatrix();
	glPushMatrix();
		glRotated(theta,0,1,0); //rotate planet about sun
		glTranslated(2.0,0,0.0);
		glRotated(theta2,0,1,0);  //rotate planet about itself
		glColor3f(0.594,0.301,0.078);
		glScaled(0.2,0.2,0.2);	//MERCURY
		mercury();
	glPopMatrix();
	glPushMatrix();
		glRotated(theta,0,1,0); //rotate planet about sun
		glTranslated(0.0,0,3.0);
		glRotated(theta4,0,1,0);  //rotate planet about itself
		glColor3f(0.945,0.077,0.789);
		glScaled(0.35,0.35,0.35);	//VENUS
		venus();
	glPopMatrix();
	glPushMatrix();
		glRotated(theta,0,1,0); //rotate planet about sun
		glTranslated(4.0,0,0);
		glRotated(theta2,0,1,0);  //rotate planet about itself
		glColor3f(0.922,0.023,0.023);
		glScaled(0.25,0.25,0.25);	//MARS
		mars();			
	glPopMatrix();
	glPushMatrix();
		glRotated(theta,0,1,0); //rotate planet about sun
		glTranslated(0.0,0,6.0);
		glRotated(theta3,0,1,0);  //rotate planet about itself
		glColor3f(0.978,0.379,0.344);
		glScaled(0.5,0.5,0.5);	//JUPITER
		jupiter();
	glPopMatrix();
	glPushMatrix();
		glRotated(theta,0,1,0); //rotate planet about sun
		glTranslated(0.0,0,-7.0);
		glRotated(theta3,0,1,0);  //rotate planet about itself
		glColor3f(0.988,0.929,0.207);
		glScaled(0.4,0.4,0.4);	//SATURN
		saturn();
			glColor3f(0.988,0.929,0.207);
		glScaled(1.0,0.1,1.0);		//sphere scaled to ring
		ring(1.5,1.0);
		ring(1.75,1.0);
		ring(2.0,1.0);
	glPopMatrix();
	glPushMatrix();
		glRotated(theta,0,1,0); //rotate planet about sun
		glTranslated(-8.0,0,0);
		glRotated(theta3,0,1,0);  //rotate planet about itself
		glColor3f(0.207,0.574,0.938);
		glScaled(0.35,0.35,0.35);	//URANUS
		uranus();
			glScaled(1.0,1.0,0.1);
			glRotated(90.0,1,1,1);
		ring(1.5,0.5);
		ring(1.75,0.5);
	glPopMatrix();
	glPushMatrix();
		glRotated(theta,0,1,0); //rotate planet about sun
		glTranslated(9.0,0,0.0);
		glRotated(theta3,0,1,0);  //rotate planet about itself
		glColor3f(0.55,0.63,0.934);
		glScaled(0.4,0.4,0.4);	//NEPTUNE
		neptune();
	glPopMatrix(); 

}
//SPHERE ENDS
static GLdouble vx=0.0,vy=0.5,vz=1.0;
	
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(0.0,0.0,0.1,0.0);
	glOrtho(-10.0,10.0,-10.0,10.0,-50.0,50.0);
	glMatrixMode(GL_MODELVIEW);

	GLfloat mat_dif[]={0.5,0.5,0.5,1.0};
	GLfloat mat_spec[]={1.0,1.0,1.0,1.0};

	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_spec);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_dif);
	glMaterialf(GL_FRONT,GL_SHININESS,75.0);
	
	
	GLfloat lig_amb[]={1.0,1.0,1.0,1.0};
	GLfloat lig_dif[]={0.5,0.5,0.5,1.0};
	GLfloat lig_spec[]={1.0,1.0,1.0,1.0};

	glLightfv(GL_LIGHT0,GL_AMBIENT,lig_amb);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lig_dif);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lig_spec);

	GLfloat light_pos[]={0.0,5.0,0.0,0.0};
	GLfloat light_inten[]={0.7,0.7,0.7,1.0};

	glLightfv (GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_inten);
	
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);
		

glNewList(ARROW, GL_COMPILE);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(-0.5,0.3,0.0);
	glVertex3f(-0.2,0.3,0.0);
	glVertex3f(-0.2,0.7,0.0);
	glVertex3f(0.2,0.7,0.0);
	glVertex3f(0.2,0.3,0.0);
	glVertex3f(0.5,0.3,0.0);
	glVertex3f(0.0,0.0,0.0);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
glEndList();
}
void dis(GLdouble dist)
{
	glPushMatrix();
		glTranslated(dist,0,0);
		glCallList(ARROW);
	glPopMatrix();
}

void disp()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	
	srb();
	dispshstar();
	spaceship();
	dispplan();

	dis(-6.0);
	
	
	dispTex();
	
	//asteroid belt
	int n;
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINES);
	glColor3f(0.8,0.5,0.0);
	for(n=0;n<360;n++)
	glVertex3f(5*cos(n),0,5*sin(n));
	glEnd();	
	glDisable(GL_COLOR_MATERIAL);
	
	glLoadIdentity();
	dispstar();
	
	gluLookAt(vx,vy,vz,0.0,0.0,0.0,0.0,1.0,0.0);	
	glFlush();
	glutSwapBuffers();
}

//TEXT GENERATOR BEGINS-----------------------------------------------
int texIn=0;
char *s0="The Sun is a yellow dwarf that is about 4.6 billion years old.";
char *s1="Mercury is the smallest planet in the solar system. A year in Mercury is just 88 days long.";
char *s2="Venus rotates clockwise. A day here lasts longer than a year. It is the second brightest object in the night sky";
char *s3="Earth has a strong magnetic field. It has one natural satellite.";
char *s4="The rise and fall of tides on the Earth is caused by the moon";
char *s5="Mars is home to the tallest planet in the Solar System, Olympus Mons. It has 2 moons."; 
char *s6="Jupiter is the 4th brightest object in the Solar System and has the shortest day of all the planets. It has 64 moons.";
char *s7="Saturn has 62 moons.";
char *s8="Uranus has 27 moons";

void declare(char *string)
{
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}
void dispTex()
{
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0,0.5,0.5);
	glRasterPos2f(-5.0,5.25);
	declare("Sirius");
	glRasterPos2f(8.0,7.25);
	declare("Regulus");
	glRasterPos2f(2.2,-5.25);
	declare("Bellatrix");
	while(texIn!=0)
	{
	glColor3f(0.0,0.0,1.0);
    	glRasterPos2f(-9.0,-7.0);
	switch(texIn)
	{
	
	case 1: declare(s1); break;
	case 2: declare(s2); break;
	case 3: declare(s3); break;
	case 4: declare(s4); break;
	case 5: declare(s5); break;
	case 6: declare(s6); break;
	case 7: declare(s7); break;
	case 8: declare(s8); break;
	case 9: declare(s0); break;	//sun
	default: glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		 glLoadIdentity(); break;
	}
	}
	glDisable(GL_COLOR_MATERIAL);
}

//TEXT ENDS
//MENU BEGINS---------------------------------------------------------

void menu1(int id1)
{
	switch(id1)
	{
		case 1:  dis(7.0); break;
		case 10: vx=0.0;vy=8.0; vz=5.0; break;
		case 11: vx=0.0;vy=0.5; vz=1.0; break;

	}
}
void menu2(int id2)
{	
	switch(id2)
	{
		case 2: break;
		case 3: break;
		case 4: vx=2.0;vy=0.5,vz=0.5;break;
		case 5: break;
	}
}
void menu3(int id3)
{	
	switch(id3)
	{
		case 6: vx=0;vy=8.0; vz=5.0; break;
		case 7: break;
		case 8: break;
		case 9: break;
	}
	glMatrixMode(GL_MODELVIEW);glutPostRedisplay();
}
void menu()
{
	int sub_menu1=glutCreateMenu(menu2);
	glutAddMenuEntry("Mercury",2);
	glutAddMenuEntry("Venus",3);
	glutAddMenuEntry("Earth",4);
	glutAddMenuEntry("Mars",5);
	int sub_menu2=glutCreateMenu(menu3);
	glutAddMenuEntry("Jupiter",6);
	glutAddMenuEntry("Saturn",7);
	glutAddMenuEntry("Uranus",8);
	glutAddMenuEntry("Neptune",9); 
	glutCreateMenu(menu1);
	glutAddMenuEntry("The Sun",1);
	glutAddSubMenu("Terrestrial Planets",sub_menu1);
	glutAddSubMenu("Giant Planets",sub_menu2);
	glutAddMenuEntry("Top View",10);
	glutAddMenuEntry("Normal Mode",11);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
}
//MENU ENDS
void myreshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-10.0,10.0,-10.0*(GLfloat)h/(GLfloat)w,10.0*(GLfloat)h/(GLfloat)w,-50.0,50.0);
	else
		glOrtho(-10.0*(GLfloat)w/(GLfloat)h,10.0*(GLfloat)w/(GLfloat)h,-10.0,10.0,-50.0,50.0);
	glMatrixMode(GL_MODELVIEW);
	disp();
}
void idle()
{
	theta+=0.5; theta2+=0.05; theta3+=0.1; theta4-=0.5; theta1+=0.1;
	if(theta>360.0) theta-=360.0;
	if(theta1>360.0) theta-=360.0;
	if(theta2>360.0) theta2-=360.0;
	if(theta3>360.0) theta3-=360.0;
	if(theta4>0.0) theta4=-360.0;
	glutPostRedisplay();
}

int main( int argc, char** argv )
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glEnable (GL_NORMALIZE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(750,750);
    glutCreateWindow("Rotation");
    init();
    menu();
    glutDisplayFunc(disp);
    glutIdleFunc(idle);
    glutMainLoop();

    return(0);			
}
