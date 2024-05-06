/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package clientedonaciones;

import interfacesistemadonaciones.interfacesistemadonaciones;
import java.rmi.registry.LocateRegistry;
import java.rmi.*;
import java.rmi.registry.Registry;
import java.util.Scanner;

import java.util.ArrayList;
/**
 *
 * @author jesusp
 */
public class clientedonaciones {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        String host = "";
        Scanner teclado = new Scanner (System.in);
        System.out.println ("Escriba el nombre o IP del servidor: ");
        //ost = teclado.nextLine();
        //host = "localhost";

        // Crea e instala el gestor de seguridad
        if (System.getSecurityManager() == null) {System.setSecurityManager(new SecurityManager());}
        try {
            // Crea el stub para el cliente especificando el nombre del servidor
            Registry mireg = LocateRegistry.getRegistry(host, 1099);
            interfacesistemadonaciones sistema = (interfacesistemadonaciones) mireg.lookup("sistemaDonacion1");
            //sistema.ping();
            if(sistema.registrar("Prueba1", "Prueba1"))
            {
                System.out.println("Se ha registrado el cliente");
            }
            
            if(sistema.registrar("Prueba2", "Prueba2"))
            {
                System.out.println("Se ha registrado el cliente");
            }
            
            if(sistema.registrar("Prueba3", "Prueba3"))
            {
                System.out.println("Se ha registrado el cliente");
            } 
            
            if (sistema.donacion("Prueba1", "Prueba1", 5))
            {
                System.out.println("Donación realizada con éxito");
            }

            
            if (sistema.donacion("Prueba2", "Prueba2", 7))
            {
                System.out.println("Donación realizada con éxito");
            } 
            
            if (sistema.donacion("Prueba3", "Prueba3", 7))
            {
                System.out.println("Donación realizada con éxito");
            }             
            
//            float donado = sistema.subtotalDonado("Prueba1", "Prueba1");
//            
//            if (donado != -1)
//            {
//                System.out.println("El subtotal del sistema es: " + donado);
//            }
//            
//            float donado2 = sistema.subtotalDonado("Prueba2", "Prueba1");
//            
//            if (donado2 != -1)
//            {
//                System.out.println("El subtotal del sistema es: " + donado2);
//            } 

              ArrayList<String> listaDonantes = sistema.listadoDonantes("Prueba2", "Prueba2");
              System.out.println(listaDonantes.toString());
        } 
        catch(NotBoundException | RemoteException e) {
            System.err.println("Exception del sistema: " + e);
        }
        System.exit(0);
    }
    
}
