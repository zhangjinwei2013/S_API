#ifndef LOCK_H_
#define LOCK_H_

#include <apr_general.h>
#include <apr_thread_mutex.h>
#include <apr_thread_rwlock.h>

enum
{
	wr_ = 0,
		rd_,
	 tryrd_,
	 trywr_
};

class RwLock_
{
public:
	RwLock_()
	{
		m_rwlock = NULL;
	}
	virtual ~RwLock_()
	{

	}
	inline apr_status_t create_(apr_pool_t *mp)
	{
		return apr_thread_rwlock_create(&m_rwlock,mp);
	}
	inline void destroy_()
	{
		if (m_rwlock)
		{
			apr_thread_rwlock_destroy(m_rwlock);
			m_rwlock = NULL;
		}
	}
	inline void lock_(int lockType = wr_)
	{
		switch(lockType)
		{
		case wr_:
			apr_thread_rwlock_wrlock(m_rwlock);
			break;
		case rd_:
			apr_thread_rwlock_rdlock(m_rwlock);
			break;
		case tryrd_:
			apr_thread_rwlock_tryrdlock(m_rwlock);
			break;
		case trywr_:
			apr_thread_rwlock_trywrlock(m_rwlock);
			break;
		}
	}
	inline void unlock_()
	{
		if (m_rwlock)
		{
			apr_thread_rwlock_unlock(m_rwlock);
			m_rwlock = NULL;
		}
	}
protected:
private:
	apr_thread_rwlock_t *m_rwlock;
};

class Mutex_
{
public:
	Mutex_()
	{
		m_mutex = NULL;
	}
	~Mutex_()
	{

	}
	inline apr_status_t crate_(apr_pool_t *mp)
	{
		return apr_thread_mutex_create(&m_mutex,APR_THREAD_MUTEX_UNNESTED,mp);
	}
	inline void destroy()
	{
		if (m_mutex)
		{
			apr_thread_mutex_destroy(m_mutex);
			m_mutex = NULL;
		}
	}
	inline void lock_(int lockType = wr_)
	{
		switch(lockType)
		{
		case wr_:
		case rd_:
			apr_thread_mutex_lock(m_mutex);
			break;
		case trywr_:
		case tryrd_:
			apr_thread_mutex_lock(m_mutex);
			break;
		}
	}
	inline void unlock_()
	{
		apr_thread_mutex_unlock(m_mutex);
	}
protected:
private:
	apr_thread_mutex_t *m_mutex;
};

template<typename T>
class Lock_
{
public:
	Lock_(T &lock,int lockType = wr_)
	{
		m_lock = lock;
		m_lock->lock_(lockType);
	}
	~Lock_()
	{
		m_lock->unlock_();
	}
protected:
private:
	T *m_lock;
};

#endif //LOCK_H_