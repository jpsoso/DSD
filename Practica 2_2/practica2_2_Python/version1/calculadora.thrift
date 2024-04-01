enum Operations
{
   ADD = 0;
   SUB = 1;
   MUL = 2;
   DIV = 3;
   SIN = 4;
   COS = 5;
   TAN = 6;
   CONVg_r = 7,
   CONVr_g = 8
}

struct Operation
{
   1: optional double member1;
   2: optional double member2;
   3: optional Operations operating
}

service Calculadora
{
   double calculate(1:Operation op)
}
