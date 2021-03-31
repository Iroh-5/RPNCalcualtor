# RPNCalculator
This is a simple calculator that processes expressions written in *Reverse Polish Notation*.
## Supported features:
* simple operations: +, -, *, /, %(only for ints)
* variables
* mathematical functions
* predefined constants(PI, E)
## Usage example:
	Enter expression to calculate or 'q' to quit:
	> 1 2 + 3 *
	= 9
	> 6 5 - 2 3 + *
	= 5
	> let A = 5 // syntax to define a variable
	> A 5 *
	= 25
	> let r = 3.5
	> PI r * r *
	= 38.48451001
	> 25 sqrt
	= 5
	> 2 10 pow
	= 1024
## Restrictions:
* all operands and operators in expressions must be separated with any space character
