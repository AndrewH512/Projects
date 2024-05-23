from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys
from PIL import Image as Image

# Set Data Pyramid
verts = [[0.5, 0.5, 0.5], [-0.5, 0.5, 0.5], [-0.5, 0.5, -0.5], [0.5, 0.5, -0.5], [0, -0.5, 0]]
polys = [[3, 2, 1, 0], [0, 1, 4], [1, 2, 4], [2, 3, 4], [3, 0, 4]]
uvs = [[0, 0], [0, 1], [1, 1], [1, 0]]


def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowSize(500, 500)
    glutInitWindowPosition(100, 100)
    glutCreateWindow("Project 4")
    glClearColor(0., 0., 0., 1.)
    glShadeModel(GL_SMOOTH)
    glEnable(GL_CULL_FACE)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_LIGHTING)
    lightZeroPosition = [10., 4., 10., 1.]
    lightZeroColor = [1.0, 1.0, 1.0, 1.0]
    glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor)
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1)
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05)
    glEnable(GL_LIGHT0)
    glutDisplayFunc(display_scene)
    glMatrixMode(GL_PROJECTION)
    gluPerspective(60, 1, 1, 40)
    glMatrixMode(GL_MODELVIEW)
    gluLookAt(0, 0, 10,
              0, 0, 0,
              0, 1, 0)
    glutMainLoop()


def crossProduct(poly):
    P0 = verts[poly[0]]
    P1 = verts[poly[1]]
    P2 = verts[poly[2]]
    V0 = [P1[0] - P0[0], P1[1] - P0[1], P1[2] - P0[2]]
    V1 = [P2[0] - P1[0], P2[1] - P1[1], P2[2] - P1[2]]
    cp = [V0[1] * V1[2] - V0[2] * V1[1],
          V0[2] * V1[0] - V0[0] * V1[2],
          V0[0] * V1[1] - V0[1] * V1[0]]
    return cp


def drawPyramid(size):
    # Draw pyramid
    glEnable(GL_RESCALE_NORMAL)
    glPushMatrix()
    glScalef(size, size, size)
    # Begin drawing triangles
    glBegin(GL_TRIANGLES)
    for f in range(5):
        normal = crossProduct(polys[f])
        glNormal3fv(normal)
        for v in range(3):
            # Set texture coordinate for the vertex
            glTexCoord2fv(uvs[v])
            glVertex3fv(verts[polys[f][v]])
    glEnd()
    glPopMatrix()


def display_scene():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    tex = read_texture("brick.jpg")
    glEnable(GL_TEXTURE_2D)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, tex)
    glPushMatrix()
    glRotatef(90, 1, 0, 0)
    glRotatef(30, 0, 1, 0)
    drawPyramid(5)
    glFlush()
    glDisable(GL_TEXTURE_2D)
    glutSwapBuffers()


def read_texture(filename):
    img = Image.open(filename)
    img_data = list(img.getdata())
    textID = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, textID)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
    glGenTextures(1, 0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.size[0], img.size[1], 0, GL_RGB,
                 GL_UNSIGNED_BYTE, img_data)
    return textID


main()

