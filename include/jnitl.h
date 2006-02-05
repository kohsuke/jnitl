// JNI template library
#pragma once

#ifdef _DEBUG
	#pragma comment(lib, "jnitld.lib")
#else
	#pragma comment(lib, "jnitl.lib")
#endif

#include "jnitl_module.h"
#include "jnitl_array.h"
#include "jnitl_accessor.h"
#include "jnitl_op.h"

namespace jnitl {
	// must be called to initialize JNITL
	void init(JNIEnv* env);
}