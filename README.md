# CRAP-Libs
## C RApid Programming Libraries

### What is this sh*t?
Some C-libraries that provide stuff like OOP or try-catch-constructions.

## Wait... OOP in C? You mean C++, right?
Nope. Thanks to structs and preprocessor macros I managed to create a Java-like object-oriented environment with classes, superclasses and even interfaces (although interfaces are merely shortcuts for declaring all methods in the interface by hand).

## Wow. Does that work on every system with every compiler?
Probably not. I used the GCC-specific function attributes and the pragma function to implement things like multiple catch blocks (I had to keep track of which classes are defined.) or interfaces which are not instance-able.

### So, how can I use this... thing?
## oop.h
Well, using (defined) classes is really easy:

```c
LinkedList_t list = new (LinkedList)();
list->add(list, "Hello World");
list->get(list, 0);
list->destruct(list);
```

The first parameter of every method call has to be the object itself. (Because the methods are basically function pointers which don't know where the original object is.)

Each object should be destructed if it's no longer used. (I am going to implement a basic garbage collector someday.)

Note the parentheses around the class name in the first line. I once had a version in which they were not necessary, but unfortunately there was something that prevented me from keeping that feature: C

(For interested fellows: The `construct(class)` macro has to be called in order to construct an object. This macro evaluates to the name of the construct method of that class. Furthermore each class defined a 0-ary macro with the name of the class (e.g. `LinkedList`) which evaluated to `construct(class)`. But that approach handicapped debugging, because on errors (and some warnings) the class name macro gets evaluated in contexts it should not, e.g. function arguments.)


Defining classes is a bit more tricky.

First the header file:
```c
// The following line registers the class.
extern class(TestClass, Object_class, (interfaces) {1 namely {Cloneable_class} }, true) {
	// The name of the class is TestClass, it extends Object_class 
	// and has one interface (Cloneable_class).
	// The last parameter (true) indicates that this class is instanceable.

	// Now let's define the datastructure.
	// First (!) we need the super-object.
	extends(Object_t);

	// Next we add the definitions from the interface.
	implements(Cloneable);

	// At last the fields and methods of the class itself:

	const char* string;

	void (*set)(defclass TestClass*, const char* string);
	const char* (*get)(defclass TestClass*);

	void (*destruct)(defclass TestClass*);
}

// The following methods need to be "static":

// the constructor
TestClass_t* method(TestClass, construct)(void);

// the populate method (see source file)
void method(TestClass, populate)(TestClass_t*, class_t);
```

The source file:
```c
// The class itself should be defined in the source file. 
// This is why in the header file the class is defined extern.
class_t TestClass_class;

// Let's define the constructor.
TestClass_t* method(TestClass, construct)(void) {
	throws(OutOfMemoryException_t);
	// This method might throw a exception. See above.


	// We now have to allocate the memory for the object.
	// On how this works: See later (try.h).
	sr_(TestClass_t* test = allocate_object(TestClass), NULL);
	
	// Call populate of TestClass on the object.
	populate(TestClass)(test, TestClass_class);

	return test;
}

// The clone method inherited from Cloneable.
// You might have to look up the interface definitions.
void* method(TestClass, clone)(void* this) {
	throws(IllegalArgumentException_t, NullPointerException_t, OutOfMemoryException_t);

	// Check for NULL.
	if (this == NULL) {
		throwr(new (NullPointerException)(), NULL);
	}

	// Check for class type.
	// This will not fail if `this` is an object of an child class of TestClass.
	if (!instanceof(this, TestClass_class)) {
		throwr(new (IllegalArgumentException)("Argument is not of type TestClass."), NULL)
	}

	TestClass_t* test = (TestClass_t*) this;

	sr_(TestClass_t* clone = new (TestClass)(), NULL);
	
	clone->string = test->string;

	return clone;
}

// The following two methods are trivial.
void method(TestClass, set)(TestClass_t* this, const char* string) {
	throws(NullPointerException_t);

	if (this == NULL) {
		throw(new (NullPointerException)());
	}

	this->string = string;
}
const char* method(TestClass, get)(TestClass_t* this) {
	throws(NullPointerException_t);

	if (this == NULL) {
		throw(new (NullPointerException)());
	}

	return this->string;
}

// The destructor:
void method(TestClass, destruct)(TestClass_t* this) {
	throws(NullPointerException_t);

	if (this == NULL) {
		throw(new (NullPointerException)());
	}

	// We don't have anything to destruct.

	// Call super destructor.
	this->super.destruct((Object_t*) this);
}

// Now the interesting part: The populate method.
void method(TestClass, populate)(TestClass_t* obj, class_t c) {
	// This method basically does the setup of the object.

	// First of all we have to populate the super object.
	// (In this case of type Object_t)
	populate(Object)((Object_t*) obj, c);

	// Let's set up all fields and methods.

	obj->string = NULL;

	add_method(obj, TestClass, destruct);
	add_method(obj, TestClass, clone);
	add_method(obj, TestClass, set);
	add_method(obj, TestClass, get);

	// Done.
}
```

TODO: the remaining 90 % of the readme (Don't judge me, it's half past 1 am and I have to get up early tomorrow.)
