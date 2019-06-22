/*
The MIT License (MIT)

Copyright (c) 2019 Grayson Burton

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>
#include <tuple>
#include <string>
#include <cassert>

extern "C" {
#include <sodium.h>
}

#include "hash.h"
#include "database.h"

int main()
{
	using dbn::hash_type;
	using dbn::bigint;
	using dbn::hash_key;
	
	assert(sodium_init() >= 0);
	hash_key key;
	crypto_shorthash_keygen(key);
	
	std::cout << "File: [" << __FILE__ << "]" << std::endl;
	std::cout << "Beginning test!" << std::endl << std::endl;
	
	std::cout << "Creating data." << std::endl;
	std::tuple<std::string, int> my_data_0 = {"Hello!", 1};
	std::tuple<std::string, int> my_data_1 = {"Hi!", 15};
	std::tuple<int, char, char> my_data_2 = {66, '\n', '"'};
	
	std::cout << "Hashing." << std::endl;
	hash_type my_data_0_hash = dbn::hl_hash(my_data_0, key);
	hash_type my_data_1_hash = dbn::hl_hash(my_data_1, key);
	hash_type my_data_2_hash = dbn::hl_hash(my_data_2, key);
	std::cout << "Data 0 hash:\t" << std::to_string(my_data_0_hash) << std::endl;
	std::cout << "Data 1 hash:\t" << std::to_string(my_data_1_hash) << std::endl;
	std::cout << "Data 2 hash:\t" << std::to_string(my_data_2_hash) << std::endl;
	
	std::cout << "Finding primes." << std::endl;
	bigint my_data_0_prime = dbn::map_hash_to_prime(my_data_0_hash);
	bigint my_data_1_prime = dbn::map_hash_to_prime(my_data_1_hash);
	bigint my_data_2_prime = dbn::map_hash_to_prime(my_data_2_hash);
	std::cout << "Data 0 prime:\t" << my_data_0_prime.get_str() << std::endl;
	std::cout << "Data 1 prime:\t" << my_data_1_prime.get_str() << std::endl;
	std::cout << "Data 2 prime:\t" << my_data_2_prime.get_str() << std::endl;
}
