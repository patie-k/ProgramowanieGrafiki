
package two_dim_shapes;

import javax.media.opengl.GL;


public class Triangle {
    
    public void draw(GL gl) {
        gl.glBegin(GL.GL_TRIANGLES);
            gl.glVertex3f(0.0f, 1.0f, 0.0f);   // Top
            gl.glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left
            gl.glVertex3f(1.0f, -1.0f, 0.0f);  // Bottom Right
        gl.glEnd();
    }
}
