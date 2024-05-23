from OpenGL import *
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from math import *
from cModel3 import *

def draw_cube():
    glBegin(GL_QUADS)
    # Front face
    glVertex3f(-5, -5, 5)
    glVertex3f(5, -5, 5)
    glVertex3f(5, 5, 5)
    glVertex3f(-5, 5, 5)
    # Back face
    glVertex3f(-5, -5, -5)
    glVertex3f(-5, 5, -5)
    glVertex3f(5, 5, -5)
    glVertex3f(5, -5, -5)
    # Top face
    glVertex3f(-5, 5, -5)
    glVertex3f(-5, 5, 5)
    glVertex3f(5, 5, 5)
    glVertex3f(5, 5, -5)
    # Bottom face
    glVertex3f(-5, -5, -5)
    glVertex3f(5, -5, -5)
    glVertex3f(5, -5, 5)
    glVertex3f(-5, -5, 5)
    # Left face
    glVertex3f(-5, -5, -5)
    glVertex3f(-5, -5, 5)
    glVertex3f(-5, 5, 5)
    glVertex3f(-5, 5, -5)
    # Right face
    glVertex3f(5, -5, -5)
    glVertex3f(5, 5, -5)
    glVertex3f(5, 5, 5)
    glVertex3f(5, -5, 5)
    glEnd()

def init():
    global pelvis
    glClearColor(0,0,0,0)
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity()
    gluPerspective(60.0, 1.0, 1.0, 100.0)
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity()
    gluLookAt(40.0, 20.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    
    pelvis = cModel3("Pelvis",0,[10,0,0])

    spine3 = cModel3("Spine 3",10,[20,0,90])
    pelvis.addChild(spine3)

    # Left arm
    lShoulder = cModel3("Left Shoulder",5,[0,0,0])
    spine3.addChild(lShoulder)
    
    upperLArm = cModel3("Upper Left Arm",10,[0,-120,0])
    lShoulder.addChild(upperLArm)

    lowerLArm = cModel3("Lower Left Arm",10,[0,-200,120])
    upperLArm.addChild(lowerLArm)
    
    lHand = cModel3("Left Hand",5,[0,90,0])
    lowerLArm.addChild(lHand)
    
    # Right arm
    rShoulder = cModel3("Right Shoulder",5,[0,-90,-60])
    spine3.addChild(rShoulder)
    
    upperRArm = cModel3("Upper Right Arm",5,[0,-90,-60])
    rShoulder.addChild(upperRArm)
    
    lowerRArm = cModel3("Lower Right Arm",10,[0,0,0])
    upperRArm.addChild(lowerRArm)
    
    rHand = cModel3("Right Hand",5,[0,0,180])
    lowerRArm.addChild(rHand)

    # Neck
    neck = cModel3("Neck",5,[20,0,90])
    spine3.addChild(neck)

    # Head
    head = cModel3("Head",10,[20,00,90])
    neck.addChild(head)

    # Hip
    hip = cModel3("Hip", 5, [0,0,-90])
    pelvis.addChild(hip)

    # Left leg
    lHip = cModel3("Left Hip", 5, [0,-5,-150])
    hip.addChild(lHip)

    upperLLeg = cModel3("Upper Left Leg", 10, [0,0,-150])
    lHip.addChild(upperLLeg)

    lowerLLeg = cModel3("Lower Left Leg", 10, [0,0,-150])
    upperLLeg.addChild(lowerLLeg)

    lFoot = cModel3("Left Foot", 5, [0,0,-60])
    lowerLLeg.addChild(lFoot)

    #Right leg
    rHip = cModel3("Right Hip", 5, [0,0,200])
    hip.addChild(rHip)

    upperRLeg = cModel3("Upper Right Leg", 10, [0,0,200])
    rHip.addChild(upperRLeg)

    lowerRLeg = cModel3("Lower Right Leg", 10, [0,270,270])
    upperRLeg.addChild(lowerRLeg)

    rFoot = cModel3("Right Foot", 5, [0,0,270])
    lowerRLeg.addChild(rFoot)

   

def display():
    global model1
    glClear(GL_COLOR_BUFFER_BIT)
    glColor3f(1,0,0)
    glBegin(GL_LINES)
    glVertex3f(-50,0,0)
    glVertex3f(50,0,0)
    glVertex3f(0,-50,0)
    glVertex3f(0,50,0)
    glEnd()

     # Draw cube
    glColor3f(0.5, 0, 0)
    glPushMatrix()
    glTranslatef(10, -5, 8)  
    draw_cube()
    glPopMatrix()
    
    glColor3f(0,0,0)
    glPushMatrix()
    pelvis.draw()
    glPopMatrix()
    glFlush()
    glutSwapBuffers()

def main():
    glutInit(())
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowPosition(80, 80)
    glutInitWindowSize(500, 500)
    glutCreateWindow("Articulated Model Example")
    init()
    glutDisplayFunc(display)
    glutIdleFunc(display)
    glutMainLoop()

main()
