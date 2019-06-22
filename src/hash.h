/*
The MIT License (MIT)

Copyright (c) 2019 Grayson Burton

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef dbn_hash_h
#define dbn_hash_h

#include <cstdint>
#include <cstddef>
#include <gmpxx.h>

extern "C" {
#include <sodium.h>
}

#ifndef UINT32_C
	#error "std::uint32_t must be defined, but wasn't found."
#endif

namespace dbn {
	using std::uint32_t;
	using hash_type = uint32_t;
	using std::size_t;
	using bigint = mpz_class;
	using bigint_raw = mpz_t;
	using hash_key = unsigned char[crypto_shorthash_siphash24_KEYBYTES];
	
	hash_type hash(
		const unsigned char * start,
		const size_t size,
		hash_key key
	) noexcept;
	
	bigint map_hash_to_prime(const hash_type obj_hash) noexcept;
	
	template <class T>
	hash_type hl_hash(const T& obj, hash_key key) noexcept;
	
	template <class T>
	bigint phash(const T& obj, hash_key key) noexcept;
}

template <class T>
dbn::hash_type dbn::hl_hash(const T& obj, hash_key key) noexcept
{
	const unsigned char* obj_ptr = reinterpret_cast<const unsigned char*>(&obj);
	
	return dbn::hash(obj_ptr, sizeof(T), key);
}

template <class T>
dbn::bigint dbn::phash(const T& obj, hash_key key) noexcept
{
	return hl_hash(dbn::hl_hash(obj, key));
}

#endif
