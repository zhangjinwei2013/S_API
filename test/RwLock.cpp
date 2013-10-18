#include "StdAfx.h"
#include "RwLock.h"

RwLock::RwLock()
{
	m_rwlock = NULL;
}

RwLock::~RwLock()
{
	
}

apr_status_t RwLock::create(apr_pool_t *mp)
{
	return apr_thread_rwlock_create(&m_rwlock,mp);
}

void RwLock::destroy()
{
	if (m_rwlock)
	{
		apr_thread_rwlock_destroy(m_rwlock);
		m_rwlock = NULL;
	}
}
