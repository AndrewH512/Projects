from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import sys
from PIL import Image, ImageDraw

# Function to create a polka dot texture with a red background
def create_polka_dot_texture(size):
    image = Image.new("RGB", (size, size), color="red")  
    draw = ImageDraw.Draw(image)

    # Draw polka dots on the red background
    # White color for dots
    dot_color = (255, 255, 255)  
    dot_radius = 8
    # We can adjust this value for the row offset
    row_offset = 28  

    for row in range(0, size, 30):
        for col in range(0 if row % (30 * 2) == 0 else row_offset, size, 30 * 2):
            draw.ellipse((col - dot_radius, row - dot_radius, col + dot_radius, row + dot_radius), fill=dot_color)

    return image

# Initialize OpenGL
def init():
    glClearColor(1.0, 1.0, 1.0, 1.0)
    glMatrixMode(GL_PROJECTION)
    gluPerspective(45, (800 / 800), 0.1, 50.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

# Function to draw the cube and map texture
def draw_cube():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0)  

    glEnable(GL_TEXTURE_2D)
    glBindTexture(GL_TEXTURE_2D, 1)

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.size[0], texture.size[1], 0, GL_RGB, GL_UNSIGNED_BYTE, texture.tobytes())

    # Draw Cube
    glBegin(GL_QUADS)
    glTexCoord2f(0, 0)
    glVertex3f(-1, -1, -1)
    glTexCoord2f(1, 0)
    glVertex3f(1, -1, -1)
    glTexCoord2f(1, 1)
    glVertex3f(1, 1, -1)
    glTexCoord2f(0, 1)
    glVertex3f(-1, 1, -1)

    glTexCoord2f(0, 0)
    glVertex3f(-1, -1, 1)
    glTexCoord2f(1, 0)
    glVertex3f(1, -1, 1)
    glTexCoord2f(1, 1)
    glVertex3f(1, 1, 1)
    glTexCoord2f(0, 1)
    glVertex3f(-1, 1, 1)

    glTexCoord2f(0, 0)
    glVertex3f(-1, -1, -1)
    glTexCoord2f(1, 0)
    glVertex3f(-1, -1, 1)
    glTexCoord2f(1, 1)
    glVertex3f(-1, 1, 1)
    glTexCoord2f(0, 1)
    glVertex3f(-1, 1, -1)

    glTexCoord2f(0, 0)
    glVertex3f(1, -1, -1)
    glTexCoord2f(1, 0)
    glVertex3f(1, -1, 1)
    glTexCoord2f(1, 1)
    glVertex3f(1, 1, 1)
    glTexCoord2f(0, 1)
    glVertex3f(1, 1, -1)

    glTexCoord2f(0, 0)
    glVertex3f(-1, -1, -1)
    glTexCoord2f(1, 0)
    glVertex3f(1, -1, -1)
    glTexCoord2f(1, 1)
    glVertex3f(1, -1, 1)
    glTexCoord2f(0, 1)
    glVertex3f(-1, -1, 1)

    glTexCoord2f(0, 0)
    glVertex3f(-1, 1, -1)
    glTexCoord2f(1, 0)
    glVertex3f(1, 1, -1)
    glTexCoord2f(1, 1)
    glVertex3f(1, 1, 1)
    glTexCoord2f(0, 1)
    glVertex3f(-1, 1, 1)
    glEnd()

    glDisable(GL_TEXTURE_2D)
    glFlush()  

# Main Loop
if __name__ == "__main__":
    glutInit()
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH)
    glutInitWindowSize(800, 800)
    glutCreateWindow("Project 3")

    glEnable(GL_DEPTH_TEST)
    texture = create_polka_dot_texture(256)

    glutDisplayFunc(draw_cube)
    init()
    glutMainLoop()
