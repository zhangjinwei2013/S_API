#ifndef POOLTEST_H_
#define POOLTEST_H_
#include "apr_general.h"
#include "apr_thread_mutex.h"
#include "apr_thread_rwlock.h"

class A
{
public:
	A(apr_pool_t *mp)
	{
		apr_pool_create(&mp_a,mp);
		apr_thread_rwlock_create(&rwlock_,mp_a);
	}
	~A()
	{
		if (rwlock_)
		{
			apr_thread_rwlock_destroy(rwlock_);
			if (mp_a)
			{
				apr_pool_destroy(mp_a);
			}
		}
	}
protected:
private:
	apr_thread_rwlock_t *rwlock_;
	apr_pool_t *mp_a;
};

class B
{
public:
	B(apr_pool_t *mp)
	{
		apr_pool_create(&mp_b,mp);
		apr_thread_mutex_create(&mutex_,0,mp_b);
	}
	~B()
	{
		if (mutex_)
		{
			apr_thread_mutex_destroy(mutex_);
			if (mp_b)
			{
				apr_pool_destroy(mp_b);
			}
		}
	}
protected:
private:
	apr_thread_mutex_t *mutex_;
	apr_pool_t         *mp_b;
};
#endif