import glob
import sys
import math

from calculadora import Calculadora

from calculadora . ttypes import Operations
from calculadora . ttypes import Operation

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
                return op.member1 + op.member2
            case Operations.SUB:
                return op.member1 - op.member2
            case Operations.MUL:
                return op.member1 * op.member2
            case Operations.DIV:
                return op.member1 / op.member2
            case Operations.COS:
                return math.cos(math.radians(op.member1))
            case Operations.SIN:
                return math.sin(math.radians(op.member1))
            case Operations.TAN:
                return math.tan(math.radians(op.member1))
            case Operations.CONVg_r:
                return math.radians(op.member1)
            case Operations.CONVr_g:
                return math.degrees(op.member1)



if __name__ == "__main__":
    handler = CalculadoraHandler()
    processor = Calculadora.Processor(handler)
    transport = TSocket.TServerSocket(host="127.0.0.1", port=9090)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    print("iniciando servidor...")
    server.serve()
    print("fin")
