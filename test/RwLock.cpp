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

void RwLock::lock(int lock_type)
{
	switch(lock_type)
	{
	case _wr:
		apr_thread_rwlock_wrlock(m_rwlock);
		break;
	case _rd:
		apr_thread_rwlock_rdlock(m_rwlock);
		break;
	case _tryrd:
		apr_thread_rwlock_tryrdlock(m_rwlock);
		break;
	case _trywr:
		apr_thread_rwlock_trywrlock(m_rwlock);
		break;
	}
}

void RwLock::unlock()
{
	apr_thread_rwlock_unlock(m_rwlock);
}
