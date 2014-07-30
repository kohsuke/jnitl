#pragma once
#include "jnitl_accessor.h"
//
//
// Type definitions that allow polymorhpic operations to Java arrays.
//
//

namespace jnitl {
namespace array {

	template <class Type>
	struct JClass {};

	template <>
	struct JClass<jobject> {
		static JClassID clazz;
	};

	template <>
	struct JClass<jstring> {
		static JClassID clazz;
	};

	__declspec( selectany )
	JClassID JClass<jstring>::clazz("java/lang/String");


	template <class Component>
	// for reference types like jobject or jstring. for primitive arrays, see the specializations later.
	class Array {
	public:
		typedef jobjectArray ARRAY;
		static ARRAY newArray(JNIEnv* env,jsize len) {
			return env->NewObjectArray(len,JClass<Component>::clazz,NULL);
		}
		static Component* lock(JNIEnv* env,ARRAY a) {
			int len = env->GetArrayLength(a);
			Component* buf = new Component[len];
			for( int i=0; i<len; i++ )
				buf[i] = static_cast<Component>(env->GetObjectArrayElement(a,i));
			return buf;
		}
		static void unlock(JNIEnv* env,ARRAY a,Component* buf) {
			int len = env->GetArrayLength(a);
			for( int i=0; i<len; i++ )
				env->SetObjectArrayElement(a,i,buf[i]);
			delete[] buf;
		}
	};

	template<>
	class Array<jboolean> {
	public:
		typedef jbooleanArray ARRAY;
		static ARRAY newArray(JNIEnv* env,jsize len) {
			return env->NewBooleanArray(len);
		}
		static jboolean* lock(JNIEnv* env,ARRAY a) {
			return env->GetBooleanArrayElements(a,NULL);
		}
		static void unlock(JNIEnv* env,ARRAY a,jboolean* buf) {
			env->ReleaseBooleanArrayElements(a,buf,0);
		}
	};

	template<>
	class Array<jbyte> {
	public:
		typedef jbyteArray ARRAY;
		static ARRAY newArray(JNIEnv* env,jsize len) {
			return env->NewByteArray(len);
		}
		static jbyte* lock(JNIEnv* env,ARRAY a) {
			return env->GetByteArrayElements(a,NULL);
		}
		static void unlock(JNIEnv* env,ARRAY a,jbyte* buf) {
			env->ReleaseByteArrayElements(a,buf,0);
		}
	};

	template<>
	class Array<jchar> {
	public:
		typedef jcharArray ARRAY;
		static ARRAY newArray(JNIEnv* env,jsize len) {
			return env->NewCharArray(len);
		}
		static jchar* lock(JNIEnv* env,ARRAY a) {
			return env->GetCharArrayElements(a,NULL);
		}
		static void unlock(JNIEnv* env,ARRAY a,jchar* buf) {
			env->ReleaseCharArrayElements(a,buf,0);
		}
	};

	template<>
	class Array<jshort> {
	public:
		typedef jshortArray ARRAY;
		static ARRAY newArray(JNIEnv* env,jsize len) {
			return env->NewShortArray(len);
		}
		static jshort* lock(JNIEnv* env,ARRAY a) {
			return env->GetShortArrayElements(a,NULL);
		}
		static void unlock(JNIEnv* env,ARRAY a,jshort* buf) {
			env->ReleaseShortArrayElements(a,buf,0);
		}
	};

	template<>
	class Array<jint> {
	public:
		typedef jintArray ARRAY;
		static ARRAY newArray(JNIEnv* env,jsize len) {
			return env->NewIntArray(len);
		}
		static jint* lock(JNIEnv* env,ARRAY a) {
			return env->GetIntArrayElements(a,NULL);
		}
		static void unlock(JNIEnv* env,ARRAY a,jint* buf) {
			env->ReleaseIntArrayElements(a,buf,0);
		}
	};

	template<>
	class Array<jlong> {
	public:
		typedef jlongArray ARRAY;
		static ARRAY newArray(JNIEnv* env,jsize len) {
			return env->NewLongArray(len);
		}
		static jlong* lock(JNIEnv* env,ARRAY a) {
			return env->GetLongArrayElements(a,NULL);
		}
		static void unlock(JNIEnv* env,ARRAY a,jlong* buf) {
			env->ReleaseLongArrayElements(a,buf,0);
		}
	};

	template<>
	class Array<jfloat> {
	public:
		typedef jfloatArray ARRAY;
		static ARRAY newArray(JNIEnv* env,jsize len) {
			return env->NewFloatArray(len);
		}
		static jfloat* lock(JNIEnv* env,ARRAY a) {
			return env->GetFloatArrayElements(a,NULL);
		}
		static void unlock(JNIEnv* env,ARRAY a,jfloat* buf) {
			env->ReleaseFloatArrayElements(a,buf,0);
		}
	};

	template<>
	class Array<jdouble> {
	public:
		typedef jdoubleArray ARRAY;
		static ARRAY newArray(JNIEnv* env,jsize len) {
			return env->NewDoubleArray(len);
		}
		static jdouble* lock(JNIEnv* env,ARRAY a) {
			return env->GetDoubleArrayElements(a,NULL);
		}
		static void unlock(JNIEnv* env,ARRAY a,jdouble* buf) {
			env->ReleaseDoubleArrayElements(a,buf,0);
		}
	};


}

// lock array on the initialization, unlock it on the deinitialization,
// and provide convenient access.
template<class Component>
class LockedArray {
private:
	// the type of the whole array
	typedef typename array::Array<Component>::ARRAY ARRAY;
	// pointer to the top of the array item
	Component* p;

	ARRAY ar;
	JNIEnv* const pEnv;
public:
	LockedArray( JNIEnv* pEnv, ARRAY ar ) : pEnv(pEnv), ar(ar) {
		p = array::Array<Component>::lock(pEnv,ar);
	}

	~LockedArray() {
		array::Array<Component>::unlock(pEnv,ar,p);
	}

	// access the top of the array
	operator Component* () const {
		return p;
	}

	// access individual item on the array
	Component& operator [] (int idx) const {
		return p[idx];
	}
};


}
