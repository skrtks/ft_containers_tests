/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mapTest.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 11:14:55 by sam           #+#    #+#                 */
/*   Updated: 2020/11/01 11:14:55 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Catch2.h"
#include "map.hpp"

#include <map>

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

TEST_CASE("Map: Constructors", "[Map]") {
	ft::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	ft::map<char,int> second (first.begin(),first.end());

	ft::map<char,int> third (second);

	ft::map<char,int,classcomp> fourth;                 // class as Compare
	fourth['a']=10;
	fourth['b']=30;
	fourth['c']=50;
	fourth['d']=70;

	bool(*fn_pt)(char,char) = fncomp;
	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
	fifth['a']=10;
	fifth['b']=30;
	fifth['c']=50;
	fifth['d']=70;

	REQUIRE(first['b'] == 30);
	REQUIRE(first['c'] == 50);

	REQUIRE(second['b'] == 30);
	REQUIRE(second['c'] == 50);

	REQUIRE(third['b'] == 30);
	REQUIRE(third['c'] == 50);

	REQUIRE(fourth['b'] == 30);
	REQUIRE(fourth['c'] == 50);

	REQUIRE(fifth['b'] == 30);
	REQUIRE(fifth['c'] == 50);
}

TEST_CASE("Map: Insert + empty + size", "[Map]") {
	ft::map<char,int> mymap;
	REQUIRE(mymap.empty() == true);
	// first insert function version (single parameter):
	mymap.insert ( std::pair<char,int>('a',100) );
	mymap.insert ( std::pair<char,int>('z',200) );

	std::pair<ft::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( std::pair<char,int>('z',500) );
	REQUIRE(ret.second == false);

	// second insert function version (with hint position):
	ft::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
	mymap.insert (it, std::pair<char,int>('c',400));	  // no max efficiency inserting
	REQUIRE(mymap.size() == 4);

	// third insert function version (range insertion):
	ft::map<char,int> anothermap;
	anothermap.insert(mymap.begin(), mymap.end());
	REQUIRE(mymap.size() == 4);
}

TEST_CASE("Map: Find", "[Map]") {
	ft::map<char,int> mymap;
	// first insert function version (single parameter):
	mymap.insert ( std::pair<char,int>('a',100) );
	mymap.insert ( std::pair<char,int>('z',200) );

	// second insert function version (with hint position):
	ft::map<char,int>::iterator it;
	it = mymap.find('a');
	bool res = it == mymap.begin();
	REQUIRE(res == true);
	it = mymap.find('x');
	res = it == mymap.end();
	REQUIRE(res == true);
}

TEST_CASE("Map: Iterators", "[Map]") {
	ft::map<int, int> myMap;

	myMap.insert(std::make_pair(9, 9));
	myMap.insert(std::make_pair(3, 3));
	myMap.insert(std::make_pair(8, 8));
	myMap.insert(std::make_pair(0, 0));
	myMap.insert(std::make_pair(7, 7));
	myMap.insert(std::make_pair(6, 6));
	myMap.insert(std::make_pair(5, 5));
	myMap.insert(std::make_pair(4, 4));
	myMap.insert(std::make_pair(2, 2));
	myMap.insert(std::make_pair(1, 1));

	ft::map<int, int>::iterator it = myMap.begin();
	for (int i = 0; i < 10; ++i) {
		REQUIRE(i == it->second);
		++it;
	}
	it = myMap.end();
	--it;
	for (int i = 9; i != 0; --i) {
		REQUIRE(i == it->second);
		--it;
	}
	ft::map<int, int>::reverse_iterator rit = myMap.rbegin();
	for (int i = 9; i != 0; --i) {
		REQUIRE(i == rit->second);
		++rit;
	}
	rit = myMap.rend();
	--rit;
	for (int i = 0; i < 10; ++i) {
		REQUIRE(i == rit->second);
		--rit;
	}
}

TEST_CASE("Map: Erase", "[Map]") {
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator it;

	// insert some values:
	mymap.insert(std::make_pair('a', 10));
	mymap.insert(std::make_pair('b', 20));
	mymap.insert(std::make_pair('c', 30));
	mymap.insert(std::make_pair('d', 40));
	mymap.insert(std::make_pair('e', 50));
	mymap.insert(std::make_pair('f', 60));

	it=mymap.find('b');
	mymap.erase (it);                   // erasing by iterator

	mymap.erase ('c');                  // erasing by key

	it=mymap.find ('e');
	mymap.erase ( it, mymap.end() );    // erasing by range

	// show content:
	it=mymap.begin();
	REQUIRE(mymap.size() == 2);
	REQUIRE(it->second == 10);
	++it;
	REQUIRE(it->second == 40);
}

TEST_CASE("Map: [] overload", "[Map]") {
	ft::map<char,int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	REQUIRE(mymap['x'] == 100);
	REQUIRE(mymap['y'] == 200);
	REQUIRE(mymap['z'] == 300);
}

TEST_CASE("Map: Swap", "[Map]") {
	ft::map<char,int> foo,bar;
	ft::map<char,int>::iterator it;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	foo.swap(bar);

	REQUIRE(foo.size() == 3);
	REQUIRE(foo['a'] == 11);
	REQUIRE(foo['b'] == 22);
	REQUIRE(foo['c'] == 33);
	it = foo.begin();
	REQUIRE(it->second == 11);

	REQUIRE(bar.size() == 2);
	REQUIRE(bar['x'] == 100);
	REQUIRE(bar['y'] == 200);
	it = bar.begin();
	REQUIRE(it->second == 100);
}

TEST_CASE("Map: Count", "[Map]") {
	ft::map<char,int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	REQUIRE(mymap.count('x') == 1);
	REQUIRE(mymap.count('a') == 0);
}

TEST_CASE("Map: upper/lower bound", "[Map]") {
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itlow=mymap.lower_bound ('b');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)
	REQUIRE(itlow->first == 'b');
	REQUIRE(itup->first == 'e');
}

TEST_CASE("Map: equal_range", "[Map]") {
	ft::map<char,int> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;

	std::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
	ret = mymap.equal_range('b');

	REQUIRE(ret.first->first == 'b');
	REQUIRE(ret.second->first == 'c');
}
