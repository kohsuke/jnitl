#pragma once

namespace jnitl {

	class JNIModule {
	public:
		JavaVM*  vm;
	
		JNIModule();
		virtual ~JNIModule() {}

		// called when the library is loaded into the JVM
		virtual jint onLoad() { return JNI_VERSION_1_2; }

		// called when the library is unloaded
		virtual void onUnload() {}
	};
}