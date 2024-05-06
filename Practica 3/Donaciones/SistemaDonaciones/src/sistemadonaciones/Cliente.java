/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package sistemadonaciones;

/**
 *
 * @author jesusp
 */
public class Cliente {
    private String nombreUsuario, contrasena;
    private float totalDonado;
    private int donacionesHechas;
    
    public Cliente(String nombreUsuario, String contrasena)
    {
        this.nombreUsuario = nombreUsuario;
        this.contrasena = contrasena;
        totalDonado = 0;
        donacionesHechas = 0;
    }

    public String getNombreUsuario() 
    {
        return nombreUsuario;
    }

    public float getTotalDonado() 
    {
        return totalDonado;
    }

    public int getDonacionesHechas() 
    {
        return donacionesHechas;
    }
    
    public boolean compruebaContrasena(String contrasena)
    {
        return this.contrasena.equals(contrasena);
    }
    
    public void setNombreUsuario(String nombreUsuario) 
    {
        this.nombreUsuario = nombreUsuario;
    }

    public void setContrasena(String contrasena) 
    {
        this.contrasena = contrasena;
    }

    public void setTotalDonado(float totalDonado) 
    {
        this.totalDonado = totalDonado;
    }

    public void setDonacionesHechas(int donacionesHechas) 
    {
        this.donacionesHechas = donacionesHechas;
    }
    
    
}
