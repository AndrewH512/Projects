from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from random import *
from math import *

class cModel3:
    def __init__(self,newName):
        self.length    = 1
        self.direction = [0,0,0]
        self.offset    = [0,0,0]
        self.rotate    = [0,0,0]
        self.translate = [0,0,0]
        self.name      = newName
        self.color     = [1,1,1]
        self.children  = []
        self.defineBone()

    def __init__(self,newName,newLength,newDirection):
        self.name      = newName
        self.length    = newLength
        self.direction = newDirection
        self.offset    = [0,0,0]
        self.rotate    = [0,0,0]
        self.translate = [0,0,0]
        self.color     = [1,1,1]
        self.children  = []
        self.defineBone()

    def rotation(self,angle,x,y):
        angle = angle * pi / 180
        x1 = x*cos(angle)-y*sin(angle)
        y1 = x*sin(angle)+y*cos(angle)
        return x1,y1

    def compOffset(self):
        x = self.length
        y = z = 0
        x,y = self.rotation(self.direction[2],x,y)
        y,z = self.rotation(self.direction[0],y,z)
        z,x = self.rotation(self.direction[1],z,x)
        return [x,y,z]
        

    def defineBone(self):
        self.vertices  = [[0,0,0],
                          [self.length/4,self.length/5,self.length/5],
                          [self.length,0,0],
                          [self.length/4,-self.length/5,self.length/5],
                          [self.length/4,self.length/5,-self.length/5],
                          [self.length/4,-self.length/5,-self.length/5]]
        self.faces     =  [[0,3,1],
                           [1,3,2],
                           [0,1,4],
                           [4,1,2],
                           [0,4,5],
                           [5,4,2],
                           [0,5,3],
                           [5,2,3]]

    def setColor(self,newColor):
        self.color = newColor

    def setOffset(self,newOffset):
        self.offset = newOffset

    def setRotate(self,newRotate):
        self.rotate = newRotate

    def setLength(self,newSize):
        self.length = newSize

    def addChild(self,newChild):
        offset = self.compOffset()
        newChild.setOffset(offset)
        self.children.append(newChild)

    def drawBone(self):
        for f in range(8):
            glBegin(GL_LINE_LOOP)
            for v in range(3):
                glVertex3fv(self.vertices[self.faces[f][v]])
            glEnd()

    def draw(self):
        glColor(self.color[0],self.color[1],self.color[2])
        glPushMatrix()
        glTranslatef(self.offset[0],self.offset[1],self.offset[2])
        glTranslatef(self.translate[0],self.translate[1],self.translate[2])
        glRotatef(self.rotate[1],0,1,0)
        glRotatef(self.rotate[0],1,0,0)
        glRotatef(self.rotate[2],0,0,1)
        glPushMatrix()
        glRotatef(self.direction[1],0,1,0)
        glRotatef(self.direction[0],1,0,0)
        glRotatef(self.direction[2],0,0,1)
        self.drawBone()
        glPopMatrix()
        for child in self.children:
            child.draw()
        glPopMatrix()
