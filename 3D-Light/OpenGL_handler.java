
package three_dim_light;

import com.sun.opengl.util.texture.Texture;
import com.sun.opengl.util.texture.TextureIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.media.opengl.GL;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.glu.GLU;


public class OpenGL_handler implements GLEventListener {
    
    private Cube cube = new Cube();
    Texture texture;
    int textureId = 0;
    
    
    public void init(GLAutoDrawable drawable) {

        GL gl = drawable.getGL();

        gl.setSwapInterval(1);
        

        // ustawienia drawing area i shading mode
        gl.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        gl.glShadeModel(GL.GL_SMOOTH);
        
        gl.glEnable(GL.GL_DEPTH_TEST);
        gl.glDepthFunc(GL.GL_LEQUAL);        
        gl.glHint(GL.GL_PERSPECTIVE_CORRECTION_HINT, GL.GL_NICEST);

        
        
        try {
            loadGlTextures(getClass().getResource("texture.png").getPath());
        } catch (IOException ex) {
            Logger.getLogger(OpenGL_handler.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        // Czyscimy drawing area
        gl.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);
        gl.glEnable(GL.GL_DEPTH_TEST);
        gl.glDepthFunc(GL.GL_LESS);
        gl.glClearDepth(1.0);
        gl.glEnable(GL.GL_LIGHT1);
        gl.glEnable(GL.GL_LIGHTING);
        
        gl.glMatrixMode(GL.GL_MODELVIEW);
        gl.glEnable(GL.GL_PROJECTION);
        
        //gl.glLoadIdentity();
        
        gl.glLoadIdentity();
        
        float SHINE_ALL_DIRECTIONS = 1;
        
        float [] lightAmbient = {1.0f, 0.0f, 0.0f, 1.0f};
        float[] lightDiffuse = {0.8f, 0.8f, 0.8f, 1f};
        float[] lightPosition = {-30.0f, 0.0f, 0.0f, SHINE_ALL_DIRECTIONS};
        
        gl.glLightfv(GL.GL_LIGHT1, GL.GL_POSITION, lightPosition, 0);
        gl.glLightfv(GL.GL_LIGHT1, GL.GL_AMBIENT, lightAmbient, 0);
        gl.glLightfv(GL.GL_LIGHT1, GL.GL_SPECULAR, lightDiffuse, 0);
        
        float[] rgba = {0.3f, 0.5f, 1f};
        gl.glMaterialfv(GL.GL_FRONT, GL.GL_AMBIENT, rgba, 0);
        gl.glMaterialfv(GL.GL_FRONT, GL.GL_SPECULAR, rgba, 0);
        gl.glMaterialf(GL.GL_FRONT, GL.GL_SHININESS, 0.5f);
        
        gl.glLoadIdentity();
    }

    public boolean loadGlTextures(String fileName) throws IOException {
        BufferedImage image = ImageIO.read(new File(fileName));
        texture = TextureIO.newTexture(image, false);
        texture.setTexParameteri(GL.GL_TEXTURE_MIN_FILTER, GL.GL_LINEAR);
        texture.setTexParameteri(GL.GL_TEXTURE_MAG_FILTER, GL.GL_LINEAR);
        texture.enable();
        texture.bind();
        return false;
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
        //gl.glTranslatef(1.5f,0.0f,-7.0f); 
        cube.draw(gl, texture);

        gl.glFlush();
    }

    public void displayChanged(GLAutoDrawable drawable, boolean modeChanged, boolean deviceChanged) {
    }
}
