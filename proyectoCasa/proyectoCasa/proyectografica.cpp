

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


//NEW// Keyframes
//Variables de dibujo y manipulacion
float posX =0, posY = 2.5, posZ =-3.5, rotRodIzq = 0;
float giroMonito = 0;

#define MAX_FRAMES 5
int i_max_steps = 90;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotInc;
	float giroMonito;
	float giroMonitoInc;
	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=0;			//introducir datos
bool play=false;
int playIndex=0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01
CTexture text7; // purta verde


//NEW///////////////////////////7

CTexture textMesa;
CTexture textPata;
CTexture textWall;
CTexture textSilla;
CTexture textTecho;
CTexture textMarble;
CTexture textPiso;
CTexture textGlassWasser;
CTexture textBarrote;
CTexture textCuadro1;
CTexture textCuadro2;
CTexture textCuadro3;
CTexture textMarco;
CTexture textLibroCG;
CTexture textPB;
CTexture textPuerta;
CTexture textPuerta_princ;
CTexture textMarco_1;
CTexture textMarco_2;
CTexture textMarco_3;
CTexture textGrass;
CTexture textSky;
CTexture textLibrero;
CTexture texttapete;

//***ROSE****
CTexture textAlmohada;
CTexture textColcha;
CTexture textMaderaBuro;
CTexture textMaderaCama;
CTexture textMor;
CTexture textclima;
CTexture textr;
CTexture textrojo;
CTexture textLampara;
CTexture textLaptop;
CTexture textPantalla;
CTexture textTeclado;
CTexture textTouchPad;
CTexture textGW;
CTexture texttap;

//CFiguras fig1;
//CFiguras fig5;
CFiguras tablaMesa;
CFiguras pata1Mesa;
CFiguras pata2Mesa;
CFiguras pata3Mesa;
CFiguras pata4Mesa;
CFiguras asientoSilla;
CFiguras respaldoSilla1;
CFiguras respaldoSilla2;
CFiguras respaldoSilla3;
CFiguras respaldoSilla4;
CFiguras techoCasa;
CFiguras pisoCasa;
CFiguras cubo;
CFiguras sky;
CFiguras tapete;
CFiguras banco;
CFiguras pelotapixar;//mio 
//*****ROSE*****

CFiguras cama;
CFiguras buro;
CFiguras cono;
CFiguras lampara;
CFiguras laptop;

float abrirPuerta = 0;


//END NEW//////////////////////////////////////////

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito


void saveFrame ( void )
{
	
	printf("frameindex %d\n",FrameIndex);			

	KeyFrame[FrameIndex].posX=posX;
	KeyFrame[FrameIndex].posY=posY;
	KeyFrame[FrameIndex].posZ=posZ;

	KeyFrame[FrameIndex].rotRodIzq=rotRodIzq;
	KeyFrame[FrameIndex].giroMonito=giroMonito;
			
	FrameIndex++;
}

void resetElements( void )
{
	posX=KeyFrame[0].posX;
	posY=KeyFrame[0].posY;
	posZ=KeyFrame[0].posZ;

	rotRodIzq=KeyFrame[0].rotRodIzq;
	giroMonito=KeyFrame[0].giroMonito;

}

void interpolation ( void )
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;	
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;	
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;	

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;	
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

}


void ciudad ()
{


}

void monito()
{
	
}



//NEW CASA//////////////////////////////////////



void mesa(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosMesa, GLfloat yPosMesa, GLfloat zPosMesa){
	//mesa	
		//tabla
		glPushMatrix();
			glScalef(xMadera, yMadera, zMadera);
			glTranslatef(xPosMesa, yPosMesa, zPosMesa);
			glPushMatrix();
				glScalef(10,.5,5);
				tablaMesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
			//patas
			glPopMatrix();
			glPushMatrix();
				glTranslatef(4, -2.75, 2);
				glScalef( .5,5,.5);
				pata1Mesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
				glTranslatef(0, 0, -8);
				pata2Mesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
				glTranslatef(-16, 0, 0);
				pata3Mesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
				glTranslatef(0, 0, 8);
				pata4Mesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
			glPopMatrix();
		glPopMatrix();

		return;
}

void silla(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosSilla, GLfloat yPosSilla, GLfloat zPosSilla){
	float numBarrotes = -2.9;
	glPushMatrix();
		//posicion y tamaño
		glScalef(xMadera, yMadera, zMadera);
		glTranslatef(xPosSilla, yPosSilla, zPosSilla);
		//figura
		glPushMatrix();
			glScalef(3,.5,3);
			asientoSilla.prisma (1.0, 1.0, 1.0, textSilla.GLindex);//1
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.35, -3.25,-1.35);
			glScalef( .3,6,.3);
			pata1Mesa.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
			glTranslatef(-9.0, 0, 0);
			pata2Mesa.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
			glTranslatef(0, 0, 9);
			pata3Mesa.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
			glTranslatef(9, 0, 0);
			pata4Mesa.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.45, 4.25, -1.45);
			glScalef( 0.1,8.0,0.1);
			respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
			for(int numBar = 1; numBar <= 10; numBar++){
				glTranslatef(numBarrotes,0,0);
				respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
			}
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,1,-1.45);
			glScalef( 2.3,0.1,0.1);
			respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
			//
			for(int numBar = 1; numBar <= 30; numBar++){
				glTranslatef(0,2,0);
				respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
			}
			glTranslatef(0,12,0);
			glScalef( 1.5,1,1);
			respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
		glPopMatrix();
	glPopMatrix();

	return;
}

