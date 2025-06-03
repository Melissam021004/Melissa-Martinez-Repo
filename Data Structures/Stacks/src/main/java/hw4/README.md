# Discussion

**Document all error conditions you determined and why they are error
conditions. Do this by including the inputs that you used to test your
program and what error conditions they exposed:**

Invalid token (given in instructions)
This error occurs if something is passed that is not an integer value, a valid operation, or a valid command.
To test this, I ran multiple words and combinations of operations such as "hello", "2.0", and "+?-" (note no spaces) and ensured these printed errors. 

Dividing or modding by 0
This is an error condition because dividing by 0 is impossible. I applied this before testing for it because it is a general rule of division, and therefore modulo.
To test this, I ran the line "7 0 / ?" and "7 0 % ?" as the first lines to ensure that it would not divide or modify the list. 

Trying to print top value of empty stack
I figured this out by trying to test the valid tokens on an empty stack and received an error when I used the period. This cannot be done because the top value does not exist at that moment.
For example, calling "." as the first command, which would be on an empty stack, resulted in an exception being thrown. 

Not enough integers
I determined this error by trying to apply the operations on stacks of various sizes and I received errors when the stack was 1.
For instance, an input of "1 +" would throw exceptions if the stack was empty before the operation, and worked similarly for other operations. 