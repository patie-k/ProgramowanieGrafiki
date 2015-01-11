/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package keyboard_control;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

/**
 *
 * @author Pati
 */

public class MouseController implements MouseMotionListener{

    private int [] mouseCoorditates;
    
    public MouseController (int [] mouseCoorditates) {
        this.mouseCoorditates = mouseCoorditates;
    }
    
    public void mouseDragged(MouseEvent me) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public void mouseMoved(MouseEvent me) {
        mouseCoorditates[0] = me.getX();
        mouseCoorditates[1] = me.getY();
    }

   
    
}