void comedor(void){
	glPushMatrix();
			mesa(2,2,2,0,1,0);
	glPopMatrix();
	//SILLAS
	//glPushMatrix();
		//glTranslatef(13,0,-0.5);
		//glRotatef(25, 0,90,0);
		//glTranslatef(-10,0,-5.0);
		//silla(1,1,1,5,-1,-4.5);
		//glPopMatrix();
		glPushMatrix();
			silla(2,1.5,1,-5,1,-5.5);
	glPopMatrix();
	glPushMatrix();
			silla(1,1,1,0,-1,-4.5);
	glPopMatrix();
		//giramos con respecto Z
		glScalef(1,1,-1);
		glPushMatrix();				
		glPushMatrix();
			silla(1,1,1,5,-1,-4.5);
	      glPopMatrix();
		glPushMatrix();
			silla(1,1,1,-5,-1,-4.5);
		glPopMatrix();
		glPushMatrix();
			silla(1,1,1,0,-1,-4.5);
		glPopMatrix();
	glPopMatrix();
		return;
}
void ropero(void){ //ropero puerta xD
			glPushMatrix();
				glTranslatef(45,-20,110);
				glRotatef(90, 0, 50, 0);
				fig5.prisma(52.0,2.0,15.0, textPuerta.GLindex);
			glPopMatrix();

			//fachada piso
			glPushMatrix();
			glTranslatef(50, -45, 130);
			glScalef(120.0, 6.0, 38.0);
			glRotatef(90, 0, 50, 0);
			fig5.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
			glPopMatrix();
			//fachada techo
			glPushMatrix();
			glTranslatef(50, 20, 130);
			glScalef(120.0, 6.0, 38.0);
			glRotatef(90, 0, 50, 0);
			fig5.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
			glPopMatrix();

			//fachada columna izq
			glPushMatrix();
			glTranslatef(20, -10, 140);
			glScalef(5.0, 70.0, 5.0);
			glRotatef(90, 0, 50, 0);
			fig5.prisma(1.0, 1.0, 1.0, textMaderaBuro.GLindex);
			glPopMatrix();
			//fachada columna der
			glPushMatrix();
			glTranslatef(70, -10, 140);
			glScalef(5.0, 70.0, 5.0);
			glRotatef(90, 0, 50, 0);
			fig5.prisma(1.0, 1.0, 1.0, textMaderaBuro.GLindex);
			glPopMatrix();




			//glPushMatrix();
			//glTranslatef(-5.5,-20,35);
				//glRotatef(180,1,0,0);
			//	fig5.prisma(1.0,6.0,50.0, textGW.GLindex);
			//glPopMatrix();
			//glPushMatrix();
			//	glTranslatef(-5.5,-20,65);
			//	glRotatef(90,1,0,0);
				//fig5.prisma(1.0,6.0,50.0, textGW.GLindex);
			//glPopMatrix();
			//glPushMatrix();
			//	glTranslatef(-5.5,-20,57.5);
			//	glRotatef(90,1,0,0);
				//	fig5.prisma(0.5,6.0,50.0, textGW.GLindex);
			//glPopMatrix();
			//glPushMatrix();
			//	glTranslatef(-5.5,-20,42.5);
				//glRotatef(90,1,0,0);
			//	fig5.prisma(0.5,6.0,50.0, textGW.GLindex);
			//glPopMatrix();
			//glPushMatrix();
			//	glTranslatef(-5.5,-45,50);
			//	fig5.prisma(0.5,6.0,31.0, textGW.GLindex);
			//glPopMatrix();
			//glPushMatrix();
			//	glTranslatef(-5.5,5,50);
			//	fig5.prisma(0.5,6.0,31.0, textGW.GLindex);
			//glPopMatrix();
			//glPushMatrix();
			//	glTranslatef(-5.5,-20,50);
			//	fig5.prisma(0.5,6.0,30.0, textGW.GLindex);
			//glPopMatrix();
		//	glPushMatrix();
			//	glTranslatef(-5.5,-30,50);
				//		fig5.prisma(0.5,6.0,30.0, textGW.GLindex);
			//glPopMatrix();
			//glPushMatrix();
			//	glTranslatef(-5.5,-10,39);
			//	fig5.prisma(0.5,6.0,7.5, textGW.GLindex);
			//glPopMatrix();
			//glPushMatrix();
			//	glTranslatef(-5.5,-10,61);
				//fig5.prisma(0.5,6.0,7.5, textGW.GLindex);
			//glPopMatrix();
}
void casa( void ){
//*****casa*****
	glPushMatrix(); //Creamos paredes
		glTranslatef(0,20,0);
		fig1.skybox2(60.0, 85.0, 85.0, textPata.GLindex);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,50,0);
		techoCasa.prisma(1,90,90, textTecho.GLindex);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-10,0);
		pisoCasa.prisma(1,85,85, textPiso.GLindex);
		//patio
		glTranslatef(0,-3,0);
		pisoCasa.prisma(1,250,250, textGrass.GLindex); //habilite el piso alrededor de la casa
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-27.5,10,-42);
		pisoCasa.prisma(40,30,1, textPata.GLindex);
		glTranslatef(30,0,0);
		pisoCasa.prisma(40,30,1, textPata.GLindex);
		glTranslatef(15,0,0);
		pisoCasa.prisma(40,30,1, textPata.GLindex);
		glPushMatrix();
			glTranslatef(15.5,0,0);
			pisoCasa.prisma(40,1,1, textPata.GLindex);// marco puerta drecha
			glTranslatef(9,0,0);
			pisoCasa.prisma(40,1,1, textPata.GLindex); //marco derecha
			glTranslatef(-4.5,18.5,0);
			pisoCasa.prisma(2.5,8,1, textPata.GLindex); //marco enmedio
		glPopMatrix();
		//puerta
		
		glTranslatef(15,-1,0);
		glRotatef(abrirPuerta, 0,1,0);
		glTranslatef(5,-0.4,0);//eran 20 en x
		pisoCasa.prisma(37,8,1, textPata.GLindex);
	glPopMatrix();
			
	//ventana 1
	glPushMatrix();
		glTranslatef(-34.5,38.5,-42);
		cubo.prisma(16.5,15,1, textPata.GLindex);
	glPopMatrix();
	//barrotes ventana
	glPushMatrix();
		glTranslatef(-42,38.5,-42);
		cubo.prisma(17,0.8,1, textPata.GLindex);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-27,38.5,-42);
		cubo.prisma(17,0.8,1, textPata.GLindex);
	glPopMatrix();
	//ventana 2
	glPushMatrix();
		glTranslatef(-19,38.5,-42);
		cubo.prisma(16.5,15,1, textPata.GLindex);
	glPopMatrix();
	//barrote
	glPushMatrix();
		glTranslatef(-11,38.5,-42);
		cubo.prisma(17,0.8,1, textPata.GLindex);
	glPopMatrix();
	//ventana 3
	glPushMatrix();
		glTranslatef(-3,38.5,-42);
		cubo.prisma(16.5,15,1, textPata.GLindex);
	glPopMatrix();
	//ventana 4
	glPushMatrix();
	glTranslatef(-13, 15.0, -42);
	cubo.prisma(16.5, 15, 1.2, textGlassWasser.GLindex);
	glPopMatrix();
	///ventana 5
	
	//ventana 6
	glPushMatrix();
	glTranslatef(20, 15.0, -42);
	cubo.prisma(16.5, 15, 1.2, textGlassWasser.GLindex);
	glPopMatrix();
	//ventana 7
	glPushMatrix();
	glTranslatef(42.5, 15.0, 0);
	glRotatef(90, 0, 50, 0);
	cubo.prisma(16.5, 15, 0.1, textGlassWasser.GLindex);
	glPopMatrix();
	//ventana 8
	glPushMatrix();
	glTranslatef(-42.5, 15.0, 0);
	glRotatef(90, 0, 50, 0);
	cubo.prisma(16.5, 15, 0.1, textGlassWasser.GLindex);
	glPopMatrix();

	//pared arriba inclinada
	//glPushMatrix();
	//glPushMatrix();
	//glTranslatef(-42.5, 95.0, 0);
	//glRotatef(40, 40, 0, 0);
	//cubo.prisma(90.5, 90, 0.1, textGlassWasser.GLindex);
	//glPopMatrix();





	//barrote
	glPushMatrix();
		glTranslatef(5,38.5,-42);
		cubo.prisma(17,0.8,1, textPata.GLindex);
	glPopMatrix();
	//ventana 4
	glPushMatrix();
		glTranslatef(13,38.5,-42);
		cubo.prisma(16.5,15,1, textPata.GLindex);
	glPopMatrix();
	//ventana 5
	  //  glPushMatrix();
		//glTranslatef(100, 38.5, -42);
	   // cubo.prisma(16.5, 15, 1, textGlassWasser.GLindex);
	   // glPopMatrix();
	//barrote
	glPushMatrix();
		glTranslatef(19.8,38.5,-42);
		cubo.prisma(17,0.8,1, textPata.GLindex);
	glPopMatrix();	
	//cierra ventana
	glPushMatrix();
		glTranslatef(31,38.5,-42);
		cubo.prisma(17,23,1, textPata.GLindex);
	glPopMatrix();
	return;
}

