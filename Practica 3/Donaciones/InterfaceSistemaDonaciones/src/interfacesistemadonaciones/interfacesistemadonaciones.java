/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package interfacesistemadonaciones;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;
/**
 *
 * @author jesusp
 */
public interface interfacesistemadonaciones extends Remote {
    
    public boolean registrar(String nombreUsuario, String contrasena) throws RemoteException;
    
    public void registra(String nombreUsuario, String contrasena)throws RemoteException;
    
    public boolean donacion(String nombreUsuario, String contrasena, float cantidad) throws RemoteException;
    
    public boolean dona(String nombreUsuario, String contrasena, float cantidad) throws RemoteException;
    
    public float subtotalDonado(String nombreUsuario, String contrasena) throws RemoteException;
    
    public float subtotal(String nombreUsuario, String contrasena) throws RemoteException;
    
    public ArrayList<String> listadoDonantes(String nombreUsuario, String contrasena) throws RemoteException;
    
    public ArrayList<String> listado(String nombreUsuario, String contrasena) throws RemoteException; 
    
    public boolean existeCliente(String nombreUsuario) throws RemoteException;
    
    public boolean existeClienteSistema(String nombreUsuario) throws RemoteException;
    
    public int getCargaUsuarios() throws RemoteException;
    
    public String getMenosCarga() throws RemoteException;
    
    public String getNombre() throws RemoteException;
    
    // Añadir operacion de inicio de sesion 
    
    public void ping() throws RemoteException;
    
    
}
