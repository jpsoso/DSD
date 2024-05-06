/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package contador;

import icontador.Icontador;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.net.MalformedURLException;

public class Contador extends UnicastRemoteObject implements Icontador {
private int suma;
public Contador() throws RemoteException{
 }
public int sumar() throws RemoteException {
return suma;
 }
public void sumar(int valor) throws RemoteException {
 suma = valor;
 }
public int incrementar() throws RemoteException {
suma++;
return suma;
 }
}

