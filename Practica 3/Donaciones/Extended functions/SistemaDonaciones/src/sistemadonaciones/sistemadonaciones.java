/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package sistemadonaciones;

import interfacesistemadonaciones.interfacesistemadonaciones;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.net.MalformedURLException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import java.util.ArrayList;
import java.util.Map; 
import java.util.HashMap;

/**
 *
 * @author jesusp
 */
public class sistemadonaciones extends UnicastRemoteObject implements interfacesistemadonaciones
{
    String nombre, replicaNombre;
    interfacesistemadonaciones replica;
    
    HashMap<String, Cliente> clientes;
    HashMap<String, Float> historialDonaciones;
    float subtotal;
    
    public sistemadonaciones(String nombre, String replicaNombre) throws RemoteException
    {
        this.nombre = nombre;
        this.clientes = new HashMap<>();
        this.historialDonaciones = new HashMap<>();
        this.replicaNombre = replicaNombre;
        this.replica = null;
        this.subtotal = 0;
    }
    
    @Override
    public boolean registrar(String nombreUsuario, String contrasena) throws RemoteException 
    {
        if(!existeClienteSistema(nombreUsuario))
        {
            if (this.getMenosCarga().equals(nombre))
            {
                this.registra(nombreUsuario, contrasena);
            }
            else
            {
                if (replica != null)
                {
                    replica.registra(nombreUsuario, contrasena);
                }
            }
            return true;
        }
        return false;
    }
    
    @Override
    public void registra(String nombreUsuario, String contrasena) throws RemoteException
    {
        Cliente nuevoCliente = new Cliente(nombreUsuario, contrasena);
        clientes.put(nombreUsuario, nuevoCliente);
        System.out.println("[" + this.nombre + "]: Nuevo cliente registrado: " + nombreUsuario + ". Usuarios en el sistema: " + clientes.size());
    }
    
    @Override
    public boolean donacion(String nombreUsuario, String contrasena, float cantidad) throws RemoteException
    {
        if (this.existeCliente(nombreUsuario))
        {
            return this.dona(nombreUsuario, contrasena, cantidad);
        }
        else 
        {
            if (replica != null)
            {
                return replica.dona(nombreUsuario, contrasena, cantidad);
            }
        }
        return false;
    }
    
    @Override 
    public boolean dona(String nombreUsuario, String contrasena, float cantidad) throws RemoteException
    {
        if (this.existeCliente(nombreUsuario) && cantidad > 0)
        {
            Cliente cliente = this.clientes.get(nombreUsuario);
            if (cliente.compruebaContrasena(contrasena))
            {
                cliente.setTotalDonado(cantidad + cliente.getTotalDonado());
                cliente.setDonacionesHechas(cliente.getDonacionesHechas() + 1);
                this.clientes.replace(nombreUsuario, cliente);
                System.out.println("[" + this.nombre + "]: Se ha registrado la donación de " + cantidad + " por el cliente " + nombreUsuario + " (Total donado: " + cliente.getTotalDonado() + ")");
                this.subtotal += cantidad;
                if (historialDonaciones.containsKey(nombreUsuario))
                {
                    historialDonaciones.put(nombreUsuario, historialDonaciones.get(nombreUsuario) + cantidad);
                }
                else
                {
                    this.historialDonaciones.put(nombreUsuario, (float) cantidad);
                }
                return true;
            }
        }
        return false;
    }
    
    @Override
    public float subtotalDonado(String nombreUsuario, String contrasena) throws RemoteException
    {
        if (this.existeCliente(nombreUsuario))
        {
            return this.subtotal(nombreUsuario, contrasena);
        }
        else 
        {
            if (replica != null)
            {
                return replica.subtotal(nombreUsuario, contrasena);
            }
        }
        return -1;
    }
    
    @Override
    public float subtotal(String nombreUsuario, String contrasena) throws RemoteException
    {
        if (this.existeCliente(nombreUsuario))
        {
            Cliente cliente = this.clientes.get(nombreUsuario);
            if (cliente.compruebaContrasena(contrasena) && cliente.getDonacionesHechas() > 0)
            {
                return this.subtotal;
            }
        }
        return -1;
    }
    
    @Override
    public ArrayList<String> listadoDonantes(String nombreUsuario, String contrasena) throws RemoteException
    {
        if (this.existeCliente(nombreUsuario))
        {
            return this.listado(nombreUsuario, contrasena);
        }
        else 
        {
            if (replica != null)
            {
                return replica.listado(nombreUsuario, contrasena);
            }
        }       
        return new ArrayList<>();
    }
    
