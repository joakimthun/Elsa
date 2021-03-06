## The Elsa Programming Language
A statically typed, garbage collected language that runs on a custom stack based vm.
Elsa is written just for fun(and educational purposes) and is not really intended for actual use.

#### Examples:
[Bouncy](../master/src/examples/bouncy): A Breakout clone written in Elsa
![alt tag](https://raw.githubusercontent.com/joakimthun/Elsa/master/src/examples/bouncy.png)

#### Running Bouncy
Download the latest release from [here](https://github.com/joakimthun/Elsa/releases).
Then just run "elsa bouncy/main.elsa" from the command line

#### Language features:

###### Basic functions
```
  // The main function is the entry point of all Elsa programs and is always required
  fn main() {
     
  }
  
  // A function that takes no arguments and returns void
  fn hello() {
     PrintLn("Hello world!");
  }
 
  // A function that takes an integer argument and returns an integer
  fn returnInt(int x) : int {
     return x;
  }
```

When passing arguments to functions all built-in types are passed by value while structs and arrays are passed by reference(pointers)

###### Closures
```
  // All types of functions(including member functions) in Elsa are treated as any other 
  // "object" and can be passed around and assigned to variables.
  
  // If a functions uses any variables or fields from the context in which it was declared 
  // the function will keep a reference to that variable or field
  
  var x = 10;
  
  // A function that takes no arguments and returns the integer captured from the outer scope
  var ret = fn : int => { return x; };
  
  // A function that takes no arguments, returns void and increments the captured variable by 1
  var inc = fn => { x = x + 1; }; 
  
  inc(); // x is now 11
  PrintLn(ret()); // Prints 11
  
  // A function that takes another function(taking no arguments and returns void) as an argument
  // and invokes the passed function twice
  fn callTwice(fn f) {
     f();
     f();
  }
  
  callTwice(inc); // callTwice will call our inc function twice
  PrintLn(ret()); // Prints 13
  PrintLn(x); // Prints 13
```


###### Variables and built-in types
```
  int i = 0;
  int h = 0xffff;
  float f = 0.0;
  char c = '0';
  bool t = true;
  byte b = byte(0);
  byte b2 = byte(0xff);
  
  // Variables can also be declared by using the var keyword 
  // and letting the compiler infer the type
  var x = 15; // int
  
  // All built-in types in Elsa have default values
  int: 0
  float: 0.0
  char: '\0'
  byte: 0
  
  // Array and struct instances will be null pointers if not instantiated 
  // with the new keyword (see the struct section)
```

###### Strings
```
  // The String struct in Elsa is very incomplete but has some basic functionality

  // Creating new string instances
  var str = "Hello World!";
  var first =  "123";
  var second = "123";

  // Retrives a char at the specified index
  str.CharAt(1) // e
  
  // Returns the length of the string as an integer
  str.Length() // 12

  // Comparing strings, the String struct define its own Equals-function
  // see the Structs section for more info
  first.Equals(second)); // true
  first == second;       // true    
  first != second;       // false
  
  // Concatenating strings
  var third = first.Concat(second); // third == "123123"
  
  // Substring, substring takes 2 integer arguments
  // the start index and the number of chars to grab
  third.Substring(0, 3); // "123"
```

The source code for the String struct can be found [here](../master/src/std/string.elsa)

###### Type conversions
```
  var floatToInt = int(10.0);
  var intToFloat = float(10);
  var intToChar = char(33);
  var charToInt = int('!');
  var intToByte = byte(10);
```


###### Operators and precedence
```
  var x1 = (3 + 5) * 6;                                 // 48
  var x2 = (3 + 5) * (6 + 8);                           // 112
  var x3 = (3 + 5 * 6) * 6;                             // 198
  var x4 = (3 + 5  / (1 * 6)) * (6 + 8 * (2 - 1));      // 42
  var x5 = true || (true && false);                     // true
  var x6 = (true && false) || (false || false);         // false
  var x7 = (1 == 1 && 2 == 2) && (7 == 8 || 0 != 8);    // true
  var x8 = 10 % 3;                                      // 1
  
  // Binary operators
  x << 1;
  x >> 1;
  x | y;
  x & y;
  
  byte x1 = 0xFF;
  byte y1 = 0xFF;
  var r = (int(x1) << 8) | int(y1);   // 65535
```


###### Arrays
```
  var arr = new int[10]; // An array of integers with an intial capacity of 10
  var arr2 = new [1, 2, 3, 4, 5, 6]; // Arrays can also be defined by using array literals
  
  // Array member functions
  arr.Push(1);  // Adds the integer 1 to the back of the array
  arr.Pop();    // Pops the last element in the array, pop returns the popped element
  arr.Length(); // Returns the array length
  
  // Array operators
  arr[2];       // Access the element at index 2 in the array
```


###### Branching
```
  if(x == 10) {
     PrintLn("x == 10");
  }
  else {
     // The else block can be omitted
     PrintLn("x == 10");
  }
``` 


###### Loops
```
  for(var i = 0; i < arr.Length(); i++)
  {
     PrintLn(arr[i]);
  }
  
  while(y || x) {
     PrintLn("Loopy loop");
  }
``` 


###### Structs
```
  struct Bitmap {
     // Fields are declared like this
     byte[] data;
     int width;
     int height;

     // Member functions are declared like any other function but inside a struct declaration
     fn GetPixel(int x, int y) : Color {
        var stride = 4;
        var base = stride * x * width + y * stride;
        return new Color { R: data[base], G: data[base + 1], B: data[base + 2], A: data[base + 3] };
     }
     
     // The Equals-function is special. If two struct instances(of the same type) are compared with the
     // == operator the Equals-function is automatically called.
     // If no Equals-function is declared, a check for reference equality is done
     fn Equals(Bitmap other) : bool {
        return true;
     }
  };
  
  struct Color {
     byte R;
     byte G;
     byte B;
     byte A;
  };
  
  // Struct instances are created by using the new keyword
  var red = new Color;
  
  // Elsa also supports initializer lists
  var red = new Color { R: 0xFF, G: o, B: o, A: 0xFF }; 
``` 


###### Enums
```
  // Enums in Elsa are just integers converted by the compiler at compile time
  enum Enum {
     Zero,      // 0
     Three = 3, // 3
     Four,      // 4
     Seven = 7  // 7
  };
``` 

###### Working with multiple source files
```
  // Including stuff from other .elsa source files is done with the use keyword
  use "std/io";

  fn main() {
     PrintLn(z);
  }
```

###### Standard library
Elsa has a very small standard library with basic functions for printing stuff to the console, 
opening a window(and drawing basic shapes), reading files etc.

All standard library functions and structs can be found [here](../master/src/std)

#### Building and OS support
Elsa only runs on Windows(at least right now) and has only been tested with the Visual C++ Compiler

###### Example VM-program:
```
    // factorial (10)
	iconst, 1,
	l_arg, 0,
	br_ineq, 9,
	iconst, 1,
	ret,
	l_arg, 0,
	l_arg, 0,
	iconst, 1,
	isub,
	call, 0,
	imul,
	ret,

	// main
	iconst, 10,
	call, 0,
	halt
```
