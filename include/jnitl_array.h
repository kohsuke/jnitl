#pragma once
#include "jnitl_accessor.h"
#include <string>
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
		static void unlock(JNIEnv* env,ARRAY a,const Component* buf) {
			int len = env->GetArrayLength(a);
			for( int i=0; i<len; i++ )
				env->SetObjectArrayElement(a,i,const_cast<Component*>(buf)[i]);
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
		static void unlock(JNIEnv* env,ARRAY a,const jboolean* buf) {
			env->ReleaseBooleanArrayElements(a,const_cast<jboolean*>(buf),0);
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
		static void unlock(JNIEnv* env,ARRAY a,const jbyte* buf) {
			env->ReleaseByteArrayElements(a,const_cast<jbyte*>(buf),0);
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
		static void unlock(JNIEnv* env,ARRAY a, const jchar* buf) {
			env->ReleaseCharArrayElements(a,const_cast<jchar*>(buf),0);
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
		static void unlock(JNIEnv* env,ARRAY a,const jshort* buf) {
			env->ReleaseShortArrayElements(a,const_cast<jshort*>(buf),0);
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
		static void unlock(JNIEnv* env,ARRAY a,const jint* buf) {
			env->ReleaseIntArrayElements(a,const_cast<jint*>(buf),0);
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
		static void unlock(JNIEnv* env,ARRAY a,const jlong* buf) {
			env->ReleaseLongArrayElements(a,const_cast<jlong*>(buf),0);
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
		static void unlock(JNIEnv* env,ARRAY a,const jfloat* buf) {
			env->ReleaseFloatArrayElements(a,const_cast<jfloat*>(buf),0);
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
		static void unlock(JNIEnv* env,ARRAY a,const jdouble* buf) {
			env->ReleaseDoubleArrayElements(a,const_cast<jdouble*>(buf),0);
		}
	};

	
	class ArrayND {
	public:
		typedef jobject Component;
		typedef jobjectArray ARRAY;
		
		static const int PREFETCHED_CLAZZES_NUM = 5;
		static JClassID clazzes[PREFETCHED_CLAZZES_NUM + 1];

		static ARRAY newArray(JNIEnv* env, jsize len, jsize dim) {
			return env->NewObjectArray(len, getClassForMultidimArray(env, dim - 1), NULL);
		}
		static Component* lock(JNIEnv* env,ARRAY a) {
			int len = env->GetArrayLength(a);
			Component* buf = new Component[len];
			for( int i=0; i<len; i++ )
				buf[i] = static_cast<Component>(env->GetObjectArrayElement(a,i));
			return buf;
		}
		static void unlock(JNIEnv* env,ARRAY a,const Component* buf) {
			int len = env->GetArrayLength(a);
			for( int i=0; i<len; i++ )
				env->SetObjectArrayElement(a,i,const_cast<Component*>(buf)[i]);
			delete[] buf;
		}

		static jclass getClassForMultidimArray(JNIEnv* env, size_t dim) {
			if(dim < PREFETCHED_CLAZZES_NUM) {
				return clazzes[dim];
			}
			else {
				std::string className("Ljava/lang/Object;");
				for (size_t i = 0; i < dim; i++)
					className.insert(0, "[");

				return env->FindClass(className.c_str());
			}
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