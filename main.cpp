#if defined(_WIN32) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#if defined(_WIN32) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <GL/glut.h>
#endif
#include <iostream>

using namespace std;
//inisialisasi variable global
const float BOX_SIZE = 7.0f;
float _angle = 0;

GLuint _textureIdDepan, _textureIdBelakang, _textureIdKanan, _textureIdKiri, _textureIdAtas, _textureIdBawah;

// Fungsi inisialisasi rendering OpenGL
void initRendering();
void loadColorTexture(const GLfloat color[], GLuint &textureId);
void drawScene();
void update(int value);
void handleKeyPress(unsigned char key, int x, int y);
void handleResize(int w, int h);

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);


    //GLfloat ambientLight[] = {0.6f, 0.6f, 0.6f, 0.1f};  //Disini Pengaturan Transparan
    GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};  //warnanya menjadi Cerah
   // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight); //nonaktifkan ini jika mau transparan

     // warna untuk masing-masing sisi objek
    GLfloat colorDepan[] = {1.0f, 0.0f, 0.0f};   // Red
    GLfloat colorAtas[] = {0.0f, 1.0f, 0.0f};    // Green
    GLfloat colorBawah[] = {0.0f, 0.0f, 1.0f};   // Blue
    GLfloat colorKiri[] = {1.0f, 1.0f, 0.0f};    // Yellow
    GLfloat colorKanan[] = {1.0f, 0.0f, 1.0f};   // Magenta
    GLfloat colorBelakang[] = {0.0f, 1.0f, 1.0f}; // Cyan
     // membuat tekstur warna untuk masing-masing sisi
    loadColorTexture(colorDepan, _textureIdDepan);
    loadColorTexture(colorAtas, _textureIdAtas);
    loadColorTexture(colorBawah, _textureIdBawah);
    loadColorTexture(colorKiri, _textureIdKiri);
    loadColorTexture(colorKanan, _textureIdKanan);
    loadColorTexture(colorBelakang, _textureIdBelakang);
}

//Fungsi untuk membuat objek agar menjadi transparan
/*
void loadTransparentTexture(const GLfloat color[], GLuint &textureId) {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set the texture image (1x1 pixel) with alpha channel
    unsigned char pixel[] = {static_cast<unsigned char>(color[0] * 255),
                             static_cast<unsigned char>(color[1] * 255),
                             static_cast<unsigned char>(color[2] * 255),
                             128};  // 128 value untuk (transparency)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
}


*/
// Fungsi membuat tekstur warna
void loadColorTexture(const GLfloat color[], GLuint &textureId) {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set texture image (1x1 pixel)
    unsigned char pixel[] = {static_cast<unsigned char>(color[0] * 255),
                             static_cast<unsigned char>(color[1] * 255),
                             static_cast<unsigned char>(color[2] * 255)};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel);
}
// Fungsi menggambar objek 3D
void drawScene() {
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -20.0f);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    //Atur Pencahayaan disini
    GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glRotatef(-_angle, 1.0f, 1.0f, 0.0f);


    //Gambar masing-masing sisi objek dengan tekstur yang sesuai
    // depan
    glBindTexture(GL_TEXTURE_2D, _textureIdDepan);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();

    // Sisi Atas
    glBindTexture(GL_TEXTURE_2D, _textureIdAtas);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    // Sisi bawah
    glBindTexture(GL_TEXTURE_2D, _textureIdBawah);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();

    // Sisi kiri
    glBindTexture(GL_TEXTURE_2D, _textureIdKiri);
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

// Sisi Kanan
glBindTexture(GL_TEXTURE_2D, _textureIdKanan);
glBegin(GL_QUADS);
glNormal3f(1.0, 0.0f, 0.0f);  // Normal sisi kanan
glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
glEnd();

    // Sisi belakang
    glBindTexture(GL_TEXTURE_2D, _textureIdBelakang);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}
// Fungsi update untuk animasi rotasi
void update(int value) {
    _angle += 1.0f;
    if (_angle > 360) {
        _angle -= 360;
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

//Fungsi untuk ESC
/*
void handleKeyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
    }
}

*/
// Fungsi untuk menglock objek gambar

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

//Main Program

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Texture With Color");
    initRendering();
//Pemanggilan Beberapa Fungsi
    glutDisplayFunc(drawScene);
        //Fungsi untuk ESC
 //glutKeyboardFunc(handleKeyPress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);
    glutMainLoop();

    return 0;
}
