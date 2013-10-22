// threadSync.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "lock.h"

apr_pool_t* mp;

int main(int argc, char* argv[])
{
	apr_initialize();
	apr_pool_create(&mp,NULL);
	apr_pool_destroy(mp);
	apr_terminate();
	return 0;
}

