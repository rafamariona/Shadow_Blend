/******Dibujar sombras mediante Blend
******Parcial #3 de Rafael Mariona
******/
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>   //manejo de imagenes

GLfloat plano_s[4] = {1, 0, 0, 0};// s=x
GLfloat plano_v[4] = {0, 1, 0, 0};// v=y
GLuint texture[0];
int rotate_x=90;
//Definición del modelo de una luz
GLfloat light_Ambient [4] = { 0.2, 0.2, 0.2, 1.0};
GLfloat light_Diffuse [4] = { 1.0, 1.0, 1.0, 1.0};
GLfloat light_Position [4] = {20.0, 15.0, 10.0, 1.0};

//***********manejo de las luces**************
void luces(void){
      glEnable (GL_LIGHTING);
      glEnable (GL_LIGHT0);
      glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ambient );
      glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Diffuse );
      glLightfv(GL_LIGHT0, GL_POSITION, light_Position );
}
//Funcion que dibuja el piso
void piso(void)
{
      //Definicion de texturas
      texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
      (
          "piso.bmp", //se carga la imagen
          SOIL_LOAD_AUTO,
          SOIL_CREATE_NEW_ID,
          SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
      );
      glEnable(GL_TEXTURE_2D);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      // allocate a texture name
      glBindTexture(GL_TEXTURE_2D, texture[0]);
      //se dibuja el piso
      glBegin(GL_QUADS);
      glTexCoord2f(10,10);
      glVertex3f(-50.0f,-50.0f,0.0f);
      glTexCoord2f(0,10);
      glVertex3f(-50.0f,50.0f,0.0f);
      glTexCoord2f(10,0);
      glVertex3f( 50.0f,50.0f,0.0f);
      glTexCoord2f(0,0);
      glVertex3f( 50.0f,-50.0f,0.0f);
      glEnd();
}
void escena(void)
{
      //Esfera
      glPushMatrix();
      glEnable (GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_DST_COLOR);
      //sombra
      glColor4f(0,0,0,0.05);
      glTranslatef(5.0f, 3.0f, 0.0f);
      glutSolidSphere(5,40,30);
      glPopMatrix();
      glPushMatrix();
      glColor4f(1.0, 0.0, 0.0,0.95);
      glTranslatef(5.0f, 0.0f, 0.0f);
      glutSolidSphere(5,40,30);
      glDisable(GL_BLEND);
      glPopMatrix();

      //Cubo
      glPushMatrix();
      glEnable(GL_BLEND);
      //sombra
      glColor4f(0,0,0,0.05);
      glBegin(GL_POLYGON);
      glVertex3f(-3,0,0);
      glVertex3f(-3,15,0);
      glVertex3f(-14,15,0);
      glVertex3f(-14,0,0);
      glEnd();
      glColor4f(1.0, 1.0, 0.0,0.95);
      glTranslatef(-8.0f, 0.0f, 0.0f);
      glutSolidCube(10);
      glDisable(GL_BLEND);
      glPopMatrix();

      //Cono
      glPushMatrix();
      glEnable(GL_BLEND);
      //sombra
      glColor4f(0,0,0,0.05);
      glScalef(4,8,4);
      glTranslatef(5.0f,0.5f,0.0f);
      glRotatef(-5,0,1,0);
      glutSolidCone(1,2,20,20);
      glPopMatrix();
      glPushMatrix();
      glColor4f(0.0, 1.0, 0.0,0.95);
      glTranslatef(20.0f, 0.0f, 0.0f);
      glScalef(4,4,4);
      glutSolidCone(1,2,20,20);
      glDisable(GL_BLEND);
      glPopMatrix();

      //Icosahedro
      glPushMatrix();
      glEnable(GL_BLEND);
      //sombra
      glColor4f(0,0,0,0.05);
      glTranslatef(-25.0f,2.5f,0.0f);
      glRotatef(5,0,1,0);
      glScalef(8,10,8);
      glutSolidIcosahedron();
      glPopMatrix();
      glPushMatrix();
      glColor4f(0.0, 0.0, 1.0,0.95);
      glTranslatef(-25.0f, 0.0f, 0.0f);
      glScalef(8,8,8);
      glutSolidIcosahedron();
      glDisable(GL_BLEND);
      glPopMatrix();



}
//*****lo que se ve en pantalla*********
void display(void)
{
      glClearColor(0.0, 0.0, 0.0 ,1.0);   //  Borrar pantalla y Z-buffer
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
      piso();      //dibuja el piso
      glLoadIdentity();   // Resetear transformaciones
      escena(); //se llaman las figuras
      glFlush();
}
//*********Para controlar el Ortho****************
void init(void)
{
      glShadeModel (GL_SMOOTH);
      glOrtho(-100.0,100.0,-100.0,100.0,-100.0,100.0);
    	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//*********redibujar la ventana**********
void reshape(int w, int h)
{
      glViewport(0,0,(GLsizei)w,(GLsizei)h);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(90.0f, (GLfloat)w/(GLfloat)h, 0.0f, 1.0f);
      gluLookAt(0.0,-20.0,30.0,  0.0,0.0,0.0, 0.0,1.0,0.0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
}
//*********Funcion principal****************+
int main(int argc, char** argv)
{
      glutInit(&argc, argv);
      glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
      glutInitWindowSize (800, 600);   //tamaño de la ventana
      glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-800)/2,
                             (glutGet(GLUT_SCREEN_HEIGHT)-600)/2);
      glutCreateWindow ("Parcial #3 by MT14002");   //nombre de la ventana
      init ();
      glutDisplayFunc(display);
      glutReshapeFunc(reshape);
      glutMainLoop();
      return 0;
}
