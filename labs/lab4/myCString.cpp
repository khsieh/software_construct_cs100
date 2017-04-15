#include "myCString.h"
#include <fstream>

using namespace std;

char* my_strcpy( char* new_string, char* str ) {
	new_string = new char[ my_strlen(str)+1 ];
	
	unsigned i = 0;
	for ( i = 0; str[i] != '\0'; ++i )
		new_string[i] = str[i];
	
	new_string[i] = '\0';

	return new_string;
}

char* my_strcat( char* dest, char* src ) {
	

	char* new_string = dest;
	dest = new char[ my_strlen(new_string)+my_strlen(src)+1 ];
	
	unsigned i = 0;
	for( i = 0; new_string[i] != '\0'; ++i )
		dest[i] = new_string[i];
	
	unsigned j = i;
	for ( j = i; src[j-i] != '\0'; ++j )
		dest[j] = src[j-i];

	dest[j] = '\0';

	//delete[] dest;
	//dest = new_string;
	new_string = NULL;

	return dest;
}

int my_strcmp( const char* str1, const char* str2 ) {

	unsigned i = 0;
	for ( i = 0; str1[i] != '\0' && str2[i] != '\0'; ++i ) {
		if ( str1[i] > str2[i] )
			return 1;
		if ( str1[i] < str2[i] )
			return -1;
	}
	
	if(str1[i] - str2[i] == 0)
		return 0;
	if(str1[i] - str2[i] > 0)
		return 1;
	if(str1[i] - str2[i] < 0)
		return -1;
	//if ( str1[i] == '\0' && str2[i] == '\0' ) 
	//	return 0;
	//if ( str1[i] != '\0' && str2[i] == '\0' )
	//	return 1;
	//if( str1[i] == '\0' && str2[i] != '\0' )
	//	return -1;
	//return 0;
}

const char* my_strchr( const char* str, int c ) {
	for ( unsigned i = 0; str[i] != '\0'; ++i )
		if ( str[i] == c )
			return str+i;

	return NULL;
}

const char* my_strstr( const char* str1, const char* str2 ) {
	if ( my_strlen(str1) < my_strlen(str2) )
		return NULL;

	for ( unsigned i = 0; str1[i] != '\0'; ++i ) {
		for ( unsigned j = i; str1[j]!='\0'; ++j ) {
			if ( str2[j-i] == '\0' )
				return str1+i;
			if ( str1[j] != str2[j-i] )
				break;
		}
			
	}

	return NULL;
}

size_t my_strlen( const char* str ) {
	size_t c_size = 0;
	
	for ( c_size = 0; str[c_size] != '\0'; ++c_size ) {
		//do nothing
	}

	return c_size;
}

ostream& operator << ( ostream& out, char* str ) {
	
	for ( unsigned i = 0; str[i] != '\0'; ++i) {
		out << str[i];
	}
	return out;
}

int main() {

	char test_string1[] = "hello!";
	char test_string2[2];
	
	//copy str1 to str2, both have "hello!"
	cout << "Testing my_strcpy" << endl;
	cout << "strcpy:    " << strcpy(test_string2, test_string1) << endl;
	cout << "my_strcpy: " << my_strcpy(test_string2, test_string1) << endl;
	cout << endl;

	//make str3 "world"
	//use strcat to append str3 to str1
	//use my_strcat to append str3 to str2
	char test_string3[] = " world";
	cout << "Testing my_strcat" << endl;
	cout << "strcat:    " << strcat(test_string1, test_string3) << endl;
	cout << "my_strcat: " << my_strcat(test_string2, test_string3) << endl;
	cout << "test_string1: " << test_string1 << endl;
	cout << "test_string2: " << test_string2 << endl;
	cout << endl;

	//compare hell and hello, resulting -1
	cout << "Testing my_strcmp with 'hell' and 'hello'" << endl;
	cout << "strcmp:    " << strcmp( "hell","hello" ) << endl;
	cout << "my_strcmp: " << my_strcmp( "hell", "hello" ) << endl;
	cout << endl;

	//compare hello and hell, resulting 1
	cout << "Testing my_strcmp with 'hello' and 'hell'" << endl;
	cout << "strcmp:    " << strcmp("hello", "hell") << endl;
	cout << "my_strcmp: " << my_strcmp("hello", "hell") << endl;
	cout << endl;
	
	//compare hello and hello, resulting 0
	cout << "Testing my_strcmp with 'hello' and 'hello'" << endl;
	cout << "strcmp:    " << strcmp("hello", "hello") << endl;
	cout << "my_strcmp: " << my_strcmp("hello", "hello") << endl;
	cout << endl;
	
	//finding '!' in test_string1, result: 5
	cout << "Testing my_strchr with '!' in 'hello! world'" << endl;
	cout << "strchr:    " << strchr( test_string1, '!' ) - test_string1 << endl;
	cout << "my_strchr: " << my_strchr( test_string1, '!' ) - test_string1 << endl;
	cout << endl;

	//finding 'q' in test_string1, result: junk
	cout << "Testing my_strchr with 'q' in 'hello! world'" << endl;
	cout << "strchr:    " << strchr( test_string1, 'q' ) - test_string1 << endl;
	cout << "my_strchr: " << my_strchr( test_string1, 'q' ) -test_string1 << endl;
	cout << endl; 
	
	//searching for 'wor' in 'hello! world', result: 7
	cout << "Testing my_strstr with 'hello! world' and 'wor'" << endl;
	cout << "strstr:    " << strstr(test_string1,"wor") - test_string1 << endl;
	cout << "my_strstr: " << my_strstr(test_string1, "wor") - test_string1 << endl;
	cout << endl;
	
	//searching in empty string. IT CRASHES!!

	//searching for 'what' in 'hello! world', result: SEG FAULT 
	cout << "Testing my_strstr with 'not here' and 'what'" << endl;
	//cout << "strstr:    " << strstr(test_string1, "what") << endl;
	//cout << "my_strstr: " << my_strstr(test_string1, "what") << endl;
	cout << "it seg faulted! :C" << endl;
	cout << endl;
	
	//print the length of test_string1, result:12
	cout << "Testing my_strlen" << endl;
	cout << "strlen:    " << strlen(test_string1) << endl;
	cout << "my_strlen: " << my_strlen(test_string1) << endl;
	cout << endl;

	return 0;
}
