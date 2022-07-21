# Graphing-Calculator   
 ![image](https://user-images.githubusercontent.com/71639489/180134955-0582ba39-4c28-437e-ac10-3e7adedc6644.png) width="200"

This application has a minimal interface (in fact, it is a pure backend), it will be of interest to those who want to get acquainted with one of the ways to implement a graphing calculator and understand the algorithm of its work. Graphing Calculator is an application that plots mathematical dependencies. This calculator plots a two-dimensional curve given by an equation with two unknowns. For example, the graph of the equation x^4 + y^4 = x^2 + y * sin(x), built in this program, will look like this.   
![изображение](https://user-images.githubusercontent.com/71639489/179417935-db67870f-256e-4c4f-ac59-b7c47c3a3925.png)   

# Installation   

To compile this project, it is preferable to use MS Visual Studio no older than VS-2015. It is enough to create an empty C++ console application project. The code folder contains 4 files arial.ttf, calc.cpp, calc.h and main.cpp, all these files must be copied to the project root directory. The main.cpp file contains the main program code, calc.h and calc.cpp are the header file and the implementation file of the auxiliary project module, and arial.ttf is the program service file. Also, for the program to work, you need to download and integrate the SFML graphic library into the project, the installation guide can be found here [https://habr.com/en/post/278977/]. When all files are copied and the project is set up, you can start the compilation process through the Visual Studio menu or with the "Ctrl + F5" combination.  

# Usage   

When compilation is complete, a simple console window will appear where you can type in a curve expression and press "Enter". The expression can contain only latin characters "x", "y", digits, separating dot for real numbers ".", signs "+", "-", "*", "/", parentheses "(", ") ", sign equals "=" and designations of standard trigonometric functions sin, cos, tg, ctg. The expression must not contain spaces.   
The curve graph will be displayed in a new window. The graph is zoomed with the mouse wheel.   
