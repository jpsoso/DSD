from calculadora import Calculadora

import math
import sys

from calculadora . ttypes import *

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

def printMainMenu():
    print("========== CALCULADORA ========== ")
    print("Seleccione un modo:")
    print("[ 1 ] Modo operaciones simples    ")
    print("[ 2 ] Modo operaciones vectoriales")
    print("[ e ] Salir de la calculadora     ")

def printSimpleOperationMenu():
    print("========== CALCULADORA ==========")
    print("Operaciones simples disponibles:")
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

def doSimpleOperation():
    operacion = Operation()
    option = ""
    while(option != "e"):
        printSimpleOperationMenu()
        option = input("¿Cuál desea realizar? -> ")
        if option != "e":
            if option == "+" or option == "-" or option == "*" or option == "/":
                correct = False
                validInput = False

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

                match option:
                    case "+":
                        operacion.operating = Operations.ADD
                    case "-":
                        operacion.operating = Operations.SUB
                    case "*":
                        operacion.operating = Operations.MUL
                    case "/":
                        operacion.operating = Operations.DIV
                
                try:
                    print(f"{operacion} = {client.calculate(operacion)}")
                except InvalidOperation as error:
                    print("Operación no válida: %r" % error)

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

                try:
                    print(f"{operacion} = {client.calculate(operacion)}")
                except InvalidOperation as error:
                    print("Operación no válida: %r" % error)
            else:
                print("Operación no válida. Por favor, introduzca una operación de entre las disponibles")                   
    
def printVectorOperationMenu():
    print("=========== CALCULADORA ============")
    print("Operaciones vectoriales disponibles:")
    print("Suma                           [ + ]")
    print("Resta                          [ - ]")
    print("Producto Escalar               [ · ]")
    print("Multiplicar vector por escalar [ * ]")
    print("Salir -----------------------> [ e ]")

def doVectorOperation():
    operacion = vector_Operation([], [])
    option = ""
    while (option != "e"):
        printVectorOperationMenu()
        option = input("¿Cuál desea realizar? -> ")
        if (option != "e"):
            if option == "+" or option == "-" or option == "·" or option == "*":
                if option == "*":
                    operacion.member1.append(float(input("Introduce el escalar -> ")))
                    validInput = False
                    while not validInput:
                        size = int(input("¿De qué tamaño es el vector? -> "))
                        if size > 0:
                            validInput = True
                        else:
                            print("Introduzca un tamaño válido")
                    for i in range(size):
                        validInput = False
                        while not validInput:
                            try:
                                validInput = True
                                operacion.member2.append(float(input(f"vector[{i}] -> ")))
                            except ValueError:
                                print("Por favor introduzca un número")
                                validInput = False

                    operacion.operating = Operations.MUL_Esc
                    try:
                        print(f"{operacion} \n = \n {client.calculateVec(operacion)}")
                    except InvalidOperation as error:
                        print("Operación no válida: %r" % error)
                    operacion.member1.clear()
                    operacion.member2.clear()  
                                
                else:
                    validInput = False
                    while not validInput:
                        size = int(input("¿De qué tamaño son los vectores? -> "))
                        if size > 0:
                            validInput = True
                        else:
                            print("Introduzca un tamaño válido")
                    for i in range(size):
                        validInput = False
                        while not validInput:
                            try:
                                validInput = True
                                operacion.member1.append(float(input(f"vector1[{i}] -> ")))
                            except ValueError:
                                print("Por favor introduzca un número")
                                validInput = False
                    for i in range(size):
                        validInput = False
                        while not validInput:
                            try:
                                validInput = True
                                operacion.member2.append(float(input(f"vector2[{i}] -> ")))
                            except ValueError:
                                print("Por favor introduzca un número")
                                validInput = False

                    match option:
                        case "+":
                            operacion.operating = Operations.ADD
                        case "-":
                            operacion.operating = Operations.SUB
                        case "·":
                            operacion.operating = Operations.P_Esc

                    try:
                        print(f"{operacion} \n = \n {client.calculateVec(operacion)}")
                    except InvalidOperation as error:
                        print("Operación no válida: %r" % error)
                    operacion.member1.clear()
                    operacion.member2.clear()  
            else:
                print("Operación no válida. Por favor, introduzca una operación de entre las disponibles")  


if __name__ == "__main__":
    transport = TSocket.TSocket("localhost", 9090)
    transport = TTransport.TBufferedTransport(transport)
    protocol = TBinaryProtocol.TBinaryProtocol(transport)

    client = Calculadora.Client(protocol)

    try:
        transport.open()
    except:
        print("No se encontró el servidor")
        sys.exit(1)

    option = ""
    while (option != "e"):
        printMainMenu()
        option = option = input("¿Cuál desea realizar? -> ")
        if (option != "e"):
            match option:
                case "1":
                    doSimpleOperation()
                case "2":
                    doVectorOperation()


    transport.close()