    @Override
    public ArrayList<String> listado(String nombreUsuario, String contrasena) throws RemoteException
    {
        if (this.existeCliente(nombreUsuario))
        {
            Cliente cliente = this.clientes.get(nombreUsuario);
            if (cliente.compruebaContrasena(contrasena) && cliente.getDonacionesHechas() > 0)
            {
                ArrayList<String> donantes = new ArrayList<>();
                for ( String donante : clientes.keySet())
                {
                    donantes.add(donante);
                }
                return donantes;
            }
        }
        return new ArrayList<>();
    }

    @Override
    public boolean existeCliente(String nombreUsuario) throws RemoteException
    {
        return this.clientes.containsKey(nombreUsuario);
    }
    
    @Override
    public boolean existeClienteSistema(String nombreUsuario) throws RemoteException
    {
        boolean existeSistema = false;
        updateReplica();
        if (this.replica != null)
        {
            existeSistema = this.replica.existeCliente(nombreUsuario);
        }
        return existeSistema || existeCliente(nombreUsuario);
    }
    
    @Override
    public int getCargaUsuarios() throws RemoteException
    {
        return clientes.size();
    }
    
    @Override
    public String getMenosCarga() throws RemoteException
    {
        if (replica == null)
        {
            return this.nombre;
        }
        else
        {
            if (clientes.size() <= replica.getCargaUsuarios())
            {
                return nombre;
            }
            else
            {
                return replica.getNombre();
            }
        }
        
    }
    
    @Override
    public String getNombre() throws RemoteException
    {
        return this.nombre;
    }
    
    @Override
    public boolean iniciaSesion(String nombreUsuario, String contrasena) throws RemoteException
    {
        if (this.existeCliente(nombreUsuario))
        {
            return comprueba(nombreUsuario, contrasena);
        }
        else 
        {
            if (replica != null)
            {
                return replica.comprueba(nombreUsuario, contrasena);
            }
        }       
        return false;
    }
    
    @Override
    public boolean comprueba(String nombreUsuario, String contrasena) throws RemoteException
    {
        Cliente cliente = clientes.get(nombreUsuario);
        return cliente.compruebaContrasena(contrasena);
    }
    
    @Override
    public ArrayList<String> topDonaciones(String nombreUsuario, String contrasena) throws RemoteException
    {
        if (this.existeCliente(nombreUsuario))
        {
            return this.top(nombreUsuario, contrasena);
        }
        else 
        {
            if (replica != null)
            {
                return replica.top(nombreUsuario, contrasena);
            }
        }       
        return new ArrayList<>();
    }
    
    @Override
    public ArrayList<String> top(String nombreUsuario, String contrasena) throws RemoteException
    {
        if (this.existeCliente(nombreUsuario))
        {
            Cliente cliente = this.clientes.get(nombreUsuario);
            if (cliente.compruebaContrasena(contrasena) && cliente.getDonacionesHechas() > 0)
            {
                System.out.println("Checkpoint 1");
                ArrayList<String> donaciones = new ArrayList<>();
                HashMap<String, Float> copy = new HashMap<>(this.historialDonaciones);
                System.out.println("Checkpoint 2");
                copy.entrySet().stream().sorted(Map.Entry.<String, Float> comparingByValue().reversed()).forEach((entry)->donaciones.add(entry.getKey() + " Donado: " + entry.getValue()));                
                System.out.println(donaciones);
                return donaciones;
            }
        }
        return new ArrayList<>();
    }
    

    @Override
    public float mediaDonaciones(String nombreUsuario, String contrasena) throws RemoteException
    {
        if (this.existeCliente(nombreUsuario))
        {
            return this.media(nombreUsuario, contrasena);
        }
        else 
        {
            if (replica != null)
            {
                return replica.media(nombreUsuario, contrasena);
            }
        }       
        return -1;        
    }
    
    @Override
    public float media(String nombreUsuario, String contrasena) throws RemoteException
    {
        if (this.existeCliente(nombreUsuario))
        {
            Cliente cliente = this.clientes.get(nombreUsuario);
            if (cliente.compruebaContrasena(contrasena) && cliente.getDonacionesHechas() > 0)
            {
                float average = 0;
                for (Map.Entry entry : this.historialDonaciones.entrySet())
                {
                    average += (float) entry.getValue();
                }
                return average / this.historialDonaciones.size();
            }
        }
        return -1;        
    }

    
    private interfacesistemadonaciones getReplica()
    {
        interfacesistemadonaciones replica = null;
        try {
            // Crea el stub para el cliente especificando el nombre del servidor
            Registry mireg = LocateRegistry.getRegistry("", 1099);
            replica = (interfacesistemadonaciones) mireg.lookup(replicaNombre);
        } 
        catch(NotBoundException | RemoteException e) {
            System.err.println("Exception del sistema: " + e);
        }
        return replica;
    }
    
    private void updateReplica()
    {
        this.replica = getReplica();
    }
    
    @Override
    public void ping() throws RemoteException
    {
        System.out.println("soy " + this.nombre + ": PING!!");
    }

}

