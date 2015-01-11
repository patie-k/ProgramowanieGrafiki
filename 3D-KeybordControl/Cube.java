
package keyboard_control;

import javax.media.opengl.GL;


public class Cube {
    
    public Cube (boolean [] keys) {
        this.keys = keys;
    }
    
    private float rquad_LR = 0.0f;
    private float rquad_UD = 0.0f;
    private boolean [] keys; 
    
    public void draw (GL gl) {
    gl.glRotatef(rquad_LR,0.0f,1.0f,0.0f);             // Obrot szescianu w osi Y
    //gl.glLoadIdentity();
    gl.glRotatef(rquad_UD,1.0f,0.0f,0.0f);             // Obrot szescianu w osi Z
    gl.glBegin(GL.GL_QUADS); 
        gl.glColor3f(0.0f,1.0f,0.0f);
        gl.glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Top)
        gl.glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Top)
        gl.glVertex3f(-1.0f, 1.0f, 1.0f);          // Bottom Left Of The Quad (Top)
        gl.glVertex3f( 1.0f, 1.0f, 1.0f);          // Bottom Right Of The Quad (Top)
        gl.glColor3f(1.0f,0.5f,0.0f);
        gl.glVertex3f( 1.0f,-1.0f, 1.0f);          // Top Right Of The Quad (Bottom)
        gl.glVertex3f(-1.0f,-1.0f, 1.0f);          // Top Left Of The Quad (Bottom)
        gl.glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Bottom)
        gl.glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Bottom)
        gl.glColor3f(1.0f,0.0f,0.0f);
        gl.glVertex3f( 1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Front)
        gl.glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Front)
        gl.glVertex3f(-1.0f,-1.0f, 1.0f);          // Bottom Left Of The Quad (Front)
        gl.glVertex3f( 1.0f,-1.0f, 1.0f);          // Bottom Right Of The Quad (Front)
        gl.glColor3f(1.0f,1.0f,0.0f);
        gl.glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Back)
        gl.glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Back)
        gl.glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Back)
        gl.glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Back
        gl.glColor3f(0.0f,0.0f,1.0f);
        gl.glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Left)
        gl.glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Left)
        gl.glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Left)
        gl.glVertex3f(-1.0f,-1.0f, 1.0f);          // Bottom Right Of The Quad (Left)
        gl.glColor3f(1.0f,0.0f,1.0f);
        gl.glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Right)
        gl.glVertex3f( 1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Right)
        gl.glVertex3f( 1.0f,-1.0f, 1.0f);          // Bottom Left Of The Quad (Right)
        gl.glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Right)
    gl.glEnd();
    
    if (keys[37]) { //Left
        rquad_LR-=0.3f;
    }
    
    if(keys[39]) { //Right
        rquad_LR+=0.3f;
    }
    
    if (keys[40]) { //Down
        rquad_UD+=0.3f;
    }
    
    if(keys[38]) { //Up
        rquad_UD-=0.3f;
    }
    //rquad-=0.15f;
  }  
}