void cuadro(void){
	glPushMatrix();
		glScalef(1,1,-1);
		glTranslatef(19,30,-42);
		cubo.prisma(16,15,.2, textCuadro2.GLindex);
		glTranslatef(0,0,-.05);
		//cubo.prisma(17,16,.05, textMarco.GLindex);
	glPopMatrix();
	return;
}

void sillon(void) {
	glPushMatrix();
	glScalef(10, 10, -10);
	glTranslatef(19, 30, -42);
	cubo.prisma(16, 15, .2, textCuadro2.GLindex);
	glTranslatef(10, 0, -.05);
	//cubo.prisma(17,16,.05, textMarco.GLindex);
	glPopMatrix();
	return;
}
//****ROSE****
void dibujaCama (GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosCama, GLfloat yPosCama, GLfloat zPosCama)
{			
			glPushMatrix(); 
			glScalef(xMadera, yMadera, zMadera); //posicion y tamaño 
			glTranslatef(xPosCama, yPosCama, zPosCama); //figura 

			//dibujamos la cabecera
			//glPushMatrix(); 
			////	glTranslatef(9.0,1.5,0.5);
				//glScalef(18.0,3.0,1.0);  //Tamaño de cabecera
				//cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			//glPopMatrix();

			//glPushMatrix(); 
			//	glTranslatef(0.5,6.0,0.5);
			//	glScalef(1.0,6.0,1.0);  
				//cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			//glPopMatrix();

			//glPushMatrix(); 
			//	glTranslatef(4.0,6.0,0.5);
			//	glScalef(4.0,6.0,1.0);  
				//cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			//glPopMatrix();


			//reloj
			glPushMatrix(); 
				glTranslatef(8.0,10.0,0.5);
				glScalef(8.0,25.0,3.0);  
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(8.0, 10.0, 2.0);
			glScalef(4.0, 12.0, 1.0);
			cama.prisma(1.0, 1.0, 1.0, textr.GLindex);
			glPopMatrix();
			//manesillas del reloj
			glPushMatrix();
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			glRotatef(270, 180, 10, 0);
			glTranslatef(9.0, -2.0, 18.0);
			tapete.cilindro(2.0, .5, 20.0, textr.GLindex);
			glDisable(GL_ALPHA_TEST);
			glPopMatrix();

			

			

			//centro clima
			glPushMatrix(); 
				glTranslatef(8.0,35.0,0.0);
				glScalef(5.0,5.0,2.0);
				cama.prisma(1.0,1.0,1.0, textclima.GLindex);
			glPopMatrix();

			//marco clima
			glPushMatrix(); 
				glTranslatef(8.0,32.0,0.0);
				glScalef(5.0,1.0,2.0);
				cama.prisma(1.0,1.0,1.0, textMor.GLindex);
			glPopMatrix();
			//marco clima arriba
			glPushMatrix();
			glTranslatef(8.0, 37.0, 0.0);
			glScalef(5.0, 1.0, 2.0);
			cama.prisma(1.0, 1.0, 1.0, textMor.GLindex);
			glPopMatrix();
			//marco clima izq
			glPushMatrix();
			glTranslatef(5.0, 34.5, 0.0);
			glScalef(1.0, 6.0, 2.0);
			cama.prisma(1.0, 1.0, 1.0, textMor.GLindex);
			glPopMatrix();
			//marco clima der
			glPushMatrix();
			glTranslatef(11.0, 34.5, 0.0);
			glScalef(1.0, 6.0, 2.0);
			cama.prisma(1.0, 1.0, 1.0, textMor.GLindex);
			glPopMatrix();

			
		glPopMatrix();
}


