//--------------------------------------------------------------------------------------------------------------------------------
#include "mdll.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MDll,MObject)

END_LMYUNIT
//................................................................................................................................
MDll::MDll(void)
{
#ifdef WINDOWSCODE

	m_DllHandle = NULL;

#else
	
	m_DllHandle = NULL;
	
#endif
}
//................................................................................................................................
MDll::~MDll()
{
	CloseDll();
}
//................................................................................................................................
int  MDll::LoadDll(MString DllPath)
{
	CloseDll();

#ifdef WINDOWSCODE

	m_DllHandle = LoadLibrary(DllPath.c_str());
	if ( m_DllHandle == NULL )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}

	return(1);
#else

	m_DllHandle = dlopen(DllPath.c_str(),RTLD_NOW);
	if ( m_DllHandle == NULL )
	{
		printf("µ÷ÓÃDLLÊ§°Ü£º%s\r\n",dlerror());
		return(ERROR_SYSTEM(GetLastError()));	
	}
	
	return(1);

#endif
}
//................................................................................................................................
void * MDll::GetDllFunction(MString FunctionName)
{
#ifdef WINDOWSCODE

	assert(m_DllHandle != NULL);
	return(::GetProcAddress(m_DllHandle,FunctionName.c_str()));

#else
	
	assert(m_DllHandle != NULL);
	return(dlsym(m_DllHandle,FunctionName.c_str()));

#endif
}
//................................................................................................................................
void MDll::CloseDll(void)
{
#ifdef WINDOWSCODE

	if ( m_DllHandle != NULL )
	{
		::FreeLibrary(m_DllHandle);
		m_DllHandle = NULL;
	}

#else
	
	if ( m_DllHandle != NULL )
	{
		dlclose(m_DllHandle);
		m_DllHandle = NULL;
	}

#endif
}
//--------------------------------------------------------------------------------------------------------------------------------
