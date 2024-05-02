// Fichero: Ejemplo_I.java
// Define la Interfaz remota
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Ejemplo_I extends Remote {
    synchronized void escribir_mensaje (String mensaje) throws RemoteException;
}

