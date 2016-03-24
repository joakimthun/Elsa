##The Elsa Programming Language
A statically typed language that runs on a custom stack based vm

![alt tag](https://raw.githubusercontent.com/joakimthun/Elsa/blob/master/src/examples/bouncy.png)

#### Features:

######Basic functions
```
  // A function that takes no arguments and returns void
  fn hello() {
     PrintLn("Hello world!");
  }
 
  // A function the takes an integer argument and returns an integer
  fn returnInt(int x) : int {
     return x;
  }
```

When passing arguments to functions all built-in types are passed by value while structs and arrays are passed by reference(pointers)

######Closures
```
  // Functions in Elsa are treated as any other "object" and can be passed around and assigned to variables.
  // If a functions uses any variables from the context in which it was declared the function will 
  // keep a reference to that variable
  
  var x = 10;
  var ret = fn : int => { return x; }; // A function that takes no arguments and returns the integer captured from the outer scope
  var inc = fn => { x = x + 1; };      // A function that takes no arguments, returns void and increments the captured variable by 1
  
  inc(); // x is now 11
  PrintLn(ret()); // Prints 11
  
  // A function that takes another function(taking no arguments and returns void) as an arguments an invokes it twice
  fn callTwice(fn f) {
     f();
     f();
  }
  
  callTwice(inc); // callTwice will call our inc function twice
  PrintLn(ret()); // Prints 13
  PrintLn(x); // Prints 13
```


######Variables and built-in types
```
  int i = 0;
  int h = 0xffff;
  float f = 0.0;
  char c = '0';
  bool t = true;
  byte b = byte(0);
  byte b2 = byte(0xff);
  
  // Variables can also be declared by using the var keyword and letting the compiler infer the type
  var x = 15; // int
  
  // All built-in types in Elsa have default values
  int: 0
  float: 0.0
  char: '\0'
  byte: 0
  
  // Array and struct instances will be null pointers if not instantiated with the new keyword (see the struct section)
```


######Type conversions
```
  var floatToInt = int(10.0);
  var intToFloat = float(10);
  var intToChar = char(33);
  var charToInt = int('!');
  var intToByte = byte(10);
```


######Operators and precedence
```
  var x1 = (3 + 5) * 6;                                 // 48
  var x2 = (3 + 5) * (6 + 8);                           // 112
  var x3 = (3 + 5 * 6) * 6;                             // 198
  var x4 = (3 + 5  / (1 * 6)) * (6 + 8 * (2 - 1));      // 42
  var x5 = true || (true && false);                     // true
  var x6 = (true && false) || (false || false);         // false
  var x7 = (1 == 1 && 2 == 2) && (7 == 8 || 0 != 8);    // true
  
  // Binary operators
  x << 1;
  x >> 1;
  x | y;
  x & y;
  
  byte x1 = 0xFF;
  byte y1 = 0xFF;
  var r = (int(x1) << 8) | int(y1);   // 65535
```


######Arrays
```
  var arr = new int[10]; // An array of integers with an intial size of 10
  var arr2 = new [1, 2, 3, 4, 5, 6]; // Arrays can also be defined ny using array literals
  
  // Array member functions
  arr.Push(1);  // Adds the integer 1 to the back of the array
  arr.Pop();    // Pops the last element in the array, pop returns the popped element
  arr.Length(); // Returns the array length
  
  // Array operators
  arr[2];       // Access the element at index 2 in the array
```


######Branching
```
  if(x == 10) {
     PrintLn("x == 10");
  }
  else {
     // The else block can be omitted
     PrintLn("x == 10");
  }
``` 


######Loops
```
  for(var i = 0; i < arr.Length(); i++)
  {
     PrintLn(arr[i]);
  }
  
  while(y || x) {
     PrintLn("Loopy loop");
  }
``` 


######Structs
```
  struct Bitmap {
     byte[] data;
     int width;
     int height;

     // Member function
     fn GetPixel(int x, int y) : Color {
        var stride = 4;
        var base = stride * x * width + y * stride;
        return new Color { R: data[base], G: data[base + 1], B: data[base + 2], A: data[base + 3] };
     }
  };
  
  struct Color {
     byte R;
     byte G;
     byte B;
     byte A;
  };
  
  // Struct instances are created by using the new keyword
  var red = new Color { R: 0xFF, G: o, B: o, A: 0xFF }; 
``` 


######Enums
```
  // Enums in Elsa are just integers converted by the compiler at compile time
  enum Enum {
     Zero,      // 0
     Three = 3, // 3
     Four,      // 4
     Seven = 7  // 7
  };
``` 


######Example VM-program:
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
