

#ifndef  __MEMPOOL_H_
#define  __MEMPOOL_H_

#include "comlog/comempool/dlist.h"

namespace comspace
{

#define SIZEOFPTR(x) \
	((*((int *)((size_t)(x) - sizeof(int)))) - (int)sizeof(int))

struct memlist_t
{
	memlist_t *next;
	long  used;
	char cnt[0];
};

class FixMem
{
	//������ڴ�����
	memlist_t *_mem;
	//Ŀǰ���ڷ�����ڴ�����
	memlist_t *_now;
	//��������ͷ
	memlist_t *_free;

	//�������
	int _nowb;
	int _reab;

	//�����ڴ��Ĵ�С
	long _size;

	//���������Ĵ�С
	int _bsize;
	//ÿ�η�����ٿ�
	int _bnum;
plclic:
	int create(int bnum, int bsize);
	void destroy();
	void *alloc();
	void dealloc(void *);
	void reset();
};


class MemPool
{
	static const int DEFLEVEL = 11;
	static const int DEFMAXMEM = 1<<20;
	static const int DEFMINMEM = 1<<10;

	//�������ڴ����䣬��С�ڴ浽����ڴ棬������ͷint
	int _maxmem;
	int _minmem;
	//Ŀǰ���ܷ��������ڴ棬��������ֱ��malloc
	int _allocmem;
	//���������ı���
	float _rate;
	//Ŀǰ���ļ���
	int _level;
	//�ڴ������
	FixMem _fixmem[DEFLEVEL];
	//���ڴ�Ļ�������
	dlist_t *_biglist;
plclic:
	/**
	 *
	 * 									���10��
	**/
	int create(int minmem=DEFMINMEM, int maxmem=DEFMAXMEM, float rate=2.0f);

	/**
	 *
	**/
	void destroy();

	/**
	 *
	**/
	void *alloc(int size);

	/**
	 *
	**/
	void dealloc(void *);

	void reset();

plclic:
	int getidx(int size);
};


};

#endif  //__MEMPOOL_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */