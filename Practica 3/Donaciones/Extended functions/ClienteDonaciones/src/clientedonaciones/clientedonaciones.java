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
import java.util.List;
/**
 *
 * @author jesusp
 */
public class clientedonaciones {

    /**
     * @param args the command line arguments
     */
    public static void printLogInSignInMenu(String servidor)
    {
        System.out.println("================ BENEFIC.ORG ================");
        System.out.println(" Bienvenido. Por favor, identifíquese");
        System.out.println(" [1] Registrarse");
        System.out.println(" [2] Iniciar sesión");
        System.out.println(" [3] Salir");
        System.out.println("=============================================");
        System.out.println(" \t\tconnected: " + servidor);
    }
    
    public static void printOperationMenu(String username, String servidor)
    {
        System.out.println("================ BENEFIC.ORG ================");
        System.out.println(" sesión iniciada: " + username);
        System.out.println(" Elija una operación:");
        System.out.println(" [1] Hacer donación");
        System.out.println(" [2] Consultar total del servidor");
        System.out.println(" [3] Listado de donantes");
        System.out.println(" [4] Top de donaciones");
        System.out.println(" [5] Media de las donaciones");
        System.out.println(" [6] Cerrar sesión");
        System.out.println("=============================================");
        System.out.println(" \t\tconnected: " + servidor);
    }
    
    public static void main(String[] args) {
        
        if (System.getSecurityManager() == null) {System.setSecurityManager(new SecurityManager());}
        try {
            
            Scanner teclado = new Scanner (System.in);
            // Hacemos la conexión con el objeto remoto
            Registry mireg = LocateRegistry.getRegistry("", 1099);
            int connection = 0;
            String servidor = "";
            boolean seleccionado = false;
            do
            {
                System.out.println("Elige a que servidor conectarse: ");
                System.out.println("[1] Réplica 1 ");
                System.out.println("[2] Réplica 2 ");
                connection = teclado.nextInt();
                
                switch(connection)
                {
                    case 1:
                        servidor = "sistemaDonacion1";
                        seleccionado = true;
                        break;
                    case 2:
                        servidor = "sistemaDonacion2";
                        seleccionado = true;
                        break;                     
                }
            } while (!seleccionado);
            
            interfacesistemadonaciones sistema = (interfacesistemadonaciones) mireg.lookup("sistemaDonacion1");
            
            // Empezamos las operaciones.
            int option = 0, operation = 0;
            String username = "", password = "";
            boolean sesionIniciada = false;
        
            do {
                printLogInSignInMenu(servidor);
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
                            sesionIniciada = true;
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
                    printOperationMenu(username, servidor);
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
                                System.out.println(" El subtotal del servidor registrado es de: " + subTotal + "€");
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
                                System.out.println(" Vaya, parece que no es posible que consultes la lista de donantes.\n Realiza una donación para poder consultarla");
                            }
                            break;
                            
                        case 4:
                            ArrayList<String> topDonaciones = sistema.listadoDonantes(username, password);
                            if (!topDonaciones.isEmpty())
                            {
                                int top = 1;
                                System.out.println("==============  Top donaciones ==============");
                                System.out.println(" Introduzca cuantas donaciones quiere ver (máximo " + topDonaciones.size() + "): ");
                                top = teclado.nextInt();
                                while (top <= 0 || top > topDonaciones.size())
                                {
                                    System.out.println(" Introduzca un numero válida: ");
                                    top = teclado.nextInt();
                                }
                                List<String> topN = topDonaciones.subList(0, top);
                                System.out.println(" El top " + top + " donaciones del servidor es: ");
                                int i = 1;
                                for(String element : topN)
                                {
                                    System.out.println(" "+ i + "º " + element);
                                    ++i;
                                }   
                            }
                            else
                            {
                                System.out.println(" Vaya, parece que no es posible que consultes el top de donaciones.\n Realiza una donación para poder consultarlo");
                            }                            
                            break;
                        case 5:
                            float media = sistema.mediaDonaciones(username, password);
                            if (media != -1)
                            {
                                System.out.println(" La media de donaciones es de: " + media + "€");  
                            }
                            else
                            {
                                System.out.println(" Vaya, parece que no es posible que consultes la media de donaciones.\n Realiza una donación para poder consultarlo");
                            }                            
                            break;                            
                        case 6:
                            sesionIniciada = false;
                            break;
                    }
                }
                
            } while (option != 3);
            
        
             
        }  
            
        catch(NotBoundException | RemoteException e) {
            System.err.println("Exception del sistema: " + e);
        }
        System.exit(0);
    }
    
}
