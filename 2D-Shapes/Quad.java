
package two_dim_shapes;

import javax.media.opengl.GL;


public class Quad {
    
    public void draw(GL gl) {
        gl.glBegin(GL.GL_QUADS);
            gl.glVertex3f(-1.0f, 1.0f, 0.0f);  // Top Left
            gl.glVertex3f(1.0f, 1.0f, 0.0f);   // Top Right
            gl.glVertex3f(1.0f, -1.0f, 0.0f);  // Bottom Right
            gl.glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left
        gl.glEnd();
    }
}
