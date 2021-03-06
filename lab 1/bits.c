/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
       //I do the 2's complement for x and or it with itself. The reason why I did 2's complement instead of 1's complement is because 1's complement does not work with 0. When x is 0, 2's complement of it and OR it with itself is always 0, shift it 31 times is still 0 add 1 is 1. When x is not 0, 2's complement of it and OR it with itself and shift it 31 times is always -1, add 1 is 0. 
       return (((~x + 1) | x) >> 31) + 1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  //make 32 bits to 00010001 00010001...
  int mx = 0x11111111;
  int total = x & mx; //check the LSB of 4 bits in a group, if it sees 1, it increases 1
  int total1 = total + ((x >> 1) & mx); //check the second LSB of 4 bits in a group
  int total2 = total1 + ((x >> 2) & mx); //keep the third LSB of 4 bits
  int total3 = total2 + ((x >> 3) & mx); //keep the MSB of 4 bits
  //now we know that each 4 bits have how many 1, so we add each 4 bits together by shifting it to the right by 4
  int countTotal = total3 & (15); 
  countTotal = countTotal + ((total3 >> 4) & 15);
  countTotal = countTotal + ((total3 >> 8) & 15);
  countTotal = countTotal + ((total3 >> 12) & 15);
  countTotal = countTotal + ((total3 >> 16) & 15);
  countTotal = countTotal + ((total3 >> 20) & 15);
  countTotal = countTotal + ((total3 >> 24) & 15);
  countTotal = countTotal + ((total3 >> 28) & 15);
  return countTotal;
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  //De Morgan's law
  return ~(~x & ~y);
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
  int mx1 = (x & ((1 << (n)) - 1)) | (((~(!!(n & 32)) + 1)) & x);
  int mx2 = mx1 | (mx1 << (n)); 
  int shift = 2 * n;
  mx2 = mx2 | ((mx2 << shift) * (((shift - 32) >> 31) & 1));
  shift = 4 * n;
  mx2 = mx2 | ((mx2 << shift) * (((shift - 32) >> 31) & 1));
  shift = 8 * n;
  mx2 = mx2 | ((mx2 << shift) * (((shift - 32) >> 31) & 1));
  shift = 16 * n;
  mx2 = mx2 | ((mx2 << shift) * (((shift - 32) >> 31) & 1));
  return mx2;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int mx = 32 + ~n + 1;
  return !(x ^ ((x << mx) >> mx));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  //n shifted it by 3 is going to be the number of bits that we want. X is shifted by n << 3 times and and it with 0...11111111.
  return (x >> (n << 3)) & 0xFF;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int sign = ((x^y) >> 31) & 1; //Take care of the sign of integers 
  int mask = 1 << 31;
  return (!(x^y)) | (!((y + (~x + 1)) & mask) & !sign) | (sign & ((x & mask) >> 31));
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  // x is shifted by 31, and Xor it with 1, we know that if it is positive (0), it will yield 1, and if it is negative (1), it will yield 0. And AND it with !!x means x is not 0. If it is 0, it will yield 0.
  return ((x >> 31) ^ 1) & !!x ;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  //-1 shifted to the left by (31 -n) since I cannot use - sign, I replaced it with -1 << 31 >> n << 1. And AND it with all 1 and flip each bit, we will get after n position, it is all 1 and before n position it is all 0. so I AND it with x >> n. 
  int mx = ~ (-1 & (((-1 << 31) >> n) << 1)); 
  return (x >> n) & mx;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  //just shift to the left 31 times, we will get the minimum value of 32 bits integer.
  return 1 << 31;
}
