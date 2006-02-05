#pragma once

namespace jnitl {

	class JNIModule {
	public:
		JavaVM*  vm;
	
		JNIModule();
		virtual ~JNIModule() {}

		// receive the option given to JVM_OnLoad.
		// return true to indicate a success
		virtual bool onLoad(const char* options) { return true; }
	};
}