##The Elsa Programming Language

####VM (In progress) 
####Compiler (TODO)

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
