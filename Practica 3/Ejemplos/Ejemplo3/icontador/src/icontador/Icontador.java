/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package icontador;
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Icontador extends Remote {
int sumar() throws RemoteException;
void sumar (int valor) throws RemoteException;
public int incrementar() throws RemoteException;
}
