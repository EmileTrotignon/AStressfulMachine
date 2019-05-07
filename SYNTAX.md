# Langage specification

This document is the specification for the langage used by the game.

This langage is used to manipulate a dynamic array of ints.

This array, called the program's memory, with only one cell allocated with 0 as a value.

## Simple operators

These are single character operators.

### IO

#### Operator ','

Asks the input stream for an input (standard input by default)

#### Operator '.'

Output the current operator to the output stream (standard output by default)

### "Arithmetic"

Arithmetic is a big word for what this is

#### Operator '+'

Increments the current cell's value by one

#### Operator '-'

Decrements the current cell's value by one

#### Operator '_'

Set the current cell's value to 0

### Pointer "arithmetic"

#### Operator '>'

Increments the pointer to the current cell.
If there are no more cells, allocate a new one with 0 as a value.

#### Operator '<'

Decrements the pointer to the previous cell
If the current cell is the first, throw an exception

#### Operator '#'

Set the pointer to 0 : the pointed cell is now the first cell.

#### Operator '^'

Set the pointer to the value stored in the current cell.
If negative or greater than the number of cells raises an exception.

## Composite operators

### Operator '*xxx?'

This operator is used to repeat a simple operator a certain number of time (defined statically in the code).

The syntax is the following : *X? where 'X' is the number of time you want to repeat your operator and '?' is the operator you want to repeat.
'?' must be simple operator. If it's not, the behaviour is undefined.

For instance "_*100+^" make the 101th cell the current (and set the previous current cell to 100)

### Gotoes

Things that have something to do with gotoes are always inside brackets.

Gotoes always have two part : the goto itself and the anchor.
There may be multiple gotoes for one anchor.

You define an anchor this way : \[N\] where N is the number of the anchor.

You define a goto this way : \[|CN\] were N is the number of the anchor you want to go to and C is a condition.

#### Conditions

+ '>' : Only go to the anchor if the current value is greater than 0
+ '<' : Only go to the anchor if the current value is lesser than 0
+ '=' : Only go to the anchor if the current value is 0
+ '/' : Only go to the anchor if the current value is not 0
+ No condition : put nothing in place of C and the goto will always be executed.

### Procedures

Things that have to do with procedures are always inside curly brackets.

Procedures are what make this language really higher level than vanilla Brainfuck by introducing some kind of abstraction.

A procedure is a separate program with its outputs and input plugged into the parent program's input and output

Call a procedure this way : {xxxx} where xxxx is the code of the procedure.

Here is a simple exemple that allows you to move a value in memory :

{,.}.>>>,

This will take the current value, and copy it three cells to the right.

This would be impossible to do without affecting the memory if there was no procedures.

Take note that until the procedure's execution is over, ',' and '.' operators do not have the usual behaviour.
Procedures are able to input and output multiple values (higher level than C !!!)

You can call a procedure that is in a file using '~' (defined below)

#### Operator '!'

You can interrupt a procedure with '!'. That allows you to only use one output from a procedure that usually output more.

## Startup operator

These operators only have meaning at the very beginning of a program (or procedure).

#### Operator '~'

This is the file marker. It is used like that : "~FILENAME" where filename is the file where your program is.

This just open the file, and use the content as a program. What is really interesting about that is that you can use it as a procedure call.
"{~add}" will open the file call "add" and use that as the procedure.

#### Memory allocation operator

You can put a number at the beginning of your file in order to tell the interpreter how much memory you will need.
More memory can still be allocated, but the specified quantity will be allocated at startup

The syntax is : "numberPROGRAM" where number is the size of the memory you want to allocate.

Example : "3>><>>++." allocates memory only once.












