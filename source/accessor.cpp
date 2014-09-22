#include "stdafx.h"
#include "../include/jnitl_accessor.h"
#include "../include/jnitl_array.h"

namespace jnitl {

JClassID* JClassID::init = NULL;
JMethodID_Base* JMethodID_Base::init = NULL;
JFieldID_Base* JFieldID_Base::init = NULL;


JClassID javaLangNumber("java/lang/Number");
JMethodID<jbyte> javaLangNumber_byteValue(javaLangNumber,"byteValue","()B");
JMethodID<jint> javaLangNumber_intValue(javaLangNumber,"intValue","()I");
JMethodID<jfloat> javaLangNumber_floatValue(javaLangNumber,"floatValue","()F");
JMethodID<jdouble> javaLangNumber_doubleValue(javaLangNumber,"doubleValue","()D");
JMethodID<jshort> javaLangNumber_shortValue(javaLangNumber,"shortValue","()S");
JMethodID<jlong> javaLangNumber_longValue(javaLangNumber,"longValue","()J");

JClassID javaLangInteger("java/lang/Integer");
JStaticMethodID<jobject> javaLangInteger_valueOf(javaLangInteger,"valueOf","(I)Ljava/lang/Integer;");

JClassID javaLangShort("java/lang/Short");
JStaticMethodID<jobject> javaLangShort_valueOf(javaLangShort,"valueOf","(S)Ljava/lang/Short;");

JClassID javaLangLong("java/lang/Long");
JStaticMethodID<jobject> javaLangLong_valueOf(javaLangLong,"valueOf","(J)Ljava/lang/Long;");

JClassID javaLangFloat("java/lang/Float");
JStaticMethodID<jobject> javaLangFloat_valueOf(javaLangFloat,"valueOf","(F)Ljava/lang/Float;");

JClassID javaLangDouble("java/lang/Double");
JStaticMethodID<jobject> javaLangDouble_valueOf(javaLangDouble,"valueOf","(D)Ljava/lang/Double;");

JClassID javaLangByte("java/lang/Byte");
JStaticMethodID<jobject> javaLangByte_valueOf(javaLangByte,"valueOf","(B)Ljava/lang/Byte;");

JClassID javaLangBoolean("java/lang/Boolean");
JMethodID<jboolean> javaLangBoolean_booleanValue(javaLangBoolean,"booleanValue","()Z");
JStaticMethodID<jobject> javaLangBoolean_valueOf(javaLangBoolean,"valueOf","(Z)Ljava/lang/Boolean;");

JClassID javaLangCharacter("java/lang/Character");
JMethodID<jchar> javaLangCharacter_charValue(javaLangCharacter,"charValue","()C");
JStaticMethodID<jobject> javaLangCharacter_valueOf(javaLangCharacter,"valueOf","(C)Ljava/lang/Character;");

JClassID javaLangString("java/lang/String");

JClassID booleanArray("[Z");
JClassID byteArray("[B");
JClassID charArray("[C");
JClassID doubleArray("[D");
JClassID floatArray("[F");
JClassID intArray("[I");
JClassID longArray("[J");
JClassID shortArray("[S");
JClassID stringArray("[Ljava/lang/String;");
JClassID objectArray("[Ljava/lang/Object;");


JClassID array::JClass<jobject>::clazz("java/lang/Object");


JClassID array::ArrayND::clazzes[array::ArrayND::PREFETCHED_CLAZZES_NUM + 1] = {
	JClassID("Ljava/lang/Object;"),
	JClassID("[Ljava/lang/Object;"),
	JClassID("[[Ljava/lang/Object;"),
	JClassID("[[[Ljava/lang/Object;"),
	JClassID("[[[[Ljava/lang/Object;"),
	JClassID("[[[[[Ljava/lang/Object;")
};


}