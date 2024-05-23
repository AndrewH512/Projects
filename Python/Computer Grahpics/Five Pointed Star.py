# Andrew Hennessy
# Computer Graphics
# January 30th 2024
# Project 1 - 5 Point Star in Opengl and GLUT
from OpenGL import *
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from math import *

def drawFivePointStar(size):
    glBegin(GL_LINE_LOOP)
    # Set Color to Blue
    glColor3f(0.0, 0.0, 1.9)  

    # Start at the top point of the star
    angle = pi / 2
    
    # Angle between consecutive points
    delta = 2 * pi / 5  

    for _ in range(5):
        x_outer = size * cos(angle)
        y_outer = size * sin(angle)
        # Add the outer points
        glVertex2f(x_outer, y_outer)

        # Use a smaller radius for inner points
        x_inner = size * cos(angle + delta / 2) / 2  
        y_inner = size * sin(angle + delta / 2) / 2
        # Add the inner points
        glVertex2f(x_inner, y_inner)

        angle += delta

    glEnd()



def drawCircle(R,cX,cY):
    # 10 sides as shown in the example
    steps = 10
    # Offset 
    angle_offset = -pi/2
    glBegin(GL_LINE_LOOP)
    # Set Color to Green
    glColor3f(0,1,0)
    for i in range(steps):
        angle = angle_offset + 2 * pi * i / steps
        x = cX + R * cos(angle)
        y = cY + R * sin(angle)
        glVertex2f(x,y)
    glEnd()

def init():
    glClearColor(1,1,1,0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-1,1,-1,1,-1,10)

def display():
    glClear(GL_COLOR_BUFFER_BIT)
    # Add draw instructions here
    # Size 1 for each the circle and star
    drawCircle(1,0,0)
    # The Star will fit inside the circle 
    drawFivePointStar(1)
    glFlush()

def main():
    glutInit(())
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowPosition(80, 80)
    glutInitWindowSize(500, 500)
    glutCreateWindow("")
    init()
    glutDisplayFunc(display)
    glutMainLoop()
    return

main()
