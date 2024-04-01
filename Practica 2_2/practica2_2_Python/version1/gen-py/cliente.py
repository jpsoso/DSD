from calculadora import Calculadora

import math

from calculadora . ttypes import Operations
from calculadora . ttypes import Operation

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

transport = TSocket.TSocket("localhost", 9090)
transport = TTransport.TBufferedTransport(transport)
protocol = TBinaryProtocol.TBinaryProtocol(transport)

client = Calculadora.Client(protocol)

transport.open()

""" print("hacemos ping al server")
client.ping()

resultado = client.suma(1, 1)
print("1 + 1 = " + str(resultado))
resultado = client.resta(1, 1)
print("1 - 1 = " + str(resultado)) """

operacion = Operation()

operacion.member1 = 180
operacion.member2 = 2
operacion.operating = Operations.CONVg_r

print(client.calculate(operacion))

transport.close()
