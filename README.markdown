JNITL - Java Native Interface Template Library
================

[JNI](http://java.sun.com/j2se/1.5.0/docs/guide/jni/index.html) is the programming interface when developing native libraries that work with Java. Unfortunately, this interface is designed to be compatible with C, and therefore it cannot take advantage of C++ language features.

This project aims to bridge this gap by providing a C++ layer on top of JNI, and making it a lot easier to use.

Features
--------
The current version has the following features:

- Method/field access regrouped by types (so that they can be driven by other templates more easily)
- Array access regrouped by types (so that they can be driven by other templates more easily)
- Convenient method/field invocations that hide method/field IDs.
- Convenient `java.lang.String` <-> LPCSTR/LPCWSTR conversion

TODOs
-----

This library can be extended in many ways, and here are some ideas. Volunteers are welcome.

- Support more platforms
- Write a little Java tool that reads a class definition and generates a wrapper C++ code that access it through JNITL, so that you can write as follows:

        // assume you've translated java.io.File to Java::Io::File
        void foo(jobject o) {
          Java::Io::File pFile = static_cast&lt;Java::Io::File>(o);
          pFile = pFile->getAbsoluteFile();
          jboolean exists = pFile->exists();
          if(exists) {
            ...
          }
        }

Unlike a Java library, where every unsed feature still bloats the application using it, C++ applications only pay for the features they actually use. So that allows us to add more features without worrying too much about the size bloat.


Usage
-----

To use JNITL, first check out the code and extract it somewhere. Then configure your C++ compiler and linker so that <tt>jnitl/include</tt> and <tt>jnitl/lib</tt> are searched by the compiler and the linker respectively.

From your program, do the following:

    // in your stdafx.h header file
    #include &lt;jnitl.h>
    using namespace jnitl;	// if you want to.

    extern JNIModule module;

    // in your stdafx.cpp file
    JNIModule module;


Customers
-----
This project is used by:

- [com4j](http://github.com/kohsuke/com4j/)
- [nlink](https://nlink.dev.ajva.net/)

(File a ticket to be listed here)
</body>
</html>
