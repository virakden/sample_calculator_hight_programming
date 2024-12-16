# Calculator Program

This is a command-line calculator tool that reads input from a text file and outputs the result to another text file.

## Features

- Reads input from a specified input text file
- Performs calculations using the calculator tool
- Outputs results to a 'result.txt' file in the same directory

## Capability
- Supports three number systems: Binary (base 2), Decimal (base 10), and Hexadecimal (base 16)
- Handles arithmetic operators (+, -, x, /)
- Supports exponentiation (^)
- Includes trigonometric functions (sin(), cos())
- Allows grouping expressions with parentheses ()
- Defines and uses variables
- Handles arbitrary-length expressions
- Outputs results in Decimal format regardless of input base

## Usage

1. Create an input text file with your calculations in it.
2. Navigate to the bin directory containing program calc file.
3. Run the calculator tool using the following command:
    ```bash
    ./calc ./path/input_file_name.txt
    ```
   Replace `input_file_name.txt` with the name of your input text file.
   

4. The results will be output to a `result.txt` file in the same directory.
 
## Input file format
- Example: input.txt
    
    ```bash
    ---
    21 - 1
    ---
    10111b * 9
    ---
    sin(0)
    ---
    i = 0x17
    i+(8-15/5)^6/3
    ```
    
- A text file containing the following this grammer 
    - One Session := header \n
                   [variable_definitions] \n
                   expression
    - header := “----”
    - variable_definitions := variable_define \n
                            [varaible_defines]
    - variable_define := varaible_name = number
    - variable_name := sequence_of_upper_or_lower_letters
    - number := decimal_number | hexadecimal_number |
                     binary_number
    - hexadecimal_number := “0x” sequence_of_0_9_A_F
    - binary_number := sequence_of_0_1 “b”
    - expression := number |
             “(“ expression “)” |
             expression operator expression |
             function “(“ expression “)”
    - operator := “+” | “-” | “*” | “/” | “^”
    - function := “sin” | “cos”


