#pragma once

namespace jnitl {

// Attach the current thread on initialization,
// and detacth it on de-initializatio
class AttachThread {
private:
	JNIModule const& module;
	JNIEnv* pEnv;
public:
	AttachThread(JNIModule& module) : module(module) {
		pEnv = NULL;
		module.vm->AttachCurrentThread(reinterpret_cast<void**>(&pEnv),NULL);
	}

	~AttachThread() {
		pEnv = NULL;
		module.vm->DetachCurrentThread();
	}

	operator JNIEnv* const () {
		_ASSERT(pEnv!=NULL);
		return pEnv;
	}
};

}