/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package servidordonaciones;

import sistemadonaciones.sistemadonaciones;
import java.net.MalformedURLException;
import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.*;

/**
 *
 * @author jesusp
 */
public class servidordonaciones {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        if (System.getSecurityManager() == null) {System.setSecurityManager(new SecurityManager());}
        try {
        // Crea una instancia de sistema de donaciones
           Registry reg = LocateRegistry.createRegistry(1099);
           sistemadonaciones sistemaDonacion = new sistemadonaciones("sistemaDonacion1", "sistemaDonacion2");
           Naming.rebind("sistemaDonacion1", sistemaDonacion);
           System.out.println("Servidor con sistema de Donaciones lanzado");
           sistemadonaciones sistemaDonacion2 = new sistemadonaciones("sistemaDonacion2", "sistemaDonacion1");
           Naming.rebind("sistemaDonacion2", sistemaDonacion2);
           System.out.println("Servidor con sistema de Donaciones 2 lanzado");        
        } 
        catch (RemoteException | MalformedURLException e) {
           System.out.println("Exception: " + e.getMessage());
        }

    }
    
}
