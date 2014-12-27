
package three_dim_shapes;

import javax.media.opengl.GL;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.glu.GLU;


public class OpenGL_handler implements GLEventListener {
    
    private Cube cube = new Cube();
    private Pyramid pyramid = new Pyramid();
    
    public void init(GLAutoDrawable drawable) {

        GL gl = drawable.getGL();

        gl.setSwapInterval(1);

        // ustawienia drawing area i shading mode
        gl.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        gl.glShadeModel(GL.GL_SMOOTH);
    } 

    public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
        GL gl = drawable.getGL();
        GLU glu = new GLU();

        if (height <= 0) {height = 1;} // unikamy dzielenia przez 0
        
        final float h = (float) width / (float) height;
        gl.glViewport(0, 0, width, height);
        gl.glMatrixMode(GL.GL_PROJECTION);
        gl.glLoadIdentity();
        glu.gluPerspective(45.0f, h, 1.0, 20.0);
        gl.glMatrixMode(GL.GL_MODELVIEW);
        gl.glLoadIdentity();
    } 
    
    public void display(GLAutoDrawable drawable) {
        GL gl = drawable.getGL();

        // Czyscimy drawing area
        gl.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);
        gl.glEnable(GL.GL_DEPTH_TEST);
        gl.glDepthFunc(GL.GL_LESS);
        gl.glClearDepth(1.0);
        
        gl.glLoadIdentity();
        gl.glTranslatef(-1.5f, 0.0f, -6.0f);
        pyramid.draw(gl);
        
        gl.glLoadIdentity();
        gl.glTranslatef(1.5f,0.0f,-7.0f); 
        cube.draw(gl);

        gl.glFlush();
    }

    public void displayChanged(GLAutoDrawable drawable, boolean modeChanged, boolean deviceChanged) {
    }
}
