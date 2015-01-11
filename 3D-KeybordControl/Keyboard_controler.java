/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package keyboard_control;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

/**
 *
 * @author Pati
 */
class Keyboard_controler implements KeyListener{
    private boolean [] keys;
    
    public Keyboard_controler (boolean [] keys) {
        
        this.keys = keys;
    }
     public void keyTyped(KeyEvent e){
         System.out.println("key typed");
      }
   
      public void keyPressed(KeyEvent e){
          //System.out.println(e.getKeyCode());
                 
         switch(e.getKeyCode())
         {
            //Kill app
            case KeyEvent.VK_ESCAPE:
               {
                  System.exit(0);
                  break;
               }
            default :
               if(e.getKeyCode()<250) // only interested in first 250 key codes, are there more?
                  keys[e.getKeyCode()]=true;	
               break;
         }
      }
   
      public void keyReleased(KeyEvent e){
         if(e.getKeyCode()<250)  // only interested in first 250 key codes, are there more?
            keys[e.getKeyCode()]=false;
      }
}