void dibujaBuro(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosBuro, GLfloat yPosBuro, GLfloat zPosBuro)
{
		glPushMatrix();		
			glScalef(xMadera, yMadera, zMadera); 
			glTranslatef(xPosBuro, yPosBuro, zPosBuro); //figura 
			//contorno
			glPushMatrix();
				glTranslatef(7.0,5.5,65.0);
				glScalef(1.0,11.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-7.0,5.5,65.0); //pata adelante derecha
				glScalef(1.0,11.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(6.5,5.5,75); //pata buro atras izq
				glScalef(1.0,11.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-6.5,5.5,75); //pata buro atras der
				glScalef(1.0,11.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			//glPushMatrix();
			//	glTranslatef(8.0,10.5,70); // tabla
			//	glScalef(12.0,1.0,1.0);
				//buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			//glPopMatrix();

			//glPushMatrix();
			//	glTranslatef(1.5,10.5,70.0);
			//	glScalef(1.0,1.0,6.0);
				//	buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			//glPopMatrix();

			//glPushMatrix();
			//	glTranslatef(14.5,10.5,5.0);
			//	glScalef(1.0,1.0,6.0);
			//	buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			//glPopMatrix();


			//	glPushMatrix();
			//	glTranslatef(8.0,6.5,8.5);
			//	glScalef(12.0,1.0,1.0);
			//	buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			//glPopMatrix();

			//glPushMatrix();
			//	glTranslatef(1.5,6.5,5.0);
			//	glScalef(1.0,1.0,6.0);
				//buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			//glPopMatrix();

			//glPushMatrix();
            //glTranslatef(14.5,6.5,5.0);
			//	glScalef(1.0,1.0,6.0);
			//	buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			//glPopMatrix();

			//glPushMatrix();
				//glTranslatef(8.0,2.5,1.5);
				//glScalef(12.0,1.0,1.0);
				//buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			//glPopMatrix();

			//glPushMatrix();
			//	glTranslatef(8.0,2.5,8.5);
			//	glScalef(12.0,1.0,1.0);
				//buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			//glPopMatrix();

			//glPushMatrix();
			//	glTranslatef(1.5,2.5,5.0);
				//glScalef(1.0,1.0,6.0);
			////	buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			//glPopMatrix();
			
			//glPushMatrix();
				//glTranslatef(14.5,2.5,5.0);
				//glScalef(1.0,1.0,6.0);
				//buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			//glPopMatrix();

			//rellenos
			glPushMatrix();
				glTranslatef(7.6,6.5,70.0);
				glScalef(1.0,7.0,8.5);
				buro.prisma(1.3,1.8,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-7,6.5,70.0);
				glScalef(1.0,7.0,8.5);
				buro.prisma(1.3,1.8,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			//tapa de atras
		glPushMatrix();
			glTranslatef(0.0,6.5,75);
				glScalef(12.0,9.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			//tapa adelante
			glPushMatrix();
			glTranslatef(0.0, 6.5, 65);
			glScalef(12.0, 9.0, 1.0);
			buro.prisma(1.0, 1.0, 1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			//base arriba
			glPushMatrix();
				glTranslatef(0.0,11.5,70.0); 
				glScalef(16.0,1.0,10.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			//caja de la tv
			glPushMatrix();
			glTranslatef(0.0, 16.5, 70);
			glScalef(12.0, 10.0, 8.0);
			buro.prisma(1.0, 1.0, 1.0, textLaptop.GLindex);
			glPopMatrix();
			//pantalla
			glPushMatrix();
			glScalef(1, 1, -1);
			glTranslatef(0, 17, -66);
			cubo.prisma(8, 9, .2, textCuadro1.GLindex);
			glTranslatef(0, 0, -.05);

			
			//cubo.prisma(17,16,.05, textMarco.GLindex);
			glPopMatrix();



			//tapete
			glPushMatrix();
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			glTranslatef(0, 0, 45);
			//glColor3b(1, 1, 1);
			tapete.cilindro(12.5, 1.0, 30, texttap.GLindex);
			glDisable(GL_ALPHA_TEST);
			glPopMatrix();

			//asiento banco
			glPushMatrix();
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			glTranslatef(0, 10, 35);
			//glColor3b(1, 1, 1);
			banco.cilindro(2.5, 1.0, 20, textBarrote.GLindex);
			glDisable(GL_ALPHA_TEST);
			glPopMatrix();
			//pata banco
			glPushMatrix();
			glTranslatef(0.0, 6.5, 35);
			glScalef(0.5, 8.0, 0.5);
			buro.prisma(1.0, 1.0, 1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			//sillon asiento
			glPushMatrix();
			glTranslatef(10.0, 7.5, 35);
			glScalef(5.5, 2.0, 4.0);
			buro.prisma(1.0, 1.0, 1.0, textrojo.GLindex);
			glPopMatrix();

			//sillon recargadera
			glPushMatrix();
			glTranslatef(10.0, 10.5, 32);
			glScalef(5.5, 8.0, 2.0);
			buro.prisma(1.0, 1.0, 1.0, textrojo.GLindex);
			glPopMatrix();

			//sillon pata1
			glPushMatrix();
			glTranslatef(12.0, 5.5, 32);
			glScalef(1.0, 2.5, 1.0);
			buro.prisma(1.0, 1.0, 1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			//sillon pata2
			glPushMatrix();
			glTranslatef(12.0, 5.5, 36);
			glScalef(1.0, 2.5, 1.0);
			buro.prisma(1.0, 1.0, 1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			//sillon pata3
			glPushMatrix();
			glTranslatef(8.0, 5.5, 36);
			glScalef(1.0, 2.5, 1.0);
			buro.prisma(1.0, 1.0, 1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			//sillon pata4
			glPushMatrix();
			glTranslatef(8.0, 5.5, 32);
			glScalef(1.0, 2.5, 1.0);
			buro.prisma(1.0, 1.0, 1.0, textMaderaBuro.GLindex);
			glPopMatrix();
			// costado sillon
			glPushMatrix();
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			glRotatef(270, 180, 10, 0);
			glTranslatef(10.5, -36.2, 9.0);
			tapete.cilindro(1.0, 3.7, 20.0, textrojo.GLindex);
			glDisable(GL_ALPHA_TEST);
			glPopMatrix();

			// costado sillon
			glPushMatrix();
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			glRotatef(270, 180, 10, 0);
			glTranslatef(14.5, -36.1, 9.0);
			tapete.cilindro(1.0, 3.7, 20.0, textrojo.GLindex);
			glDisable(GL_ALPHA_TEST);
			glPopMatrix();






			////////////////////sillaa
			glPushMatrix();
			glScalef(3, .5, 3);
			asientoSilla.prisma(1.0, 1.0, 1.0, textSilla.GLindex);//1
			glPopMatrix();
			glPushMatrix();
			glTranslatef(10.35, -3.25, -1.35);
			glScalef(.3, 6, .3);
			pata1Mesa.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
			glTranslatef(-9.0, 0, 0);
			pata2Mesa.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
			glTranslatef(0, 0, 9);
			pata3Mesa.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
			glTranslatef(9, 0, 0);
			pata4Mesa.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
			glPopMatrix();











			//cajones
			//glPushMatrix();
			//	glTranslatef(8.0,8.5,9.25);
			//	glScalef(12.0,3.0,0.5);
			//	buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			//glPopMatrix();

			//glPushMatrix();
			//	glTranslatef(8.0,4.5,9.25);
			//	glScalef(12.0,3.0,0.5);
			//	buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			//glPopMatrix();

			//glPushMatrix();
			//	glTranslatef(8.0,8.5,9.75);
			//	glScalef(2.0,1.0,0.5);
			//	buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
		//	glPopMatrix();

			//glPushMatrix();
				//glTranslatef(8.0,4.5,9.75);
				////glScalef(2.0,1.0,0.5);
				//buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
				//glPopMatrix();
		//glPopMatrix();
}

//void libros( void){
	//glPushMatrix();
		//	glTranslatef(-1,-8,25);
		//	cubo.prisma(1,2,2, textLibroCG.GLindex);
		//glPopMatrix();

		//glPushMatrix();
		//	glRotatef(30, 0,1,0);
			//glTranslatef(-10,-8,25);
			//cubo.prisma(.7,2,2, textPB.GLindex);
	//glPopMatrix();
	//return;
//}
//END CASA////////////////////////////////////





GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		ciudad();
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

    
    text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
    text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();

	text7.LoadTGA("city/puertaverde.tga");
	text7.BuildGLTexture();
	text7.ReleaseImage();


	//NEW////////////////////////////////////////////

	textMesa.LoadBMP("casa/wood_5.bmp");
	textMesa.BuildGLTexture();
	textMesa.ReleaseImage();

	textPata.LoadBMP("casa/madera.bmp"); //toda la fachada
    textPata.BuildGLTexture();
	textPata.ReleaseImage();

	textWall.LoadBMP("casa/brick_2.bmp");
	textWall.BuildGLTexture();
	textWall.ReleaseImage();

	textSilla.LoadBMP("casa/madera.bmp"); //textura de las sillas
    textSilla.BuildGLTexture();
	textSilla.ReleaseImage();
	
	textTecho.LoadBMP("casa/madera.bmp");  //techo
	textTecho.BuildGLTexture();
	textTecho.ReleaseImage();

	textMarble.LoadBMP("casa/marble_2.bmp"); //mesas
	textMarble.BuildGLTexture();
	textMarble.ReleaseImage();

	texttap.LoadBMP("casa/grass_2.bmp"); //mesas
	texttap.BuildGLTexture();
	texttap.ReleaseImage();

	textPiso.LoadBMP("casa/floor-parquet.bmp");
	textPiso.BuildGLTexture();
	textPiso.ReleaseImage();

	textGlassWasser.LoadBMP("casa/glass_2.bmp");
	textGlassWasser.BuildGLTexture();
	textGlassWasser.ReleaseImage();

	textBarrote.LoadBMP("casa/brickwall.bmp");
	textBarrote.BuildGLTexture();
	textBarrote.ReleaseImage();

	textCuadro1.LoadBMP("casa/coraje.bmp"); //cuadro_1
	textCuadro1.BuildGLTexture();
	textCuadro1.ReleaseImage();

	textCuadro2.LoadBMP("casa/grito.bmp"); //cuadro en la pared
	textCuadro2.BuildGLTexture();
	textCuadro2.ReleaseImage();

	textCuadro3.LoadBMP("casa/reloj.bmp"); //reloj
	textCuadro3.BuildGLTexture();
	textCuadro3.ReleaseImage();

	textMarco.LoadBMP("casa/burned wood.bmp");
	textMarco.BuildGLTexture();
	textMarco.ReleaseImage();

	textLibroCG.LoadBMP("casa/gc_donald.bmp");
	textLibroCG.BuildGLTexture();
	textLibroCG.ReleaseImage();

	textPuerta.LoadBMP("casa/door_3.bmp");  //door_3 puertaverde2
	textPuerta.BuildGLTexture();
	textPuerta.ReleaseImage();

	textPuerta_princ.LoadBMP("casa/door_3_4_puerta.bmp");
	textPuerta_princ.BuildGLTexture();
	textPuerta_princ.ReleaseImage();

	//textPuerta_princ.LoadBMP("casa/pelotapixar.bmp");
	//textPuerta_princ.BuildGLTexture();
	//textPuerta_princ.ReleaseImage();

	textMarco_1.LoadBMP("casa/door_3_1_izq.bmp");
	textMarco_1.BuildGLTexture();
	textMarco_1.ReleaseImage();

	textMarco_2.LoadBMP("casa/door_3_2_der.bmp");
	textMarco_2.BuildGLTexture();
	textMarco_2.ReleaseImage();

	textMarco_3.LoadBMP("casa/door_3_3_cen.bmp");
	textMarco_3.BuildGLTexture();
	textMarco_3.ReleaseImage();

	textGrass.LoadBMP("casa/maderaburo.bmp");
	textGrass.BuildGLTexture();
	textGrass.ReleaseImage();

	textSky.LoadBMP("casa/blue-sky-texture.bmp");
	textSky.BuildGLTexture();
	textSky.ReleaseImage();

	textLibrero.LoadBMP("casa/strata.bmp");
	textLibrero.BuildGLTexture();
	textLibrero.ReleaseImage();

	textGW.LoadBMP("casa/glass window.bmp");
	textGW.BuildGLTexture();
	textGW.ReleaseImage();

	// mis texturas
	texttapete.LoadBMP("puertaverde2.bmp");
	texttapete.BuildGLTexture();
	texttapete.ReleaseImage();

	
	//*****ROSE******
	textAlmohada.LoadBMP("casa/almohada.bmp");
	textAlmohada.BuildGLTexture();
	textAlmohada.ReleaseImage();

	textColcha.LoadBMP("casa/colcha.bmp");
	textColcha.BuildGLTexture();
	textColcha.ReleaseImage();

	textMaderaBuro.LoadBMP("casa/buro.bmp");
	textMaderaBuro.BuildGLTexture();
	textMaderaBuro.ReleaseImage();
	///////////////////clima
	textMor.LoadBMP("casa/morado.bmp");
	textMor.BuildGLTexture();
	textMor.ReleaseImage();

	textclima.LoadBMP("casa/clima.bmp");
	textclima.BuildGLTexture();
	textclima.ReleaseImage();

	textr.LoadBMP("casa/reloj3.bmp");
	textr.BuildGLTexture();
	textr.ReleaseImage();

	textrojo.LoadBMP("casa/app.bmp");
	textrojo.BuildGLTexture();
	textrojo.ReleaseImage();


	//////////////////clima
	textMaderaCama.LoadBMP("casa/maderaCama.bmp");
	textMaderaCama.BuildGLTexture();
	textMaderaCama.ReleaseImage();

	textLampara.LoadBMP("casa/lampara.bmp");
	textLampara.BuildGLTexture();
	textLampara.ReleaseImage();

	textLaptop.LoadBMP("casa/laptop.bmp");
	textLaptop.BuildGLTexture();
	textLaptop.ReleaseImage();

	textPantalla.LoadBMP("casa/windows.bmp");
	textPantalla.BuildGLTexture();
	textPantalla.ReleaseImage();

	textTeclado.LoadBMP("casa/tecla.bmp");
	textTeclado.BuildGLTexture();
	textTeclado.ReleaseImage();

	textTouchPad.LoadBMP("casa/touchpad.bmp");
	textTouchPad.BuildGLTexture();
	textTouchPad.ReleaseImage();

	//END NEW//////////////////////////////

	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;
		KeyFrame[i].rotRodIzq =0;
		KeyFrame[i].rotInc =0;
		KeyFrame[i].giroMonito =0;
		KeyFrame[i].giroMonitoInc =0;
	}
	//NEW//////////////////NEW//////////////////NEW///////////

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glPushMatrix();
	

	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
					fig1.skybox(130.0, 130.0, 130.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glEnable ( GL_COLOR_MATERIAL );
					glColor3f(1, 1, 1);
					//glScalef(0.5, 0.5, 0.5);
					//monito();
					glCallList(ciudad_display_list);
					glTranslatef(posX, posY, posZ);
					glRotatef(giroMonito, 0, 1, 0);
					monito();
				glDisable ( GL_COLOR_MATERIAL );
			glPopMatrix();			

			//glPushMatrix(); //Flecha
				//glScalef(7,0.1,7);
			//	glDisable(GL_LIGHTING);
				////fig3.prisma_anun(text3.GLindex, 0);
				//glEnable(GL_LIGHTING);
			//glPopMatrix();


			//CASA///////////////////
			//¨****casa*****
			glPushMatrix();
				glScalef(1.0, 0.5, 1.0);
				glTranslatef(-2, 3, -30.2);
				glRotatef(180, 0, 1, 0);
				glDisable(GL_LIGHTING);
				glScalef(0.5, 0.5, 0.35);
					casa();
				
				glPushMatrix();
					//****cuadros***			
					cuadro();
					// sillon

					//****LIBROS****
					glPushMatrix();
						glTranslatef(26,11,4);
						//libros();	
					glPopMatrix();
					//****COMEDOR***
					glPushMatrix();
						glTranslatef(-2000,0,25);
						glScalef(1.3,1.3,1.3);
						comedor();
					glPopMatrix();
					//mesa y laptop
					glPushMatrix();
						glRotatef(90, 0,1,0);
						mesa(1,1.5,1,-20,1.4,2);
					glPopMatrix();
				
					//	glPushMatrix();
					//	glRotatef(90, 0,1,0);
					//	dibujaLaptop(.3,.3,.3,-90,9,77);
					//dglPopMatrix();

					glPushMatrix(); //silla alado del tapete
						glRotatef(140, 0,1,0);
						silla(1,1,1,-1,0,-12.5);
					glPopMatrix();

					//*****ROSE*****
					glPushMatrix(); 
						glPushMatrix();
							glTranslatef(0,0,-0.5); 
							glRotatef(90, 0,1,0); 
							glTranslatef(2,0,-0.5);
							dibujaCama(1.1,1.1,1.1,14.0,-5.5,-37.0); 
						glPopMatrix();
						glPushMatrix();
							glRotatef(90, 0,1,0); 
							dibujaBuro(1,1,1,-2,-9.5,-42.0); 
						glPopMatrix();
						glPushMatrix();
							glTranslatef(0,47,0);
							glScalef(1.2,1.2,1.2);
							lampara.cono(2.0,0.4,100,textLampara.GLindex);
						glPopMatrix();
					glPopMatrix();
					//***********
					//ropero
					glPushMatrix();
						glRotatef(180, 0,1,0);
						glTranslatef(-35,23,-35);
						glScalef(.7,.7,.7);
						ropero();
					glPopMatrix();
				glPopMatrix();

			glEnable(GL_LIGHTING);
			glPopMatrix();
					

			glColor3f(1.0,1.0,1.0);

		glPopMatrix();
	glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-11,12.0,-14.0,(void *)font,"Proyecto compu grafica Bravo Romero Brandon");
			pintaTexto(-11,8.5,-14,(void *)font,s);
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	fig3.text_izq-= 0.001;
	fig3.text_der-= 0.001;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;

	//Movimiento del monito
	if(play)
	{		
		
		if(	i_curr_steps >= i_max_steps) //end of animation between frames?
		{			
			playIndex++;		
			if(playIndex>FrameIndex-2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex=0;
				play=false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			posX+=KeyFrame[playIndex].incX;
			posY+=KeyFrame[playIndex].incY;
			posZ+=KeyFrame[playIndex].incZ;

			rotRodIzq+=KeyFrame[playIndex].rotInc;
			giroMonito+=KeyFrame[playIndex].giroMonitoInc;

			i_curr_steps++;
		}
		
	}


	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case 'k':		//
		case 'K':
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}

			break;

		case 'l':						
		case 'L':
			if(play==false && (FrameIndex>1))
			{

				resetElements();
				//First Interpolation				
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;

		case 'y':						
		case 'Y':
			posZ++;
			printf("%f \n", posZ);
			break;

		case 'g':						
		case 'G':
			posX--;
			printf("%f \n", posX);
			break;

		case 'h':						
		case 'H':
			posZ--;
			printf("%f \n", posZ);
			break;

		case 'j':						
		case 'J':
			posX++;
			printf("%f \n", posX);
			break;

		case 'b':						
			rotRodIzq++;
			printf("%f \n", rotRodIzq);
			break;

		case 'B':						
			rotRodIzq--;
			printf("%f \n", rotRodIzq);
			break;

		case 'p':						
			giroMonito++;
			break;

		case 'P':						
			giroMonito--;
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

void menuKeyFrame( int id)
{
	switch (id)
	{
		case 0:	//Save KeyFrame
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}
			break;

		case 1:	//Play animation
			if(play==false && FrameIndex >1)
			{

				resetElements();
				//First Interpolation
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;


	}
}


void menu( int id)
{
	
}



int main ( int argc, char** argv )   // Main Function
{
  int submenu;
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Practica 11"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  submenu = glutCreateMenu	  ( menuKeyFrame );
  glutAddMenuEntry	  ("Guardar KeyFrame", 0);
  glutAddMenuEntry	  ("Reproducir Animacion", 1);
  glutCreateMenu	  ( menu );
  glutAddSubMenu	  ("Animacion Monito", submenu);
 
  glutAttachMenu	  (GLUT_RIGHT_BUTTON);


  glutMainLoop        ( );          // 

  return 0;
}