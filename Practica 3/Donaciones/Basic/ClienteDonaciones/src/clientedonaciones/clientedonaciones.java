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
    public static void printLogInSignInMenu()
    {
        System.out.println("================ BENEFIC.ORG ================");
        System.out.println(" Bienvenido. Por favor, identifíquese");
        System.out.println(" [1] Registrarse");
        System.out.println(" [2] Iniciar sesión");
        System.out.println(" [3] Salir");
        System.out.println("=============================================");
    }
    
    public static void printOperationMenu(String username)
    {
        System.out.println("================ BENEFIC.ORG ================");
        System.out.println(" sesión iniciada: " + username);
        System.out.println(" Elija una operación:");
        System.out.println(" [1] Hacer donación");
        System.out.println(" [2] Consultar total del servidor");
        System.out.println(" [3] Listado de donantes");
        System.out.println(" [4] Top 5 donaciones");
        System.out.println(" [5] Cerrar sesión");
        System.out.println("=============================================");
    }
    
    public static void main(String[] args) {
        
        if (System.getSecurityManager() == null) {System.setSecurityManager(new SecurityManager());}
        try {
            
            // Hacemos la conexión con el objeto remoto
            Registry mireg = LocateRegistry.getRegistry("", 1099);
            interfacesistemadonaciones sistema = (interfacesistemadonaciones) mireg.lookup("sistemaDonacion1");
            
            // Empezamos las operaciones.
            int option = 0, operation = 0;
            String username = "", password = "";
            boolean sesionIniciada = true;
            Scanner teclado = new Scanner (System.in);
        
            do {
                printLogInSignInMenu();
                option = teclado.nextInt();
                switch (option)
                {
                    case 1:
                        System.out.println("==============  Registro de cliente ==============");
                        System.out.println(" Introduce nombre de usuario: ");
                        username = teclado.next();
                        System.out.println(" Introduce la contraseña: ");
                        password = teclado.next();

                        if (sistema.registrar(username, password))
                        {
                            System.out.println(" Registro realizado con éxito al usuario " + username);
                        }
                        else
                        {
                            System.out.println(" No se ha podido llevar a cabo el registro del usuario " + username);
                        }
                        break;
                    
                    case 2:
                        System.out.println("==============  Inicio sesión de cliente ==============");
                        System.out.println(" Introduce nombre de usuario: ");
                        username = teclado.next();
                        System.out.println(" Introduce la contraseña: ");
                        password = teclado.next();

                        if (sistema.iniciaSesion(username, password))
                        {
                            System.out.println(" Credenciales correctas. Bienvenido de vuelta " + username);
                            sesionIniciada = true;
                        }
                        else
                        {
                            System.out.println(" Credenciales incorrectas, por favor revíselas");
                        }
                        break;
                }
                
                while (sesionIniciada)
                {
                    printOperationMenu(username);
                    operation = teclado.nextInt();
                    switch (operation)
                    {
                        case 1:
                            float cantidad = 0;
                            System.out.println("==============  Hacer donación ==============");
                            System.out.println(" Introduzca la cantidad a donar: ");
                            cantidad = teclado.nextFloat();
                            while (cantidad <= 0)
                            {
                                System.out.println(" Introduzca una cantidad válida: ");
                                cantidad = teclado.nextFloat();
                            }
                            if (sistema.donacion(username, password, cantidad))
                            {
                                System.out.println(" Donación realizada con éxito");
                            }
                            else
                            {
                                System.out.println(" No ha sido posible realizar la donación, por favor inténtelo más tarde");
                            }
                            break;
                        case 2:
                            float subTotal = sistema.subtotalDonado(username, password);
                            if (subTotal > -1)
                            {
                                System.out.println(" El subtotal de este servidor es de: " + subTotal + "€");
                            }
                            else
                            {
                                System.out.println(" Vaya, parece que no es posible que consultes el subtotal.\n Realiza una donación para poder consultarlo");
                            }
                            break;
                        case 3:
                            ArrayList<String> donantes = sistema.listadoDonantes(username, password);
                            if (!donantes.isEmpty())
                            {
                                System.out.println(" La lista de donantes del servidor: " + donantes);
                            }
                            else
                            {
                                System.out.println(" Vaya, parece que no es posible que consultes el la lista de donantes.\n Realiza una donación para poder consultarla");
                            }
                            break;
                            
                        case 4:
                            break;
                            
                        case 5:
                            sesionIniciada = false;
                            break;
                    }
                }
                
            } while (option < 3 && option > 0);
            
        
             
        }  
            
        catch(NotBoundException | RemoteException e) {
            System.err.println("Exception del sistema: " + e);
        }
        System.exit(0);
    }
    
}
