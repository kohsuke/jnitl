// stdafx.cpp : source file that includes just the standard includes
// jnitl.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "../include/jnitl_module.h"
#include "../include/jnitl_accessor.h"

namespace jnitl {

JNIModule* pModule;

JNIModule::JNIModule() {
	if(pModule==NULL) {
		_RPT0(_CRT_ASSERT,"More than one JNIModule instances are defined");
	}
	pModule = this;
}


extern "C"
JNIEXPORT jint JNICALL JVM_OnLoad(JavaVM* _jvm, const char* options, void* reserved) {
	if(pModule!=NULL) {
		return pModule->onLoad(options) ? JNI_OK : JNI_ERR;
	} else {
		_RPT0(_CRT_WARN,"No JNIModule is defined");
		return JNI_OK;
	}
}


void init(JNIEnv* env) {
	JClassID::runInit(env);
	JMethodID_Base::runInit(env);
	JFieldID_Base::runInit(env);
}

}