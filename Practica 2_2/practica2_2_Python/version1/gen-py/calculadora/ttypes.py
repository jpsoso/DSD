#
# Autogenerated by Thrift Compiler (0.16.0)
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#
#  options string: py
#

from thrift.Thrift import TType, TMessageType, TFrozenDict, TException, TApplicationException
from thrift.protocol.TProtocol import TProtocolException
from thrift.TRecursive import fix_spec

import sys

from thrift.transport import TTransport
all_structs = []


class Operations(object):
    ADD = 0
    SUB = 1
    MUL = 2
    DIV = 3
    SIN = 4
    COS = 5
    TAN = 6
    CONVg_r = 7
    CONVr_g = 8

    _VALUES_TO_NAMES = {
        0: "ADD",
        1: "SUB",
        2: "MUL",
        3: "DIV",
        4: "SIN",
        5: "COS",
        6: "TAN",
        7: "CONVg_r",
        8: "CONVr_g",
    }

    _NAMES_TO_VALUES = {
        "ADD": 0,
        "SUB": 1,
        "MUL": 2,
        "DIV": 3,
        "SIN": 4,
        "COS": 5,
        "TAN": 6,
        "CONVg_r": 7,
        "CONVr_g": 8,
    }


class Operation(object):
    """
    Attributes:
     - member1
     - member2
     - operating

    """


    def __init__(self, member1=None, member2=None, operating=None,):
        self.member1 = member1
        self.member2 = member2
        self.operating = operating

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, [self.__class__, self.thrift_spec])
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.DOUBLE:
                    self.member1 = iprot.readDouble()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.DOUBLE:
                    self.member2 = iprot.readDouble()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.I32:
                    self.operating = iprot.readI32()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('Operation')
        if self.member1 is not None:
            oprot.writeFieldBegin('member1', TType.DOUBLE, 1)
            oprot.writeDouble(self.member1)
            oprot.writeFieldEnd()
        if self.member2 is not None:
            oprot.writeFieldBegin('member2', TType.DOUBLE, 2)
            oprot.writeDouble(self.member2)
            oprot.writeFieldEnd()
        if self.operating is not None:
            oprot.writeFieldBegin('operating', TType.I32, 3)
            oprot.writeI32(self.operating)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        return

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)
    
    def __str__(self) -> str:
        toReturn = ""
        match self.operating:
            case Operations.ADD:
                toReturn = f"{self.member1} + {self.member2}"
            case Operations.SUB:
                toReturn = f"{self.member1} - {self.member2}"
            case Operations.MUL:
                toReturn = f"{self.member1} * {self.member2}"
            case Operations.DIV:
                toReturn = f"{self.member1} / {self.member2}"
            case Operations.COS:
                toReturn = f"cos({self.member1})"
            case Operations.SIN:
                toReturn = f"sin({self.member1})"
            case Operations.TAN:
                toReturn = f"tan({self.member1})"
            case Operations.CONVg_r:
                toReturn = f"convGradosARadianes({self.member1})"
            case Operations.CONVr_g:
                toReturn = f"convRadianesAGrados({self.member1})" 
        return toReturn        

all_structs.append(Operation)
Operation.thrift_spec = (
    None,  # 0
    (1, TType.DOUBLE, 'member1', None, None, ),  # 1
    (2, TType.DOUBLE, 'member2', None, None, ),  # 2
    (3, TType.I32, 'operating', None, None, ),  # 3
)
fix_spec(all_structs)
del all_structs
