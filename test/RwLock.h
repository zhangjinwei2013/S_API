#ifndef RWLOCK_H_
#define RWLOCK_H_

#include <apr_thread_rwlock.h>

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
	inline void lock(int lock_type);
	inline void unlock();
private:
	apr_thread_rwlock_t    *m_rwlock;
};

template<typename T>
class Loker
{
public:
	Loker(T &locker,int lock_type)
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