//////////////////////////////////////////////////////
////BLOG LINK https://ryanmanthorp.wordpress.com /////
//////////////////////////////////////////////////////

//OpenGL Assignemt that uses what we have learned in the first semester 

#include <stdlib.h>
#include <math.h>
#include <glut.h> 
#include <iostream>
#include <IL/ilut.h>



bool TreeDrawn = false; //booleans to spawn objects
bool CubeDrawn = false;


int i, j;
// angle for the camera direction
float angle = 0.0f;

// vector for the camera direction
float lx = 0.0f;
float lz = -1.0f;
float ly = -1.0f;

// XZ position for the camera
float x = 0.0f;
float z = 5.0f;
float y = 0.0f;

// for moving the camera
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

//lighting colours
GLfloat liGreen[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat liBrown[] = { 2, 1.5, 1, 1.0 };
GLfloat liBlue[] = { 0.0, 0.0, 1, 1.0 };

//images 
GLint groundImage;
GLint skywall;

//this is for displaying text byt at this moment it does not work
void text1(const char *text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length;i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
	
}

//for loading and setting up textures
void InitTextures(void)
{
	// Define wrapping behaviour for material
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Define texture Filtering behaviour for material
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	skywall = ilutGLLoadImage("sky.jpg");
	groundImage = ilutGLLoadImage("grass1.jpg"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // Define how material is sent further down the rendering pipeline
																
}



void changeSize(int w, int h) {

	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);
}

//for creating the trees
void tree() {


	if (TreeDrawn == true) {
		// Draw tree
		glDisable(GL_TEXTURE_2D);
		glMaterialfv(GL_FRONT, GL_AMBIENT, liGreen); //apply the green lighting colour to this shape
		glTranslatef(0.0f, 5, 0.0f); //move the shape upwards
		glutSolidSphere(2.75f, 20, 20); //create a sphere
		glRotatef(90, 1.0f, 0.0f, 0.0f); //rotate the cone facing downwards
		glMaterialfv(GL_FRONT, GL_AMBIENT, liBrown); //apply the brown lighting colour to this shape
		glutSolidCone(1.15f, 10, 10, 20); //create the cone
		glEnable(GL_TEXTURE_2D); //enable textures after this item has been created
		
		glEnd();
	}
}


void cube() 
{
	if (CubeDrawn == true) {

		glDisable(GL_TEXTURE_2D);
		glBegin(GL_POLYGON);
		glMaterialfv(GL_FRONT, GL_AMBIENT, liBlue);

		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		glEnd();

		glBegin(GL_POLYGON);
	
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glEnd();


		glBegin(GL_POLYGON);
	
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glEnd();

	
		glBegin(GL_POLYGON);
	
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glEnd();

	
		glBegin(GL_POLYGON);
	
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glEnd();


		

		glEnable(GL_TEXTURE_2D);

		glFlush();



	}

}

//for calculating the camera movement
void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
	
}

//renders what we have created to the screen
void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);

	std::string text;
	text = "test";
	text1(text.data(), text.size(), 200, 200);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Set the camera
	gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f); //manipulates the lookat values in order to use mouse and keyboard values

	// Draw ground

	glEnable(GL_TEXTURE_2D); //enables textures
	glBindTexture(GL_TEXTURE_2D, groundImage); //sets the texture to be the groundImage
	//creating a large box that the scene is inside
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); //the coordinates for the textures
	glVertex3f(1000.0f, -1.0f, 1000.0f); 
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1000.0f, -1.0f, 1000.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1000.0f, -1.0f, -1000.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1000.0f, -1.0f, -1000.0f);
	//glDisable(GL_TEXTURE_2D);
	glEnd();

	//draw walls
	glBindTexture(GL_TEXTURE_2D, skywall);

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(100.0f, 100.0f, 100.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-100.0f, 100.0f, 100.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-100.0f, -100.0f, 100.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(100.0f, -100.0f, 100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(100.0f, -100.0f, -100.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-100.0f, -100.0f, -100.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-100.0f, 100.0f, -100.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(100.0f, 100.0f, -100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-100.0f, 100.0f, 100.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-100.0f, 100.0f, -100.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-100.0f, -100.0f, -100.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-100.0f, -100.0f, 100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(100.0f, 100.0f, -100.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(100.0f, 100.0f, 100.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(100.0f, -100.0f, 100.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(100.0f, -100.0f, -100.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	

	//draws an array of desired shapes
	for (i = -3; i < 3; i++)
		for (j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0, 0, j * 10.0);
			tree();
			cube();
			glPopMatrix();
		}
	glutSwapBuffers();

}
//for closing the window with escape key
void processNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27)
		exit(0);
}

//moving the camera with keyboard
void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_UP: deltaMove = 0.05f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.05f; break;
	
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;

	}
}

//altering the lookat values with mouse drag
void mouseMove(int x, int y) {


	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
		//ly = -sin(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) {


	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP) 
		{
			angle += deltaAngle;
			xOrigin = -1;
			
		}
		else 
		{
			xOrigin = x;
		}
	}
}

//setting up light properties 
void light() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);  
	glEnable(GL_LIGHTING);		
	glEnable(GL_LIGHT0);

	GLfloat qaAmbientLight[] = { 0.2, 0.2, 0.2, 1.0 }; 
													
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);  
	
	
	GLfloat qaLightPosition[] = { lx, ly, lz, 1.0 };		// to set the light position at the camera position
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);		// Set position of light0
}


//menue system 
void myMenu(GLint menuNumber)
{
	switch (menuNumber)
	{
	case 2:
		
		TreeDrawn = true; // enables bool that draws tree
		break;
	case 3:
	
		TreeDrawn = false; // disables bool that draws tree
		break;
	case 4:

		CubeDrawn = true;
		break;
	case 5:

		CubeDrawn = false;
		break;
	}
}




//main function that handles all of the functions and menue entries
int main(int argc, char **argv) 
{

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("test");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);


	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);	InitTextures();
	glCullFace(GL_BACK);

	glutCreateMenu(myMenu);
	glutAddMenuEntry("-----------------", 1); //these lines will be displayed in the menue when the user right clicks
	glutAddMenuEntry("Draw Forest", 2);
	glutAddMenuEntry("Remove Forest", 3);
	glutAddMenuEntry("-----------------", 1);
	glutAddMenuEntry("Draw Cube", 4);
	glutAddMenuEntry("Remove Cube", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	light();
	
	
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}