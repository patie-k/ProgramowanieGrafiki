
package keyboard_control;

import javax.media.opengl.GL;


public class Pyramid {
    
    private float rtri = 0.0f;
    
    public void draw (GL gl) {
        gl.glRotatef(rtri,0.0f,1.0f,0.0f);             // Obrot piramidy w osi Y
        gl.glBegin(GL.GL_TRIANGLES);
            gl.glColor3f(1.0f,0.0f,0.0f);
            gl.glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Front)
            gl.glColor3f(0.0f,1.0f,0.0f);
            gl.glVertex3f(-1.0f,-1.0f, 1.0f);          // Left Of Triangle (Front)
            gl.glColor3f(0.0f,0.0f,1.0f);
            gl.glVertex3f( 1.0f,-1.0f, 1.0f);          // Right Of Triangle (Front)
            gl.glColor3f(1.0f,0.0f,0.0f);
            gl.glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Right)
            gl.glColor3f(0.0f,0.0f,1.0f);
            gl.glVertex3f( 1.0f,-1.0f, 1.0f);          // Left Of Triangle (Right)
            gl.glColor3f(0.0f,1.0f,0.0f);
            gl.glVertex3f( 1.0f,-1.0f, -1.0f);         // Right Of Triangle (Right)
            gl.glColor3f(1.0f,0.0f,0.0f);
            gl.glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Back)
            gl.glColor3f(0.0f,1.0f,0.0f);
            gl.glVertex3f( 1.0f,-1.0f, -1.0f);         // Left Of Triangle (Back)
            gl.glColor3f(0.0f,0.0f,1.0f);
            gl.glVertex3f(-1.0f,-1.0f, -1.0f);         // Right Of Triangle (Back
            gl.glColor3f(1.0f,0.0f,0.0f);
            gl.glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Left)
            gl.glColor3f(0.0f,0.0f,1.0f);
            gl.glVertex3f(-1.0f,-1.0f,-1.0f);          // Left Of Triangle (Left)
            gl.glColor3f(0.0f,1.0f,0.0f);
            gl.glVertex3f(-1.0f,-1.0f, 1.0f);          // Right Of Triangle (Left)
        gl.glEnd();
        rtri+=0.2f;
  } 
}
