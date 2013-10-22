#ifndef RWLOCK_H_
#define RWLOCK_H_

#include <apr_thread_rwlock.h>
#include <apr_thread_mutex.h>

enum
{
	_wr = 0,
	    _rd,
	 _tryrd,
	 _trywr
};

class RwLock
{
public:	
	RwLock();
	~RwLock();
	apr_status_t create(apr_pool_t *mp);
	void destroy();
	inline void lock(int lock_type = _wr)
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
	inline void unlock()
	{
		apr_thread_rwlock_unlock(m_rwlock);
	}
private:
	apr_thread_rwlock_t    *m_rwlock;
};

class Mutex_
{
public:
	Mutex_();
	~Mutex_();
	apr_status_t create(apr_pool_t *mp);
	void destory();
	inline void lock();
protected:
private:
};
template<typename T>
class Loker
{
public:
	Loker(T &locker,int lock_type = _wr)
	{
		m_locker = &locker;
		locker->lock(lock_type);
	}
	~Loker()
	{
		m_locker->unlock();
	}
private:
	T *m_locker;
};

#endif