/****************************************************************************
**
*W  integer.h                   GAP source                   Martin Schoenert
**                                                           & Alice Niemeyer
**                                                           & Werner  Nickel
**
*H  @(#)$Id: integer.h,v 4.10 2002/04/15 10:03:50 sal Exp $
**
*Y  Copyright (C)  1996,  Lehrstuhl D fuer Mathematik,  RWTH Aachen,  Germany
*Y  (C) 1998 School Math and Comp. Sci., University of St.  Andrews, Scotland
*Y  Copyright (C) 2002 The GAP Group
**
**  This file declares the functions handling arbitrary size integers.
*/
#ifdef  INCLUDE_DECLARATION_PART
const char * Revision_integer_h =
   "@(#)$Id: integer.h,v 4.10 2002/04/15 10:03:50 sal Exp $";
#endif


/****************************************************************************
**

*T  TypDigit  . . . . . . . . . . . . . . . . . . . .  type of a single digit
**
**  'TypDigit' is the type of a single digit of an  arbitrary  size  integer.
**  This is of course unsigned short int, which gives us the 16 bits we want.
*/
#ifdef SYS_IS_64_BIT
typedef UInt4           TypDigit;
#else
typedef UInt2           TypDigit;
#endif

#define NR_DIGIT_BITS      (8 * sizeof(TypDigit))
#define INTBASE            (1L << NR_DIGIT_BITS)
#define NR_SMALL_INT_BITS  (2*NR_DIGIT_BITS - 4)

/****************************************************************************
**
*F  PrintInt( <int> ) . . . . . . . . . . . . . . . print an integer constant
**
**  'PrintInt'  prints  the integer  <int>   in the  usual  decimal notation.
**  'PrintInt' handles objects of type 'T_INT', 'T_INTPOS' and 'T_INTNEG'.
*/
extern  void            PrintInt (
            Obj                 op );


/****************************************************************************
**
*F  EqInt( <intL>, <intR> ) . . . . . . . . .  test if two integers are equal
**
**  'EqInt' returns 1  if  the two integer   arguments <intL> and  <intR> are
**  equal and 0 otherwise.
*/
extern  Int             EqInt ( 
            Obj                 opL,
            Obj                 opR );


/****************************************************************************
**
*F  LtInt( <intL>, <intR> ) . . . . . test if an integer is less than another
**
**  'LtInt' returns 1 if the integer <intL> is strictly less than the integer
**  <intR> and 0 otherwise.
*/
extern  Int             LtInt (
            Obj                 opL,
            Obj                 opR );


/****************************************************************************
**
*F  SumInt( <intL>, <intR> )  . . . . . . . . . . . . . . sum of two integers
**
**  'SumInt' returns the sum of the two integer arguments <intL> and  <intR>.
**  'SumInt' handles operands of type 'T_INT', 'T_INTPOS' and 'T_INTNEG'.
**
**  It can also be used in the cases that both operands  are  small  integers
**  and the result is a small integer too,  i.e., that  no  overflow  occurs.
**  This case is usually alread<<y handled in 'EvSum' for a better  efficiency.
*/
extern  Obj             SumInt (
            Obj                 opL,
            Obj                 opR );


/****************************************************************************
**
*F  DiffInt( <intL>, <intR> ) . . . . . . . . . .  difference of two integers
**
**  'DiffInt' returns the difference of the two integer arguments <intL>  and
**  <intR>.  'DiffInt' handles  operands  of  type  'T_INT',  'T_INTPOS'  and
**  'T_INTNEG'.
**
**  It can also be used in the cases that both operands  are  small  integers
**  and the result is a small integer too,  i.e., that  no  overflow  occurs.
**  This case is usually already handled in 'EvDiff' for a better efficiency.
*/
extern  Obj             DiffInt (
            Obj                 opL,
            Obj                 opR );


