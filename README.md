##The Elsa Programming Language
A statically typed language that runs on a custom stack based vm

#### Features:

######Functions
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

     fn GetPixel(int x, int y) : Color {
        var stride = 4;
        var base = stride * x * width + y * stride;
        return new Color { R: data[base], G: data[base + 1], B: data[base + 2], A: data[base + 3] };
     }
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
