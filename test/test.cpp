// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <apr_pools.h>
#include "RwLock.h"
#include "pooltest.h"

apr_pool_t *g_mp;

int main(int argc, char* argv[])
{
	apr_initialize();
	apr_pool_create(&g_mp,NULL);
	apr_pool_destroy(g_mp);
	apr_terminate();
	return 0;
}

