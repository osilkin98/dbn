/*
The MIT License (MIT)

Copyright (c) 2019 Grayson Burton

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef dbn_database_h
#define dbn_database_h

#include <gmpxx.h>
#include "hash.h"

namespace dbn {
	using bigint = mpz_class;
	
	class database;
}

class dbn::database {
	public:
		using row = bigint;
		
		database() = default;
		database(const database&) = default;
		database(database&&) = default;
		database& operator=(const database&) = default;
		database& operator=(database&&) = default;
		~database() = default;
		
		// Returns whether the entry was inserted.
		// This depends on if the input was prime and if the entry was
		// already in the database.
		bool insert(const row& entry) noexcept;
		bool insert(const uint32_t entry_hash) noexcept;
		
		// Returns whether an entry is in the database.
		bool search(const row& entry) const noexcept;
		bool search(const uint32_t entry_hash) const noexcept;
		
		// Returns whether the entry was in the database to begin with.
		bool remove(const row& entry) noexcept;
		bool remove(const uint32_t entry_hash) noexcept;
	
	private:
		bigint db_number = 1_mpz;
};

#endif
