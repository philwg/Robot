#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include "Robot.h"
#include "Mesh.h"
#include "Ground.h"
#include "Forest.h"
#include "Cadeau.h"

/** Déclarations ******************************************************/

Robot *gRobot;
Ground *gGround;
Point3D CameraPos;
Forest *pForest;
Cadeau *pCadeau;

bool DrawBoundingSphere = false;
GLuint window;
char presse = 0;
int x, y, oldx, oldy;
int IDLE = 1;

/** Classe interne ****************************************************/

class RobMesh : public Mesh {
	public:
		RobMesh();
};

/** Gestion des évènements clavier ************************************/

void clavier(unsigned char touche, int x, int y)
{
	switch (touche) {
  
		case 'd':
			glEnable(GL_DEPTH_TEST);
			glutPostRedisplay();
			break;
		
		case 'D':
			glDisable(GL_DEPTH_TEST);
			glutPostRedisplay();
			break;
	
		case 'i':
			IDLE = 1-IDLE;
			glutPostRedisplay();
			break;

		case 'q': 
			exit(0);
		
		default:
			break;
	}
}

/** Gestion du redimensionnement **************************************/

void reshape(int width, int height) 
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)(800.0f/600.0f), 0.1f, 2000.0f);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/** Gestion du clic souris ********************************************/

void mouse(int button, int state,int x,int y)
{
	// si on appuie sur le bouton gauche ...
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		// le booléen presse passe a 1 (vrai) 
		presse = 1;
		// on sauvegarde la position de la souris 
		oldx = x; 
		oldy = y;
	}
	
	// si on relache le bouton gauche, le booléen presse passe à 0 (faux) 
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) presse = 0; 
}

/** Gestion des mouvements de la souris *******************************/

void mousemotion(int x,int y)
{
	Matrix3x4 M;
	// si le bouton gauche est presse 
	if (presse) {
		// on modifie les angles de rotation de l'objet
		// en fonction de la position actuelle de la souris
		// et de la derniere position sauvegardee
		M.SetRotationY((float)(x-oldx)*0.01f);
		M.PreRotateX((float)(y-oldy)*0.01f);
		M.TransformPoints(&CameraPos, 1);
		glutPostRedisplay();
	}
	// Actualisation de la position sauvegardée
	oldx = x;
	oldy = y;
}

/** Gestion de l'affichage ********************************************/  

void affichage(void) 
{
	/** Gestion alternative de l'animation
	*
	*		gRobot->Animate(timeGetTime());
	*		int t = clock_gettime(0, &time);
	*		gRobot->Animate((unsigned)time.tv_nsec);
	*
	*/
	
	gRobot->Animate(0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	Point3D P = gRobot->GetRef().O;
	gRobot->set_CadeauNbr(pCadeau->update_At(P));
	P = P + Point3D(0.0f, 1.0f, 0.0f);
	Point3D CP = P + Point3D(CameraPos.x*gRobot->GetRef().I)
				   + Point3D(CameraPos.y*gRobot->GetRef().J)
				   + Point3D(CameraPos.z*gRobot->GetRef().K);
	gluLookAt(CP.x, CP.y, CP.z, P.x, P.y, P.z, 0, 1, 0);
	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);
	glEnable(GL_FOG);
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
		gGround->Draw();		
	    pForest->Draw();
	    pCadeau->Draw();
		gRobot->Draw();
	glDisable(GL_LIGHTING);
	glColor3f(0.3f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		gRobot->Draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glutSwapBuffers();		
}  

/** Gestion des touches spéciales du clavier **************************/

void special(int touche, int a, int b)
{
	//static int oldx,oldy;
	//int x,y;
	//Matrix3x4 M;
	
	switch (touche) {
		
		case GLUT_KEY_PAGE_UP:
			CameraPos.Set(0.0f, 0.5f, -3.0f);
			break;
			
		case GLUT_KEY_PAGE_DOWN:
			DrawBoundingSphere = !DrawBoundingSphere;
			break;
			
		case GLUT_KEY_UP:
			gRobot->TurnRight(false);
			gRobot->TurnLeft(false);
			if (pForest->noTree_inFront(gRobot->GetRef())) gRobot->Walk(true);
			else gRobot->Walk(false);
			break;
		
		case GLUT_KEY_LEFT:
			gRobot->Walk(false);
			gRobot->TurnRight(false);
			gRobot->TurnLeft(true);
			break;
			
		case GLUT_KEY_RIGHT:
			gRobot->TurnLeft(false);
			gRobot->Walk(false);
			gRobot->TurnRight(true);	
			break;
			
		default:
			break;
	}
	glutPostRedisplay();	
}

/** Lanceur de l'application ******************************************/

int main(int argc,char **argv)
{	
	// Initialisation de glut et creation de la fenetre
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	window  = glutCreateWindow("Noel");
	
	// Paramètres OpenGL
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);	
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	
	// Initialisation des lumières
	GLfloat light_ambient[] =	{  0.2f, 0.2f,   0.2f, 1.0f};
	GLfloat light_diffuse[] =	{  1.0f, 1.0f,   1.0f, 1.0f};
	GLfloat light_specular[] =	{  1.0f, 1.0f,   1.0f, 1.0f};
	GLfloat light_position[] =	{100.0f, 0.0f, 100.0f, 0.0f};
	GLfloat global_ambient[] =	{  0.2f, 0.2f,   0.2f, 1.0f};
	
	glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv (GL_LIGHT_MODEL_AMBIENT, global_ambient);
	
	// Paramètres Fog
	GLfloat fogColor[4]= {0.5f, 0.5f, 0.8f, 1.0f};	// Fog Color
	glFogi(GL_FOG_MODE, GL_LINEAR );				// Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);				// Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.1f);					// How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);				// Fog Hint Value
	glFogf(GL_FOG_START, 1.0f);						// Fog Start Depth
	glFogf(GL_FOG_END, 50.0f);						// Fog End Depth
	glEnable(GL_FOG);								// Enables GL_FOG
	
	// Enregistrement des fonctions de rappel
	glutDisplayFunc(affichage);
	glutKeyboardFunc(clavier);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemotion);
	// glutIdleFunc(idle);
	
	// Entree dans la boucle principale glut
	CameraPos.Set(0.0f, 0.5f, -3.0f);
	gRobot = new Robot();
	gGround = new Ground(100.0f, 100);
	pForest = new Forest(gGround, 100);
	pCadeau = new Cadeau(12, gGround, pForest);
	gRobot->StartAnimation(0);
	glutMainLoop();
	
	// Nettoyage
	delete pCadeau;
	delete pForest;
	delete gGround;
	delete gRobot;
	
	// Sortie
	return 0;
}
