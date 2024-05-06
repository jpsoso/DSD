/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package servidor;

import contador.Contador;
import java.net.MalformedURLException;
import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.*;

/**
 *
 * @author jesusp
 */
public class servidor {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        if (System.getSecurityManager() == null) {System.setSecurityManager(new SecurityManager());}
        try {
        // Crea una instancia de contador
           Registry reg = LocateRegistry.createRegistry(1099);
           Contador micontador = new Contador();
           Naming.rebind("mmicontador", micontador);
           System.out.println("Servidor RemoteException | MalformedURLExceptiondor preparado");
        } 
        catch (RemoteException | MalformedURLException e) {
           System.out.println("Exception: " + e.getMessage());
        }

    }
    
}
