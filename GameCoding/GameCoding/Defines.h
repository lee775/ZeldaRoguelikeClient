#pragma once

#define DECLARE_SINGLE(classname)				\
public:											\
static classname* GetInstance()					\
{												\
	if (s_instance == nullptr)					\
		s_instance = new classname();			\
												\
	return s_instance;							\
}												\
static void DestroyInstance()					\
{												\
	if (s_instance != nullptr)					\
		delete s_instance;						\
	s_instance = nullptr;						\
}												\
private:										\
	classname() {}								\
	static classname* s_instance;				\

#define GET_SINGLE(classname)	classname::GetInstance()
#define DESTROY_SINGLE(classname)	classname::DestroyInstance()

#define SAFE_DELETE(ptr)		\
if (ptr)						\
{								\
	delete ptr;					\
	ptr = nullptr;				\
}								