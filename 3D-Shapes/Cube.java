
package three_dim_shapes;

import javax.media.opengl.GL;

public class Cube {
    
    private float rquad = 0.0f;
    
    public void draw (GL gl) {
    gl.glRotatef(rquad,0.0f,1.0f,0.0f);             // Obrot szescianu w osi Y
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
    rquad-=0.15f;
  }  
}
