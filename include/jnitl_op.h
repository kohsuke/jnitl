#pragma once
//
//
// Helper classes to invoke JNI methods in a more type-safe manner.
//
//

namespace jnitl {
namespace op {

	// specialized for each return type.
	template <class JavaType>
	class Op {
	};

	// default implementation for Op
	template <class JT,
		JT (JNIEnv::* callMethod)( jobject, jmethodID, va_list ),
		JT (JNIEnv::* callStaticMethod)( jclass, jmethodID, va_list ),
		JT (JNIEnv::* getField)( jobject, jfieldID ),
		void (JNIEnv::* setField)( jobject, jfieldID, JT ),
		JT (JNIEnv::* getStaticField)( jclass, jfieldID ),
		void (JNIEnv::* setStaticField)( jclass, jfieldID, JT )
	>
	class Basic_Op {
	public:
		static JT invoke( JNIEnv* env, jobject o, jmethodID id, ... ) {
			va_list args;
			va_start(args,env);
			JT r = (env->*callMethod)(o,id,args);
			va_end(args);
			return r;
		}
		static JT invokeV( JNIEnv* env, jobject o, jmethodID id, va_list args ) {
			return (env->*callMethod)(o,id,args);
		}
		static JT invokeStaticV( JNIEnv* env, jclass clazz, jmethodID id, va_list args ) {
			return (env->*callStaticMethod)(clazz,id,args);
		}
	};

#define JNITL_DEF_OP(t,mt,ft) \
	template <> \
	class Op<t> : public Basic_Op<t, \
		&JNIEnv::Call##mt, \
		&JNIEnv::CallStatic##mt, \
		&JNIEnv::Get##ft, \
		&JNIEnv::Set##ft, \
		&JNIEnv::GetStatic##ft, \
		&JNIEnv::SetStatic##ft \
	> {};

	JNITL_DEF_OP(jboolean,BooleanMethodV,BooleanField)
	JNITL_DEF_OP(jint,IntMethodV,IntField)
	JNITL_DEF_OP(jshort,ShortMethodV,ShortField)
	JNITL_DEF_OP(jbyte,ByteMethodV,ByteField)
	JNITL_DEF_OP(jlong,LongMethodV,LongField)
	JNITL_DEF_OP(jfloat,FloatMethodV,FloatField)
	JNITL_DEF_OP(jdouble,DoubleMethodV,DoubleField)
	JNITL_DEF_OP(jobject,ObjectMethodV,ObjectField)

}
}