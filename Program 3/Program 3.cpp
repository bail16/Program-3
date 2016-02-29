#include "stdafx.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Pocztkowy rozmiar i pozycja prostokta
//GLfloat x1 = 100.0f;
//GLfloat y1 = 150.0f;
GLsizei rsize = 50;

// Wspolrzedne wielokata

GLfloat x0 = 50.0, y0 = 140;
GLfloat x1 = 50.0, y1 = 170.0;
GLfloat x2 = 79.0, y2 = 165.0;
GLfloat x3 = 85.0, y3 = 120.0;
GLfloat x4 = 35.0, y4 = 110.0;
GLfloat x5 = 15.0, y5 = 140.0;

//sterownik switcha
GLint ster = 0;


// Rozmiar kroku (liczba pikseli) w osi x i y
GLfloat xstep = 3.0f;
GLfloat ystep = 3.0f;
GLfloat step = 3.0f;
// Dane zmieniajcych siê rozmiarów okna
GLfloat windowWidth;
GLfloat windowHeight;
///////////////////////////////////////////////////////////
void ChangeCordX(int value)
{
	x0 += value;
	x1 += value;
	x2 += value;
	x3 += value;
	x4 += value;
	x5 += value;
}
void ChangeCordY(int value)
{
	y0 += value;
	y1 += value;
	y2 += value;
	y3 += value;
	y4 += value;
	y5 += value;
}

// Wywo³ywana w celu przerysowania sceny
void RenderScene(void) {
	// Wyczyszczenie okna aktualnym kolorem czyszcz¹cym
	glClear(GL_COLOR_BUFFER_BIT);

	// Aktualny kolor rysuj¹cy - czerwony
	//	R	G	B
	glColor3f(1.0f, 0.0f, 0.0f);

	// Narysowanie prostok¹ta wype³nionego aktualnym kolorem
	glBegin(GL_TRIANGLES);
	glVertex2f(x0, y0);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);

	glVertex2f(x0, y0);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);

	glVertex2f(x0, y0);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);

	glVertex2f(x0, y0);
	glVertex2f(x4, y4);
	glVertex2f(x5, y5);

	glVertex2f(x0, y0);
	glVertex2f(x5, y5);
	glVertex2f(x1, y1);

	glEnd();

	// Wys³anie poleceñ do wykonania - !!! dla animacji to jest inne polecenie
	glutSwapBuffers();
}
///////////////////////////////////////////////////////////
// Wywo³ywana przez bibliotek GLUT w czasie, gdy okno nie
// jest przesuwane ani nie jest zmieniana jego wielkoœæ
void TimerFunction(int value) {
	// Odwrócenie kierunku, je¿eli osi¹gniêto lew¹ lub praw¹ krawêdŸ
	if (x0 > windowWidth - rsize || x0 < 40) 
	{
		ChangeCordX(-step);
		ster = 0;
		xstep = -xstep;
		step = -step;
	}

	// Odwrócenie kierunku, je¿eli osi¹gniêto doln¹ lub górn¹ krawêdŸ
	else if (y0 > windowHeight - rsize || y0 < 40)
	{
		ChangeCordY(-step);
		ster = 1;
		ystep = -ystep;
		ster = 1;
	}


	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno     
	// zmniejszy³o swoj wielkoœæ w czasie, gdy kwadrat odbija³ siê od     
	// krawêdzi, co mog³oby spowodowaæ, ¿e znalaz³ by siê poza      
	// przestrzeni¹ ograniczajc¹.     
	
	if (x0 > windowWidth - rsize)
		x0 = windowWidth - rsize - 1;

	if (y0 > windowHeight - rsize)
		y0 = windowHeight - rsize - 1;

	// Wykonanie przesuniêcia kwadratu

	switch (ster)
	{
	case 0:
		ChangeCordY(ystep);
		break;
	case 1:
		ChangeCordX(xstep);
		break;
	default:
		break;
	}

	// Ponowne rysowanie sceny z nowymi wspó³rzêdnymi  
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}
///////////////////////////////////////////////////////////
// Konfigurowanie stanu renderowania
void SetupRC(void) {
	// Ustalenie niebieskiego koloru czyszcz¹cego     
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}
///////////////////////////////////////////////////////////
// Wywo³ywana przez bibliotek GLUT przy ka¿dej zmianie wielkoœci okna
void ChangeSize(GLsizei w, GLsizei h) {
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;

	// Ustalenie wielkoœci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie uk³adu wspó³rzêdnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Keep the square square, this time, save calculated
	// width and height for later use
	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	// Ustanowienie przestrzeni ograniczaj¹cej (lewo, prawo, dó³, góra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
///////////////////////////////////////////////////////////
// G³ówny punkt wejœcia programu
void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Bounce");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}
