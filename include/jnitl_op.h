#pragma once
/*
	Helper classes to invoke JNI methods in a more type-safe manner.

	The goal is to define Op<T>, where T is both primitives and references,
	that hides difference in the JNI method names. For example, in JNI, calling
	a method that returns a boolean is BooleanMethodV, while calling a method
	that returns int is IntMethodV. We turn that into Op<boolean>::invokeV and
	Op<int>::invokeV. This serves as the basic building block for further type
	parameterization.

	We define five static methods invoke/invokeV/invokeStaticV/getField/setField.
	See Basic_Op for the signature of those 5 methods.
*/

namespace jnitl {
namespace op {

	// default implementation for Op
	template <class JT, class RT,
		RT (JNIEnv::* callMethod)( jobject, jmethodID, va_list ),
		RT (JNIEnv::* callStaticMethod)( jclass, jmethodID, va_list ),
		RT (JNIEnv::* getF)( jobject, jfieldID ),
		void (JNIEnv::* setF)( jobject, jfieldID, RT ),
		RT (JNIEnv::* getStaticField)( jclass, jfieldID ),
		void (JNIEnv::* setStaticField)( jclass, jfieldID, RT )
	>
	class Basic_Op {
	public:
		static JT invoke( JNIEnv* env, jobject o, jmethodID id, ... ) {
			va_list args;
			va_start(args,env);
			JT r = static_cast<JT>((env->*callMethod)(o,id,args));
			va_end(args);
			return r;
		}
		static JT invokeV( JNIEnv* env, jobject o, jmethodID id, va_list args ) {
			return static_cast<JT>((env->*callMethod)(o,id,args));
		}
		static JT invokeStaticV( JNIEnv* env, jclass clazz, jmethodID id, va_list args ) {
			return static_cast<JT>((env->*callStaticMethod)(clazz,id,args));
		}
		static JT getField( JNIEnv* env, jobject o, jfieldID id ) {
			return static_cast<JT>((env->*getF)(o,id));
		}
		static void setField( JNIEnv* env, jobject o, jfieldID id, RT value ) {
			(env->*setF)(o,id,value);
		}
	};

#define JNITL_DEF_OP_LIST(mt,ft) \
	&JNIEnv::Call##mt, \
	&JNIEnv::CallStatic##mt, \
	&JNIEnv::Get##ft, \
	&JNIEnv::Set##ft, \
	&JNIEnv::GetStatic##ft, \
	&JNIEnv::SetStatic##ft

#define JNITL_DEF_OP(t,mt,ft) \
	template <> \
	class Op<t> : public Basic_Op<t,t, \
		JNITL_DEF_OP_LIST(mt,ft) \
	> {};


	// it defaults to jobject
	template<typename T>
	class Op : public Basic_Op<T, jobject, JNITL_DEF_OP_LIST(ObjectMethodV,ObjectField)> {};

	// specialization for primitives
	JNITL_DEF_OP(jboolean,BooleanMethodV,BooleanField)
	JNITL_DEF_OP(jint,IntMethodV,IntField)
	JNITL_DEF_OP(jshort,ShortMethodV,ShortField)
	JNITL_DEF_OP(jbyte,ByteMethodV,ByteField)
	JNITL_DEF_OP(jlong,LongMethodV,LongField)
	JNITL_DEF_OP(jfloat,FloatMethodV,FloatField)
	JNITL_DEF_OP(jdouble,DoubleMethodV,DoubleField)
	JNITL_DEF_OP(jchar,CharMethodV,CharField)

	// void requires a specialization because there's no void field.
	template <>
	class Op<void> {
	public:
		static void invoke( JNIEnv* env, jobject o, jmethodID id, ... ) {
			va_list args;
			va_start(args,env);
			env->CallVoidMethodV(o,id,args);
			va_end(args);
		}
		static void invokeV( JNIEnv* env, jobject o, jmethodID id, va_list args ) {
			env->CallVoidMethodV(o,id,args);
		}
		static void invokeStaticV( JNIEnv* env, jclass clazz, jmethodID id, va_list args ) {
			env->CallStaticVoidMethodV(clazz,id,args);
		}
	};
}
}