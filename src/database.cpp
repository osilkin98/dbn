/*
The MIT License (MIT)

Copyright (c) 2019 Grayson Burton

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <gmp.h>
#include <gmpxx.h>
#include "hash.h"
#include "database.h"

constexpr unsigned int prime_test_reps = 50U;
constexpr static bool prime_allow_probable = true;

using namespace dbn;

enum class primality {
	composite = 0, probable = 1, certain = 2,
};

bool database::insert(const row& entry) noexcept
{
	if (search(entry)) return false;
	
	int is_prime = mpz_probab_prime_p(entry.get_mpz_t(), prime_test_reps);
	
	if (is_prime == static_cast<int>(primality::composite)) return false;
	else if (is_prime == static_cast<int>(primality::certain) or
			prime_allow_probable) {
		db_number *= entry;
		
		return true;
	} else return false;
}

bool database::insert(const uint32_t entry_hash) noexcept
{
	return insert(map_hash_to_prime(entry_hash));
}

bool database::search(const row& entry) const noexcept
{
	return mpz_divisible_p(db_number.get_mpz_t(), entry.get_mpz_t());
}

bool database::search(const uint32_t entry_hash) const noexcept
{
	return search(map_hash_to_prime(entry_hash));
}

bool database::remove(const row& entry) noexcept
{
	if (search(entry)) {
		db_number /= entry;
		
		return true;
	} else return false;
}

bool database::remove(const uint32_t entry_hash) noexcept
{
	return remove(map_hash_to_prime(entry_hash));
}
