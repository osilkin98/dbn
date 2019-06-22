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

extern "C" {
#include <sodium.h>
}

#if crypto_shorthash_siphash24_BYTES != 8U
	#error "Siphash24 must have 8 bytes as the hash length."
#endif

using namespace dbn;

dbn::uint32_t dbn::hash(
	const unsigned char * const start,
	const dbn::size_t size,
	dbn::hash_key key
) noexcept
{
	unsigned char data_hash[crypto_shorthash_BYTES];
	
	crypto_shorthash(data_hash, start, size, key);
	
	const uint32_t first_half = data_hash[0] | (data_hash[1] >> 8) |
		(data_hash[2] >> 16) | (data_hash[3] >> 24);
	const uint32_t second_half = data_hash[4] | (data_hash[5] >> 8) |
		(data_hash[6] >> 16) | (data_hash[7] >> 24);
	
	return first_half ^ second_half;
}

bigint dbn::map_hash_to_prime(const dbn::uint32_t obj_hash) noexcept
{
	bigint curprime = 2;
	
	for (dbn::uint32_t i = 0; i < obj_hash; i++)
		mpz_nextprime(curprime.get_mpz_t(), curprime.get_mpz_t());
	
	return curprime;
}
