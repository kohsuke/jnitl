#pragma once

namespace jnitl {

// auto-pointer that keeps a global reference
template <typename T/*something that derives from jobject*/>
class GlobalRef {
private:
	T obj;
	JNIEnv* env;

public:
	GlobalRef(JNIEnv* env, T obj) : obj(NULL), env(NULL) {
		Attach(env,obj);
	}
	GlobalRef() : obj(NULL),env(NULL) {}
	~GlobalRef() {
		Detach();
	}
	void Attach(JNIEnv* _env, T _obj) {
		Detach();
		env = _env;
		obj = env->NewGlobalRef(_obj);
	}
	void Detach() {
		if(obj!=NULL) {
			env->DeleteGlobalRef(obj);
			obj = NULL;
		}
	}
	operator T () {
		return obj;
	}
};

}