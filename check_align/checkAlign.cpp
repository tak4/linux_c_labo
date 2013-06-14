#include <stdio.h>
#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

template<typename T>
inline unsigned
alignmentof ()
{
  struct S
  {
    char start_;
    T object_;
  };

  return (unsigned) & ((S *) 0)->object_;
}

/* Computes the alignment, in bytes, of TYPE.  */

#define alignof(type) (alignmentof<type> ())

enum A { a };

void showAlign() {
    printf("char           : size=%d,  align=%d\n", sizeof(char),           alignof(char)          );
    printf("signed char    : size=%d,  align=%d\n", sizeof(signed char),    alignof(signed char)   );
    printf("unsigned char  : size=%d,  align=%d\n", sizeof(unsigned char),  alignof(unsigned char) );
    printf("short          : size=%d,  align=%d\n", sizeof(short),          alignof(short)         );
    printf("signed short   : size=%d,  align=%d\n", sizeof(signed short),   alignof(signed short)  );
    printf("unsigned short : size=%d,  align=%d\n", sizeof(unsigned short), alignof(unsigned short));
    printf("int            : size=%d,  align=%d\n", sizeof(int),            alignof(int)           );
    printf("signed int     : size=%d,  align=%d\n", sizeof(signed int),     alignof(signed int)    );
    printf("unsigned int   : size=%d,  align=%d\n", sizeof(unsigned int),   alignof(unsigned int)  );
    printf("enum A         : size=%d,  align=%d\n", sizeof(enum A),         alignof(enum A)        );
    printf("void *         : size=%d,  align=%d\n", sizeof(void *),         alignof(void *)        );
    printf("void (*) ()    : size=%d,  align=%d\n", sizeof(void (*) ()),    alignof(void (*) ())   );
    printf("float          : size=%d,  align=%d\n", sizeof(float),          alignof(float)         );
    printf("double         : size=%d,  align=%d\n", sizeof(double),         alignof(double)        );
    printf("long           : size=%d,  align=%d\n", sizeof(long),           alignof(long)          );
    printf("unsigned long  : size=%d,  align=%d\n", sizeof(unsigned long),  alignof(unsigned long) );
}

int checkAlign ()
{
  if (sizeof  (char)                    !=  1)
    return 1;
  if (alignof (char)                    !=  1)
    return 2;
  if (sizeof  (signed char)             !=  1)
    return 3;
  if (alignof (signed char)             !=  1)
    return 4;
  if (sizeof  (unsigned char)           !=  1)
    return 5;
  if (alignof (unsigned char)           !=  1)
    return 6;
  if (sizeof  (short)                   !=  2)
    return 7;
  if (alignof (short)                   !=  2)
    return 8;
  if (sizeof  (signed short)            !=  2)
    return 9;
  if (alignof (signed short)            !=  2)
    return 10;
  if (sizeof  (unsigned short)          !=  2)
    return 11;
  if (alignof (unsigned short)          !=  2)
    return 12;
  if (sizeof  (int)                     !=  4)
    return 13;
  if (alignof (int)                     !=  4)
    return 14;
  if (sizeof  (signed int)              !=  4)
    return 15;
  if (alignof (signed int)              !=  4)
    return 16;
  if (sizeof  (unsigned int)            !=  4)
    return 17;
  if (alignof (unsigned int)            !=  4)
    return 18;
  if (sizeof  (enum A)                  !=  4)
    return 19;
  if (alignof (enum A)                  !=  4)
    return 20;
#ifdef HAVE_IA64_TYPES
  if (sizeof  (__int64)                 !=  8)
    return 21;
  if (alignof (__int64)                 !=  8)
    return 22;
  if (sizeof  (signed __int64)          !=  8)
    return 23;
  if (alignof (signed ___int64)         !=  8)
    return 24;
  if (sizeof  (unsigned __int64)        !=  8)
    return 25;
  if (alignof (unsigned __int64)        !=  8)
    return 26;
  if (sizeof  (__int128)                != 16)
    return 27;
  if (alignof (__int128)                != 16)
    return 28;
  if (sizeof  (signed __int128)         != 16)
    return 29;
  if (alignof (signed ___int128)        != 16)
    return 30;
  if (sizeof  (unsigned __int128)       != 16)
    return 31;
  if (alignof (unsigned ___int128)      != 16)
    return 32;
#endif  /* HAVE_IA64_TYPES  */
  if (sizeof  (void *)                  !=  4)
    return 33;
  if (alignof (void *)                  !=  4)
    return 34;
  if (sizeof  (void (*) ())             !=  4)
    return 35;
  if (alignof (void (*) ())             !=  4)
    return 36;
  if (sizeof  (float)                   !=  4)
    return 37;
  if (alignof (float)                   !=  4)
    return 38;
  if (sizeof  (double)                  !=  8)
    return 39;
  if (alignof (double)                  !=  8)
    return 40;
#ifdef HAVE_IA64_TYPES
  if (sizeof  (__float80)               != 16)
    return 41;
  if (alignof (__float80)               != 16)
    return 42;
  if (sizeof  (__float128)              != 16)
    return 43;
  if (alignof (__float128)              != 16)
    return 44;
#endif  /* HAVE_IA64_TYPES  */
  if (sizeof  (long)                    !=  4)
    return 50;
  if (alignof (long)                    !=  4)
    return 51;
  if (sizeof  (unsigned long)           !=  4)
    return 52;
  if (alignof (unsigned long)           !=  4)
    return 53;

  return 0;
}


struct _t {
    char   c1;
    double d1;
    char   c2;
    short  s2;
    char   c3;
    long   l3;
    short  s4[10];
} t = {
    1,1,
    2,2,
    3,3,
    {2,2,2,2,2,2,2,2,2,2},
};

const static string empty_str;

/** 
 * stringstream型のクリア
 */
template<class SS>
void clear_sstream(SS& ss ){
	ss.clear();
	ss.str(empty_str);
	ss << dec;
}

ostream& stream_dump(ostream &out, const char*data, size_t data_size, size_t limit_size/*=256*/)
{
	assert(data);

	ostringstream ss1, ss2;
	ss1.setf(ios::hex, ios::basefield);

	const size_t dump_size(std::min(data_size, limit_size));
	const char* const beyond = data +  dump_size;

	for(int i(0); data < beyond; data++, i++  ){
		if(i%16==0){
			ss1 << setw(4) << setfill('0') << i << ": ";
		}

		const int c(static_cast<int>(*data) & 0xff);

		ss1 << setw(2) << setfill('0') << c << ' ';

		ss2 << (isascii(c) and !iscntrl(c) ? *data : '.' );	// ASCII以外は '.'

		if((i+1)%16==0){
			out << ss1.str() << "| " << ss2.str() << endl;
			clear_sstream(ss1);
			ss1.setf(ios::hex, ios::basefield);
			clear_sstream(ss2);
		}
	}
	if(!ss1.str().empty()){
		out << setw(54) << setfill(' ') << setiosflags(ios::left) << ss1.str() << "| " << ss2.str() << endl;
	}
	if(dump_size < data_size ){
		out << "..." << endl;
	}
	return out;
}

int main()
{

	// 各データ型サイズとアライメントを表示する    
    showAlign();
	// ※以下は何をしたいのかよく分からない
	// サイズとアライメントが想定したものかのチェック？ 
    std::cout << checkAlign() << std::endl;
	// 構造体tとアライメントを表示する
    std::cout << sizeof(_t) << ":" <<  alignof(_t) << std::endl;
	// 構造体tのメモリダンプ
    char *p = (char *)&t;
    stream_dump(std::cout,   p, sizeof(t), sizeof(t));
}

