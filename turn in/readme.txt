

who's file: Xiaomin Wu


Xiaomin Wu: 1.add, store,load global 2.function detect,clone,replace 3.called func return  4.testing 


examples you have tested and result:
-example0.c	good
-example1.c	good
-example2.c	good
-example3.c	good
-example4.c	good
-demo2.c (changed many version during testing)	good
-demo3.c	good

files include: Clonefunc.cpp example0clonefunc example1clonefunc example2clonefunc example3clonefunc example4clonefunc demo2clonefunc demo3clonefunc 
		Makefile readme.txt runtest readex checkresult clean 

method/commands to run test your code: 
Set LLVM environment according to instruction of project
Should have directory: demo645/obj	demo645/opt	demo645/sample	project645/
in demo645/sample/lib/ create Clonefunc directory and put Makefile and Clonefunc.cpp in it
First should configure LLVM in obj directory: 
$setenv PATH /afs/glue/class/old/enee/759c/llvm/llvm-3.4-install/opt/bin/:$PATH
May need use $chmod 755 ${command} to register (following file should be put in obj/)
$runtest		(run test, generate output readable IR)#work for directory in Xiaomin Wu's Glue server, for different directory, Please change the file
$readex			(generate readable IR of input .bc file)#work for directory in Xiaomin Wu's Glue server
$checkresult		(show output readable IR and output .bc's .cpp generating file)
$clean 			(clean old generated files, automatically called by runtest)

short summary of the project:
The project is an optimization PASS in LLVM compiler. The PASS called Clonefunc is used to optimize the return efficiency of called functions. The optimization is done by cloning targeted functions and determine if they are returning a value or not. If function returns value, save the value to global variable and then use direct return method to make function return instead of taking return address from stack or register. If function returns void, just change the return method to direct return. Original functions of the cloned functions are kept unchanged, so that compiler can choose to make the program call the original function if it is faster than the modified clone function. The project can handles different styles of program written, including one function is called in multiple callsite, nested function calling, tail function call and so on. The output IR should have same functionality as the input IR but can run faster than the input IR since the indirect function return method has been changed to direct function return method.    