/****************************************************************************
**
*F  ProdInt( <intL>, <intR> ) . . . . . . . . . . . . product of two integers
**
**  'ProdInt' returns the product of the two  integer  arguments  <intL>  and
**  <intR>.  'ProdInt' handles  operands  of  type  'T_INT',  'T_INTPOS'  and
**  'T_INTNEG'.
**
**  It can also be used in the cases that both operands  are  small  integers
**  and the result is a small integer too,  i.e., that  no  overflow  occurs.
**  This case is usually already handled in 'EvProd' for a better efficiency.
*/
extern  Obj             ProdInt (
            Obj                 opL,
            Obj                 opR );


/****************************************************************************
**
*F  ModInt( <intL>, <intR> )  . . representant of residue class of an integer
**
**  'ModInt' returns the smallest positive representant of the residue  class
**  of the  integer  <intL>  modulo  the  integer  <intR>.  'ModInt'  handles
**  operands of type 'T_INT', 'T_INTPOS', 'T_INTNEG'.
**
**  It can also be used in the cases that both operands  are  small  integers
**  and the result is a small integer too,  i.e., that  no  overflow  occurs.
**  This case is usually already handled in 'EvMod' for a better efficiency.
*/
extern  Obj             ModInt (
            Obj                 opL,
            Obj                 opR );


/****************************************************************************
**
*F  PowInt( <intL>, <intR> )  . . . . . . . . . . . . . . power of an integer
**
**  'PowInt' returns the <intR>-th (an integer) power of the integer  <intL>.
**  'PowInt' is handles operands of type 'T_INT', 'T_INTPOS' and 'T_INTNEG'.
**
**  It can also be used in the cases that both operands  are  small  integers
**  and the result is a small integer too,  i.e., that  no  overflow  occurs.
**  This case is usually already handled in 'EvPow' for a better  efficiency.
*/
extern  Obj             PowInt (
            Obj                 opL,
            Obj                 opR );


/****************************************************************************
**
*F  QuoInt( <intL>, <intR> )  . . . . . . . . . . . quotient of two integers
**
**  'QuoInt' returns the integer part of the two integers <intL> and  <intR>.
**  'QuoInt' handles operands of type  'T_INT',  'T_INTPOS'  and  'T_INTNEG'.
**
**  It can also be used in the cases that both operands  are  small  integers
**  and the result is a small integer too,  i.e., that  no  overflow  occurs.
**
**  Note that this routine is not called from 'EvQuo', the  division  of  two
**  integers yields  a  rational  and  is  therefor  performed  in  'QuoRat'.
**  This operation is however available through the internal function 'Quo'.
*/
extern  Obj             QuoInt (
            Obj                 opL,
            Obj                 opR );


/****************************************************************************
**
*F  RemInt( <intL>, <intR> )  . . . . . . . . . . . remainder of two integers
**
**  'RemInt' returns the remainder of the quotient  of  the  integers  <intL>
**  and <intR>.  'RemInt' handles operands of type  'T_INT',  'T_INTPOS'  and
**  'T_INTNEG'.
**
**  Note that the remainder is different from the value returned by the 'mod'
**  operator which is always positive.
*/
extern  Obj             RemInt (
            Obj                 opL,
            Obj                 opR );


/****************************************************************************
**
*F  GcdInt( <opL>, <opR> )  . . . . . . . . . . . . . . . gcd of two integers
**
**  'GcdInt' returns the gcd of the two integers <opL> and <opR>.
*/
extern  Obj             GcdInt (
            Obj                 opL,
            Obj                 opR );


/****************************************************************************
**

*F * * * * * * * * * * * * * initialize package * * * * * * * * * * * * * * *
*/

/****************************************************************************
**                                              \
                                                \

*F  InitInfoInt() . . . . . . . . . . . . . . . . . . table of init functions
*/
StructInitInfo * InitInfoInt ( void );


/****************************************************************************
**

*E  integer.c . . . . . . . . . . . . . . . . . . . . . . . . . . . ends here
*/
