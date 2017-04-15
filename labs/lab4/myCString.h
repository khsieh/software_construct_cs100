#ifndef __myCString_h_
#define __myCString_h_

#include<cstring>
#include<iostream>

char* my_strcpy( char* str );
char* my_strcat( char* dest, char* src );
int my_strcmp( const char* str1, const char* str2 );
const char* my_strchr( const char* str, int c );
const char* my_strstr( const char* str1, const char* str2 );
size_t my_strlen( const char* str );

#endif //__myCSTRING_h_
