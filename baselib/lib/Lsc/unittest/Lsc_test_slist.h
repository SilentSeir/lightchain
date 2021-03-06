// Lsc_slist.cpp : 定义控制台应用程序的入口点。
//


#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include <Lsc/archive/Lsc_serialization.h>
#include <Lsc/archive/Lsc_filestream.h>
#include <Lsc/archive/Lsc_binarchive.h>
#include <Lsc/containers/slist/Lsc_slist.h>
#include <Lsc/containers/string/Lsc_string.h>

#define ERROR() printf("error%d\n", __LINE__)
#include <string>
#if 0
template<typename T>
int test_iterate(Lsc::slist<T> list)
{
	int v=0;
	for(list.iterator i=list.begin(); i!=list.end(); ++i)
	{
		if( *i != v)
			ERROR();
		v++;
	}
}
#endif
//template<typename T>

#include <cxxtest/TestSuite.h>
class p
{
plclic:
	bool operator()(int q)
	{
		return q==50; 
	}
};
class Lsc_test_slist : plclic CxxTest::TestSuite
{
	plclic:

    void test_operator()
    {
        typedef Lsc::slist<int>::iterator Iter;
        {
            {
                Lsc::slist<int> l1;
                Lsc::slist<int> l2;
                l1.create();
                l2.create();
                TS_ASSERT(0 == l1.size());
                TS_ASSERT(0 == l2.size());
                TS_ASSERT( 0 != l1.erase_after( l1.begin() ) );
                TS_ASSERT( l1.begin() == l1.end() );
                TS_ASSERT( l2.begin() == l2.end() );
            }
            {  
                Lsc::slist<int> l1;
                Lsc::slist<int> l2;
                for (int i = 0; i < 5; i ++) {
                    l1.push_front(i);
                }
                TS_ASSERT( 5 == l1.size() );

                for (int i = 0; i < 60; i ++) {
                    l2.push_front(i);
                }
                TS_ASSERT( 60 == l2.size() );

                Iter f1,f2;
                f1 = l1.begin();
                f2 = l2.begin();
                
                for (size_t i = 1; i < l1.size(); i ++) {
                    f1 ++;
                    f2 ++;
                }
                Iter tmp = f1;
                f2 ++;
                while (f2 != l2.end()) {
                    l1.insert_after( f1, *f2 );
                    f1 ++;
                    f2 ++;
                }
                TS_ASSERT(60 == l1.size());
                TS_ASSERT(60 == l2.size());
                
                l1.erase_after( tmp, l1.end() );
                TS_ASSERT(5 == l1.size());
                int i = 4;
                for (Iter iter = l1.begin(); iter != l1.end(); ++ iter) {
                    TS_ASSERT( i == *iter );
                    i --;
                }
            }
            {  
                Lsc::slist<int> l1;
                Lsc::slist<int> l2;
                for (int i = 0; i < 5; i ++) {
                    l1.push_front(i);
                }

                for (int i = 0; i < 60; i ++) {
                    l2.push_front(i);
                }
                TS_ASSERT( 60 == l2.size() );
                l2 = l1;
                TS_ASSERT( 5 == l2.size() );

                TS_ASSERT( l2.size() == l1.size() );
                Iter iter1,iter2;
                for (iter1 = l1.begin(), iter2 = l2.begin(); iter1 != l1.end() && iter2 != l2.end(); ++ iter1, ++ iter2) {
                    TS_ASSERT( *iter1 == *iter2);
                }
            }
            {  
                Lsc::slist<int> l1;
                Lsc::slist<int> l2;
                for (int i = 0; i < 5; i ++) {
                    l1.push_front(i);
                }

                for (int i = 0; i < 60; i ++) {
                    l2.push_front(i);
                }
                l1 = l2;
                TS_ASSERT( l2.size() == l1.size() );
                Iter iter1,iter2;
                for (iter1 = l1.begin(), iter2 = l2.begin(); iter1 != l1.end() && iter2 != l2.end(); ++ iter1, ++ iter2) {
                    TS_ASSERT( *iter1 == *iter2);
                }
            }
            {  
                Lsc::slist<int> l1;
                for (int i = 0; i < 5; i ++) {
                    l1.push_front(i);
                }
                TS_ASSERT( 5 == l1.size() );
                Lsc::slist<int> l2(l1);
                TS_ASSERT( l1.size() == l2.size() );
                Iter iter1,iter2;
                for (iter1 = l1.begin(), iter2 = l2.begin(); iter1 != l1.end() && iter2 != l2.end(); ++ iter1, ++ iter2) {
                    TS_ASSERT( *iter1 == *iter2 );
                }
            }
            {
                Lsc::slist<int> t1;
                for (int i = 0; i < 100; i ++) {
                    t1.push_front(i);
                }
                TS_ASSERT(100 == t1.size());
                Lsc::slist<int> t2;
                t2 = t1;
                TS_ASSERT( 100 == t2.size() );
                int i = 99;
                for (Lsc::slist<int>::iterator Iter = t2.begin(); Iter != t2.end(); ++ Iter) {
                    TS_ASSERT( *Iter == i -- );
                }
                i = 99;
                t1 = t1;
                TS_ASSERT( 100 == t1.size() );
                for (Lsc::slist<int>::iterator Iter = t1.begin(); Iter != t1.end(); ++ Iter) {
                    TS_ASSERT( *Iter == i -- );
                }
                Lsc::slist<int> t3;
                t3.push_front(1);
                TS_ASSERT( 1 == *t3.begin() );
                TS_ASSERT(1 == t3.size());
                Lsc::slist<int> t5;
                Lsc::slist<int> t4;
                t4 = t3;
                TS_ASSERT(0 == t5.size());
                TS_ASSERT(1 == t4.size());
                t3.pop_front();
                t3 = t5;
                TS_ASSERT( 0 == t3.size() );
                t1 = t3;
                TS_ASSERT( 0 == t1.size() );
                TS_ASSERT( 0 == t3.size() );
            } 
        }
        {
            Lsc::slist<Lsc::string> l1;
            Lsc::slist<Lsc::string> l2;
            for (int i = 0; i < 1000; i ++) {
                l1.push_front( "hello world" );
            }
            TS_ASSERT(1000 == l1.size());
            for (int i = 0; i < 100; i ++) {
                l2 = l1;
            }
            TS_ASSERT(1000 == l1.size());
            TS_ASSERT(1000 == l2.size());
        }
    }
    void test_create()
    {
        Lsc::slist<int> l1;
        int i;
        for (i = 0; i < 10000; i ++) {
            l1.create();
        }
        for (i = 0; i < 10000; i ++) {
            l1.create();
        }
        Lsc::slist<int> l2;
        for (i = 0; i < 10000; i ++) {
            l2.create();
        }
        TS_ASSERT(0 == l1.size());
        TS_ASSERT(0 == l2.size());
        for (i = 0; i < 100; i ++) {
            l2.push_front(i);
        }
        TS_ASSERT( 100 == l2.size() );
    }
	void test_string()
	{
		Lsc::slist<std::string> t1;
		TS_ASSERT(!t1.create());
		TS_ASSERT(!t1.push_front(std::string("123")));
		TS_ASSERT(!t1.push_front(std::string("abc")));
		TS_ASSERT(!t1.push_front(std::string("ABC")));
        TS_ASSERT(3 == t1.size());
		TS_ASSERT(!t1.destroy());
	}
	void test_push_front()
	{
		Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());
        TS_ASSERT(0 == t1.size());
		for(int i=0; i<100; i++)
		{
			TS_ASSERT(!t1.push_front(i));
		}
        TS_ASSERT(100 == t1.size());
		int v = 99;
		for(Lsc::slist<int>::iterator i = t1.begin(); i != t1.end(); i++)
		{
			TS_ASSERT_EQUALS(*i, v);
			v--;
		}
		TS_ASSERT(!t1.destroy());
	}
	void test_assign()
	{
		Lsc::slist<int> t1, t2;
		TS_ASSERT(!t1.create());
		for (int i=0; i<100; i++)
		{
			TS_ASSERT(!t1.push_front(i));
		}
        TS_ASSERT(100 == t1.size());
		TS_ASSERT(!t2.create());
		t2.assign(t1.begin(), t1.end());
        TS_ASSERT(100 == t2.size());
		int v = 99;
		for(Lsc::slist<int>::iterator i1 = t2.begin(); i1!=t2.end(); ++i1)
		{
			TS_ASSERT_EQUALS( *i1, v);
			v--;
		}
		TS_ASSERT(!t1.destroy());
		TS_ASSERT(!t2.destroy());
	}
	
	void test_const()
	{
		Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());				
		for(int i=100; i>0; i--)
		{
			TS_ASSERT(!t1.push_front(i));
		}
		const Lsc::slist<int> & t2 = t1;
		int p = 1;
		for(Lsc::slist<int>::const_iterator i1 = t2.begin(); i1!=t2.end(); ++i1)
		{
			TS_ASSERT_EQUALS(p , *i1);
			p++;
		}
		TS_ASSERT(!t1.destroy());
	}
	void test_const1()
	{
		Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());				
		for(int i=100; i>0; i--)
		{
			TS_ASSERT(!t1.push_front(i));
		}
		const Lsc::slist<int> & t2 = t1;
		int p = 1;
		for(Lsc::slist<int>::const_iterator i1 = t2.begin(); i1!=t2.end(); i1++)
		{
			TS_ASSERT_EQUALS(p , *i1);
			p++;
		}
		TS_ASSERT(!t1.destroy());
	}
	void test_const2()
	{
		Lsc::slist<int>::const_iterator i = Lsc::slist<int>::iterator();
	}

	void test_pop_front()
	{
		Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());
		for(int i=0; i<100; i++)
		{
			TS_ASSERT(!t1.push_front(i));
		}
        TS_ASSERT(100 == t1.size());
		for(int i=99; i>=0; i--)
		{
			TS_ASSERT_EQUALS(i, t1.front());
			t1.pop_front();
		}
        TS_ASSERT(0 == t1.size());
		TS_ASSERT(!t1.destroy());
	}
	void test_sort()
	{
		Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());
		for(int i=100; i>0; i--)
		{
			TS_ASSERT(!t1.push_front(rand()));
			//TS_ASSERT(!t1.push_front(i));
		}
        TS_ASSERT(100 == t1.size());
		t1.sort();
		TS_ASSERT_EQUALS(t1.size() , 100);
		for(Lsc::slist<int>::iterator i1 = t1.begin(); i1!=t1.end(); ++i1)
		{
			//TS_ASSERT(tmp > *i1);
			//	printf("%d\n", *i1);
			/*	if( *i1 != v)
				{
				printf("%d, %d",*i1, v);
				ERROR();
				}
				v--;*/
		}
		TS_ASSERT(!t1.destroy());
	}
	void test_sort1()
	{
		Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());
		for(int i=100; i>0; i--)
		{
			//TS_ASSERT(!t1.push_front(rand()));
			TS_ASSERT(!t1.push_front(i));
		}
		t1.sort(std::less<int>());
		TS_ASSERT_EQUALS(t1.size() , 100);
		for(Lsc::slist<int>::iterator i1 = t1.begin(); i1!=t1.end(); ++i1)
		{
			//	printf("%d\n", *i1);
			/*	if( *i1 != v)
				{
				printf("%d, %d",*i1, v);
				ERROR();
				}
				v--;*/
		}
		TS_ASSERT(!t1.destroy());
	}
	void test_remove()
	{
		Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());
		for(int i=100; i>0; i--)
		{
			TS_ASSERT(!t1.push_front(i));
		}
		t1.remove(50);
		TS_ASSERT_EQUALS(t1.size(), 99);
		TS_ASSERT(!t1.destroy());
	}

	void test_remove1()
	{
		Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());
		for(int i=100; i>0; i--)
		{
			TS_ASSERT(!t1.push_front(i));
		}
		TS_ASSERT(!t1.remove_if(p()));
		TS_ASSERT_EQUALS(t1.size(), 99);
		TS_ASSERT(!t1.destroy());
	}
	
	void test_erase_after()
	{
		Lsc::slist<int> t1;
        Lsc::slist<int> t2;
		TS_ASSERT(!t1.create());
        TS_ASSERT(!t2.create());
		for(int i=100; i>0; i--)
		{
			TS_ASSERT(!t1.push_front(i));
		}
		t1.erase_after(t1.begin());
        t2.erase_after(t1.begin()); 
		TS_ASSERT_EQUALS(t1.size(), 98);
		TS_ASSERT(!t1.destroy());
        TS_ASSERT(!t2.destroy());
	}
	void test_erase_after1()
	{
		Lsc::slist<int> t1;
        Lsc::slist<int> t2;
		TS_ASSERT(!t1.create());
        TS_ASSERT(!t2.create());
	
		for(int i=100; i>0; i--)
		{
			TS_ASSERT(!t1.push_front(i));
		}
		t1.erase_after(t1.begin(), t1.end());
		TS_ASSERT_EQUALS(t1.size(), 1);
        TS_ASSERT_EQUALS(t2.size(), 0);
		
        for(int i=100; i>0; i--)
		{
			TS_ASSERT(!t1.push_front(i));
		}
		t2.erase_after(t1.begin(), t1.end());
		TS_ASSERT_EQUALS(t1.size(), 1);
        TS_ASSERT_EQUALS(t2.size(), 0);
		
        TS_ASSERT(!t1.destroy());
        TS_ASSERT(!t2.destroy());
	}
	void test_reverse()
	{
		Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());
		for(int i=0; i<100; i++)
		{
			TS_ASSERT(!t1.push_front(i));
		}
		t1.reverse();
		TS_ASSERT_EQUALS(t1.size(), 100);
		for(int i=0; i<100; i++)
		{
			TS_ASSERT_EQUALS(i ,t1.front());
			t1.pop_front();
		}
		TS_ASSERT(!t1.destroy());
	}
	void test_swap()
	{
		Lsc::slist<int> t1;
		Lsc::slist<int> t2;
		TS_ASSERT(!t1.create());				
		TS_ASSERT(!t2.create());				
		for(int i=0; i<100; i++)
		{
			TS_ASSERT(!t1.push_front(i));
		}
		for(int i=0; i<50; i++)
		{
			TS_ASSERT(!t2.push_front(3 * i));
		}
		t2.swap(t1);
		TS_ASSERT_EQUALS(t1.size() , 50);
		TS_ASSERT_EQUALS(t2.size() , 100);
		TS_ASSERT(!t1.destroy());
		TS_ASSERT(!t2.destroy());
	}

	
	void test_serialization()
	{
		
		Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());
		for(int i=0; i<100; i++)
		{
			TS_ASSERT(!t1.push_front(i));
		}

		Lsc::filestream fd;
		fd.open("data", "w");
		fd.setwbuffer(1<<20);
		Lsc::binarchive ar(fd);
		TS_ASSERT (ar.write(t1) == 0);
		fd.close();
	
		t1.clear();
		TS_ASSERT_EQUALS(t1.size(), 0);
		std::string str;
		fd.open("data", "r");
		{
			Lsc::binarchive ar(fd);
			TS_ASSERT (ar.read(&t1) == 0);
			fd.close();
		}
		TS_ASSERT_EQUALS(t1.size(), 100);
		for(int i=99; i>=0; i--)
		{
			TS_ASSERT_EQUALS(i ,t1.front());
			t1.pop_front();
		}
	}
	void test_previous()
	{
		Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());
		for(int i=0; i<100; i++)
		{
			TS_ASSERT(!t1.push_front(i));
		}

		Lsc::slist<int>::iterator i1 = t1.begin(); 
		for(int i =0; i<50; ++i)
		{
			i1++;
		}
		TS_ASSERT_EQUALS(*i1, 49);
		TS_ASSERT_EQUALS(*t1.previous(i1), 50);
	}
	void test_merge()
	{
		//Lsc::slist<int, Lsc::Lsc_alloc<int> > t1;
		//Lsc::slist<int, Lsc::Lsc_alloc<int> > t1;
		Lsc::slist<int> t1;
		Lsc::slist<int> t2;
		TS_ASSERT(!t1.create());				
		TS_ASSERT(!t2.create());				
		t2.merge(t1);
		TS_ASSERT_EQUALS(t2.empty() , true);
		for(int i=49; i>=0; i--)
		{
			TS_ASSERT(!t1.push_front(2*i));
		}
		TS_ASSERT_EQUALS(t2.size() , 0);
		t2.merge(t1);
		TS_ASSERT_EQUALS(t2.size() , 50);
		for(int i=49; i>=0; i--)
		{
			TS_ASSERT(!t1.push_front(2*i+1));
		}
		t2.merge(t1);
		TS_ASSERT_EQUALS(t1.empty() , true);
		TS_ASSERT_EQUALS(t2.size() , 100);
		TS_ASSERT(!t1.destroy());
		Lsc::slist<int>::iterator p = t2.begin();
		for(int v = 0; v < 100; v++)
		{
			TS_ASSERT_EQUALS(*p , v);
			p++;
		}
		TS_ASSERT(!t2.destroy());
	}
    void test_size()
    {
        Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());	
		const size_t N = 1000000;
        for(size_t i=0; i<N; i++)
		{
			TS_ASSERT(!t1.push_front(i));
            TS_ASSERT((i + 1) == t1.size());
        }
        TS_ASSERT(N == t1.size());
		TS_ASSERT(t1.size()<t1.max_size());
		TS_ASSERT(!t1.destroy());
    }
    void test_iterator(){
        {
            //non-const
            Lsc::slist<int> li;
            
            Lsc::slist<int>::iterator it1 = li.begin();
            Lsc::slist<int>::iterator it2 = li.end();
            TS_ASSERT(it1 == it2);
            
            Lsc::slist<int>::const_iterator cit1 = li.begin();
            Lsc::slist<int>::const_iterator cit2 = li.end();
        
        }
        {
            //const
            const Lsc::slist<int> li;
            
            Lsc::slist<int>::const_iterator cit1 = li.begin();
            Lsc::slist<int>::const_iterator cit2 = li.end();
            TS_ASSERT(cit1 == cit2);
        }
    }

    void test_iterator_2(){
		Lsc::slist<int> t1;
		TS_ASSERT(!t1.create());
        TS_ASSERT(0 == t1.size());
		for(int i=0; i<100; i++)
		{
			TS_ASSERT(!t1.push_front(i));
		}
        TS_ASSERT(100 == t1.size());
		int v = 99;
		for(Lsc::slist<int>::iterator i = t1.begin(); i != t1.end(); i++)
		{
			TS_ASSERT_EQUALS(*i, v);
			v--;
		}
		v = 99;
		for(Lsc::slist<int>::iterator i = t1.begin(); i != t1.end(); ++i)
		{
			TS_ASSERT_EQUALS(*i, v);
			v--;
		}
		TS_ASSERT(!t1.destroy());
    }

};
