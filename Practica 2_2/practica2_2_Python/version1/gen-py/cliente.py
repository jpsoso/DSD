from calculadora import Calculadora

import math

from calculadora . ttypes import Operations
from calculadora . ttypes import Operation

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

def print_menu():
    print("========== CALCULADORA ==========")
    print("Operaciones disponibles:")
    print("Suma                        [ + ]")
    print("Resta                       [ - ]")
    print("Multiplicación              [ * ]")
    print("División                    [ / ]")
    print("Seno (grados)               [sin]")
    print("Coseno (grados)             [cos]")
    print("Tangente                    [tan]")
    print("Convertir grados a radianes [g2r]")
    print("Convertir radianes a grados [r2g]")
    print("Salir --------------------> [ e ]")
    print("¿Cuál desea realizar? -> ")

if __name__ == "__main__":
    transport = TSocket.TSocket("localhost", 9090)
    transport = TTransport.TBufferedTransport(transport)
    protocol = TBinaryProtocol.TBinaryProtocol(transport)

    client = Calculadora.Client(protocol)

    try:
        transport.open()
    except:
        print("No se pudo realizar la conexión al servidor")

    operacion = Operation()

    option = ""

    while(option != "e"):
        print_menu()
        option = input()
        if option != "e":
            if option == "+" or option == "-" or option == "*" or option == "/":
                correct = False
                validInput = False
                while not correct:
                    while not validInput:
                        try:
                            validInput = True
                            operacion.member1 = float(input("Introduzca el primer  operando -> "))
                        except ValueError:
                            print("Por favor introduzca un número")
                            validInput = False
                        
                    validInput = False
                    while not validInput:
                        try:
                            validInput = True
                            operacion.member2 = float(input("Introduzca el segundo operando -> "))
                        except ValueError:
                            print("Por favor introduzca un número")
                            validInput = False
                        
                    if operacion.member2 == 0 and option == "/" :
                        print("[ERROR] No se puede dividir por 0")
                    else:
                        correct = True

                match option:
                    case "+":
                        operacion.operating = Operations.ADD
                    case "-":
                        operacion.operating = Operations.SUB
                    case "*":
                        operacion.operating = Operations.MUL
                    case "/":
                        operacion.operating = Operations.DIV
                
                print(f"{operacion} = {client.calculate(operacion)}")

            elif option == "sin" or option == "cos" or option == "tan" or option == "g2r" or option == "r2g":
                validInput = False
                while not validInput:
                    try:
                        validInput = True
                        operacion.member1 = float(input("Introduzca el operando -> "))
                    except ValueError:
                        print("Por favor introduzca un número")
                        validInput = False
                    

                match option:
                    case "sin":
                        operacion.operating = Operations.SIN
                    case "cos":
                        operacion.operating = Operations.COS
                    case "tan":
                        operacion.operating = Operations.TAN
                    case "g2r":
                        operacion.operating = Operations.CONVg_r
                    case "r2g":
                        operacion.operating = Operations.CONVr_g

                print(f"{operacion} = {client.calculate(operacion)}")

            else:
                print("Operación no válida. Por favor, introduzca una operación de entre las disponibles")                   
    
    transport.close()


"""     operacion.member1 = 180
    operacion.member2 = 2
    operacion.operating = Operations.CONVg_r

    print(client.calculate(operacion)) """


