/*
 * Utility.hpp
 *
 *  Created on: Oct 16, 2013
 *      Author: Cfyz
 */

#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <string>
#include <sstream>
#include <mutex>
#include <algorithm>

namespace BearLibTerminal
{
	template<typename T, typename char_t> bool try_parse(const std::basic_string<char_t>& s, T& out)
	{
		std::basic_stringstream<char_t> stream(s);
		stream >> out;
		return !(stream.fail() || stream.bad());
	}

	bool try_parse(const std::wstring& s, bool& out);

	bool try_parse(const std::wstring& s, uint16_t& out);

	bool try_parse(const std::wstring& s, wchar_t& out);

	template<typename char_t, typename T> std::basic_string<char_t> to_string(const T& value)
	{
		std::basic_ostringstream<char_t> stream;
		stream << value;
		return stream.str();
	}

	template<typename char_t> bool ends_with(const std::basic_string<char_t>& what, const std::basic_string<char_t>& with)
	{
		// FIXME: does not handle multiple occurences properly
		return what.find(with) == what.length() - with.length();
	}

	template<typename char_t> std::basic_string<char_t> file_extension(const std::basic_string<char_t>& s)
	{
		size_t n = s.find_last_of(char_t('.'));
		if (s.length() > 1 && n < s.length()-1)
		{
			return s.substr(n+1);
		}
		else
		{
			return std::basic_string<char_t>();
		}
	}

	template<typename T> T get_locked(const T& reference, std::mutex& lock)
	{
		std::lock_guard<std::mutex> guard(lock);
		return reference;
	}

	template<typename char_t> std::basic_string<char_t> to_lower(std::basic_string<char_t> s)
	{
		std::transform(s.begin(), s.end(), s.begin(), ::tolower);
		return s;
	}
}

#endif /* UTILITY_HPP_ */
