import glob
import sys
import math

from calculadora import Calculadora

from calculadora . ttypes import *

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

import logging

logging.basicConfig(level=logging.DEBUG)


class CalculadoraHandler:
    def __init__(self):
        self.log = {}

    def calculate(self, op):
        match op.operating:
            case Operations.ADD:
                result = op.member1 + op.member2
                print(f"Calculando suma. Resultado: {result}")
                return result
            case Operations.SUB:
                result = op.member1 - op.member2
                print(f"Calculando resta. Resultado: {result}")
                return result
            case Operations.MUL:
                result = op.member1 * op.member2
                print(f"Calculando multiplicación. Resultado: {result}")
                return result
            case Operations.DIV:
                if op.member2 == 0:
                    raise InvalidOperation("No se puede dividir por 0")
                result = op.member1 / op.member2
                print(f"Calculando división. Resultado: {result}")
                return result
            case Operations.COS:
                result = math.cos(math.radians(op.member1))
                print(f"Calculando coseno. Resultado: {result}")
                return result 
            case Operations.SIN:
                result = math.sin(math.radians(op.member1))
                print(f"Calculando seno. Resultado: {result}")
                return result
            case Operations.TAN:
                result = math.tan(math.radians(op.member1))
                print(f"Calculando tangente. Resultado: {result}")
                return result
            case Operations.CONVg_r:
                result = math.radians(op.member1)
                print(f"Convirtiendo a radianes. Resultado: {result}")
                return result
            case Operations.CONVr_g:
                result = math.degrees(op.member1)
                print(f"Convirtiendo a grados. Resultado: {result}")
                return result

    def calculateVec(self, op):
        result = []
        match op.operating:
            case Operations.ADD:
                if len(op.member1) == len(op.member2) and len(op.member1) > 0:
                    for i in range(len(op.member1)):
                        result.append(op.member1[i] + op.member2[i])
                    print(f"Resultado de la suma de vectores {result}")
                    return result
                else:
                    raise InvalidOperation("El tamaño de los vectores debe de ser el mismo, además de no nulo")
            case Operations.SUB:
                if len(op.member1) == len(op.member2) and len(op.member1) > 0:
                    for i in range(len(op.member1)):
                        result.append(op.member1[i] - op.member2[i])
                    print(f"Resultado de la resta de vectores {result}")
                    return result
                else:
                    raise InvalidOperation("El tamaño de los vectores debe de ser el mismo, además de no nulo")
            case Operations.P_Esc:
                if len(op.member1) == len(op.member2) and len(op.member1) > 0:
                    for i in range(len(op.member1)):
                        result.append(0)
                        result[0] += (op.member1[i] * op.member2[i])
                    print(f"Resultado del producto escalar {result}")
                    return result
                else:
                    raise InvalidOperation("El tamaño de los vectores debe de ser el mismo, además de no nulo")  
            case Operations.MUL_Esc:
                if len(op.member2) > 0:
                    for i in range(len(op.member2)):
                        result.append((op.member1[0] * op.member2[i]))
                    print(f"Resultado de multiplicar el escalar {result}")
                    return result
                else:
                    raise InvalidOperation("Introduzca un escalar y un vector de tamaño no nulo")     




if __name__ == "__main__":
    handler = CalculadoraHandler()
    processor = Calculadora.Processor(handler)
    transport = TSocket.TServerSocket(host="127.0.0.1", port=9090)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    print("Iniciando el servidor...")
    server.serve()
