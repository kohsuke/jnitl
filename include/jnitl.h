// JNI template library
#pragma once

#include <crtdbg.h>

// if the following line fails, you have to add
// $JAVA_HOME/include and $JAVA_HOME/include/win32
// to your include directory.
#include <jni.h>

#include "jnitl_module.h"
#include "jnitl_array.h"
#include "jnitl_accessor.h"
#include "jnitl_op.h"
#include "jnitl_string.h"


// link appropriate library
#ifdef _DEBUG
	#ifdef _DLL
		#pragma comment(lib, "jnitld-dll.lib")
	#else
		#pragma comment(lib, "jnitld.lib")
	#endif
#else
	#ifdef _DLL
		#pragma comment(lib, "jnitl-dll.lib")
	#else
		#pragma comment(lib, "jnitl.lib")
	#endif
#endif