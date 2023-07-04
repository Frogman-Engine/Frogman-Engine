#ifndef _FE_CORE_FSTREAM_GUARD_HXX_
#define _FE_CORE_FSTREAM_GUARD_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"
#include <fstream>


BEGIN_NAMESPACE(FE)

template<class fstream>
class basic_fstream_guard final
{
private:
	fstream& m_fstream_ref;

public:
	typedef fstream fstream_type;

	basic_fstream_guard(fstream& file_io_ref_p) noexcept : m_fstream_ref(file_io_ref_p) {}

	basic_fstream_guard(fstream& file_io_ref_p, const typename fstream::char_type* cstr_ptr_p) noexcept : m_fstream_ref(file_io_ref_p)
	{
		if (this->m_fstream_ref.is_open() == false)
		{
			this->m_fstream_ref.open(cstr_ptr_p);
		}
	}


	basic_fstream_guard(const basic_fstream_guard& other_ref_p) noexcept = delete;


	basic_fstream_guard(basic_fstream_guard&& move_p) noexcept = default;


	basic_fstream_guard& operator=(const basic_fstream_guard& other_ref_p) noexcept = delete;


	basic_fstream_guard& operator=(basic_fstream_guard&& move_p) noexcept = default;


	~basic_fstream_guard() noexcept
	{
		if (this->m_fstream_ref.is_open() == true)
		{
			this->m_fstream_ref.close();
		}
	}


	void operator<<(const typename fstream::char_type* cbuffer_ptr_p) noexcept { this->m_fstream_ref << cbuffer_ptr_p; }

	void operator<<(const typename fstream::char_type cbuffer_p) noexcept { this->m_fstream_ref << cbuffer_p; }

	bool operator>>(typename fstream::char_type* buffer_ptr_p) noexcept
	{
		if (this->m_fstream_ref.is_open() == false) { return false; }

		this->m_fstream_ref << buffer_ptr_p;
		return true;
	}

	bool operator>>(typename fstream::char_type buffer_p) noexcept
	{
		if (this->m_fstream_ref.is_open() == false) { return false; }

		this->m_fstream_ref << buffer_p;
		return true;
	}


	_FORCE_INLINE_ bool is_open() noexcept { return this->m_fstream_ref.is_open(); }

	_FORCE_INLINE_ void endl() noexcept { this->m_fstream_ref << std::endl; }

	template<class container>
	bool write_a_file(container& container_p) noexcept
	{
		if (this->m_fstream_ref.is_open() == false)
		{
			return false;
		}

		for (auto& string_ref : container_p)
		{
			if (*(string_ref.unsafe_begin()) != static_cast<const typename fstream::char_type>('\0'))
			{
				this->m_fstream_ref << string_ref.c_str() << std::endl;
			}
		}

		return true;
	}

	template<class container, FE::uint64 line_buffer_max_size>
	bool read_a_file(container& container_p) noexcept
	{
		if (this->m_fstream_ref.is_open() == false)
		{
			return false;
		}

		typename fstream::char_type l_string_buffer[line_buffer_max_size] = "\0";

		while (this->m_fstream_ref)
		{
			this->m_fstream_ref.getline(l_string_buffer, line_buffer_max_size);
			if (l_string_buffer[0] != static_cast<const typename fstream::char_type>('\0'))
			{
				container_p.emplace_back(l_string_buffer);
			}
		}

		return true;
	}

	_FORCE_INLINE_ fstream& get_fstream_reference() noexcept { return this->m_fstream_ref; }
};

using fstream_guard = FE::basic_fstream_guard<std::fstream>;
using wfstream_guard = FE::basic_fstream_guard<std::wfstream>;

using ofstream_guard = FE::basic_fstream_guard<std::ofstream>;
using wofstream_guard = FE::basic_fstream_guard<std::wofstream>;

using ifstream_guard = FE::basic_fstream_guard<std::ifstream>;
using wifstream_guard = FE::basic_fstream_guard<std::wifstream>;

END_NAMESPACE
#endif
