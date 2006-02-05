// stdafx.cpp : source file that includes just the standard includes
// jnitl.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "../include/jnitl_module.h"
#include "../include/jnitl_accessor.h"

namespace jnitl {

JNIModule* pModule;

JNIModule::JNIModule() {
	if(pModule!=NULL) {
		_RPT0(_CRT_ASSERT,"More than one JNIModule instances are defined");
	}
	pModule = this;
}


extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* _jvm, void* reserved) {
	JNIEnv* env = NULL;

	if(_jvm->GetEnv((void**)&env,JNI_VERSION_1_2)==JNI_OK) {
		_ASSERT(env!=NULL);
		jnitl_init(env);
	} else {
		_RPT0(_CRT_ASSERT,"Unable to obtain JNIEnv");
	}
	
	if(pModule!=NULL) {
		return pModule->onLoad();
	} else {
		_RPT0(_CRT_WARN,"No JNIModule is defined");
		return JNI_VERSION_1_2;
	}
}

extern "C"
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* _jvm, void* reserved) {
	if(pModule!=NULL) {
		return pModule->onUnload();
	}
}

void jnitl_init(JNIEnv* env) {
	JClassID::runInit(env);
	JMethodID_Base::runInit(env);
	JFieldID_Base::runInit(env);
}

}