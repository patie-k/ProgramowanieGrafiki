package keyboard_control;

import com.sun.opengl.util.Animator;
import java.awt.Frame;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.media.opengl.GLCanvas;

public class Keyboard_Control {
    
    public static boolean[] keys=new boolean[256];
    private static int [] mouseCoordinates = {0, 0};
        
    public static void main(String[] args) {
        Frame frame = new Frame("Simple JOGL Application");
        frame.setFocusable(true);
        frame.requestFocusInWindow();
        Keyboard_controler test = new Keyboard_controler(keys);
        MouseController mouseController = new MouseController(mouseCoordinates);
       
        frame.pack();
        frame.addKeyListener(test);
        GLCanvas canvas = new GLCanvas();
        
        canvas.addGLEventListener(new OpenGL_handler(keys, mouseCoordinates));
        canvas.addKeyListener(test);
        canvas.addMouseMotionListener(mouseController);
        frame.add(canvas);
        
        frame.setSize(640, 480);
        final Animator animator = new Animator(canvas);
        frame.addWindowListener(new WindowAdapter() {

            @Override
            public void windowClosing(WindowEvent e) {
                //uruchamianie animator.stop w nowym watku
                new Thread(new Runnable() {

                    public void run() {
                        animator.stop();
                        System.exit(0);
                    }
                }).start();
            }
        });
        // wysrodkowanie ramki
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        animator.start();
    }

}

