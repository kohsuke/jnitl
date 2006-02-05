#pragma once

namespace jnitl {

// auto-pointer that keeps a global reference
template <typename T/*something that derives from jobject*/>
class GlobalRef {
private:
	T obj;
	JNIEnv* env;

public:
	GlobalRef(JNIEnv* env, T obj) : obj((T)env->NewGlobalRef(obj)), env(env) {
	}
	~GlobalRef() {
		env->DeleteGlobalRef(obj);
		obj = NULL;
	}
	operator T () {
		return obj;
	}
};

}