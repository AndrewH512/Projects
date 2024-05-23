from OpenGL.GL import *
from OpenGL.GLUT import *
import math

# Global variables
polygons = []
current_polygon = []
drawing = False

# Draw Polygon
def drawWiredPoly(vertices):
    glBegin(GL_LINE_LOOP)
    for vertex in vertices:
        glVertex2f(vertex[0], vertex[1])
    glEnd()

def drawFeedback(vertices):
    glColor3f(0, 0, 0)
    glPointSize(5)
    glBegin(GL_POINTS)
    for vertex in vertices:
        glVertex2f(vertex[0], vertex[1])
    glEnd()

def display():
    glClear(GL_COLOR_BUFFER_BIT)
    
    glColor3f(1, 0, 0)
    for polygon in polygons:
        drawWiredPoly(polygon)
    if drawing:
        drawWiredPoly(current_polygon)
    drawFeedback(current_polygon)
    
    glFlush()

def init():
    glClearColor(1,1,1,0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-1,1,-1,1,-1,10)

# User Input
def mouse_click(button, state, x, y):
    global current_polygon, drawing

    if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
        if not drawing:
            current_polygon = []
            drawing = True

        # Convert window coordinates to normalized device coordinates
        normalized_x = (x - 250) / 250.0
        normalized_y = (250 - y) / 250.0

        current_polygon.append((normalized_x, normalized_y))
        glutPostRedisplay()

        if len(current_polygon) > 2 and math.isclose(current_polygon[0][0], normalized_x, abs_tol=0.02) and math.isclose(current_polygon[0][1], normalized_y, abs_tol=0.02):
            # Complete the current polygon and start a new one
            polygons.append(current_polygon[:-1])
            current_polygon = []
            drawing = False

def main():
    glutInit(())
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowPosition(80, 80)
    glutInitWindowSize(500, 500)
    glutCreateWindow("Draw n-sided Polygon")
    init()

    glutDisplayFunc(display)
    glutMouseFunc(mouse_click)

    glutMainLoop()

if __name__ == "__main__":
    main()
