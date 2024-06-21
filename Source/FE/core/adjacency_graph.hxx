#ifndef _FE_CORE_CONTAINERS_ADJACENCY_GRAPH_HXX_
#define _FE_CORE_CONTAINERS_ADJACENCY_GRAPH_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/allocator.hxx>
#include <FE/core/iterator.hxx>

// std
#include <any>
#include <set>




BEGIN_NAMESPACE(FE)

namespace internal::adjacency_graph
{
	template<typename T>
	struct less
	{
		constexpr boolean operator()(const T& left_p, const T& right_p) const noexcept
		{
    		return left_p.get_key() < right_p.get_key();
		}
	};

	template<typename T>
	struct greater
	{
		constexpr boolean operator()(const T& left_p, const T& right_p) const noexcept
		{
    		return left_p.get_key() > right_p.get_key();
		}
	};
}

template<typename Key, typename T>
class adjacency_graph
{
public:
	class node_type;

	using key_type = Key;
	using value_type = T; 
	using underlying_container = std::set<node_type, internal::adjacency_graph::less<node_type>, FE::aligned_allocator<node_type>>;
	using edge_type = typename underlying_container::value_type*;
	using key_comparator = typename underlying_container::key_compare;
	using allocator_type = typename underlying_container::allocator_type;
	using size_type = typename underlying_container::size_type;

	class node_type
	{
		friend class adjacency_graph;
		
		node_type* m_upper_adjacent = nullptr;
		node_type* m_lower_adjacent = nullptr;
		std::any m_iterator_to_this;

		Key m_key;

	public: 
		T _value;


		node_type(const Key& key_p, const T& value_p) noexcept : m_key(key_p), _value(value_p) {}
		node_type() noexcept = default;
		~node_type() noexcept = default;

		_FORCE_INLINE_ const Key& get_key() const noexcept { return this->m_key; }
	};

	struct adjacent_node_iterator
	{
		using category = adjacent_node_iterator;
		using value_type = node_type;
		using difference_type = var::ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;
		using const_pointer = const value_type*;
		using const_reference = const value_type&;

	protected:
		pointer m_iterator;

	public:
		_FORCE_INLINE_ _CONSTEXPR20_ adjacent_node_iterator() noexcept : m_iterator() {}
		_FORCE_INLINE_ _CONSTEXPR17_ adjacent_node_iterator(const_pointer const value_p) noexcept : m_iterator(const_cast<pointer>(value_p)) {}
		_FORCE_INLINE_ _CONSTEXPR20_ adjacent_node_iterator(const adjacent_node_iterator& other_p) noexcept : m_iterator(other_p.m_iterator) {}
		_FORCE_INLINE_ _CONSTEXPR20_ adjacent_node_iterator(adjacent_node_iterator&& other_p) noexcept : m_iterator(other_p.m_iterator) { other_p.m_iterator = nullptr; }
		_FORCE_INLINE_ _CONSTEXPR23_ ~adjacent_node_iterator() noexcept {}

		_FORCE_INLINE_ _CONSTEXPR20_ boolean is_null() const noexcept { return this->m_iterator == nullptr; }

		_FORCE_INLINE_ _CONSTEXPR20_ reference operator*() const noexcept
		{
			FE_ASSERT(this->m_iterator == nullptr, "${%s@0}: Unable to dereference a null iterator.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
			return *(this->m_iterator);
		}

		_FORCE_INLINE_ _CONSTEXPR20_ pointer operator->() const noexcept
		{
			FE_ASSERT(this->m_iterator == nullptr, "${%s@0}: Unable to access a null iterator.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
			return this->m_iterator;
		}


		_FORCE_INLINE_ _CONSTEXPR20_ void operator++() noexcept
		{
			FE_ASSERT(this->m_iterator == nullptr, "${%s@0}: The iterator was null.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
			this->m_iterator = this->m_iterator->m_upper_adjacent;
		}

		_FORCE_INLINE_ _CONSTEXPR20_ void operator--() noexcept
		{
			FE_ASSERT(this->m_iterator == nullptr, "${%s@0}: The iterator was null.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
			this->m_iterator = this->m_iterator->m_lower_adjacent;
		}


		_FORCE_INLINE_ _CONSTEXPR20_ pointer operator+(const difference_type pointer_offset_p) const noexcept
		{			
			pointer l_destination = this->m_iterator;
			for(difference_type i = 0; i < pointer_offset_p; ++i)
			{
				FE_ASSERT(l_destination == nullptr, "${%s@0}: Unable to perform iterator + ${%ld@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), &pointer_offset_p);
				l_destination = l_destination->m_upper_adjacent;
			}
			return l_destination;
		}

		_FORCE_INLINE_ _CONSTEXPR20_ void operator+=(const difference_type pointer_offset_p) noexcept
		{
			for(difference_type i = 0; i < pointer_offset_p; ++i)
			{
				FE_ASSERT(this->m_iterator == nullptr, "${%s@0}: Unable to perform iterator += ${%ld@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), &pointer_offset_p);
				this->m_iterator = this->m_iterator->m_upper_adjacent;
			}
		}


		_FORCE_INLINE_ _CONSTEXPR20_ pointer operator-(const difference_type pointer_offset_p) const noexcept
		{
			pointer l_destination = this->m_iterator;
			for(difference_type i = 0; i < pointer_offset_p; ++i)
			{
				FE_ASSERT(l_destination == nullptr, "${%s@0}: Unable to perform iterator - ${%ld@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), &pointer_offset_p);
				l_destination = l_destination->m_lower_adjacent;
			}
			return l_destination;
		}

		_FORCE_INLINE_ _CONSTEXPR20_ void operator-=(const difference_type pointer_offset_p) noexcept
		{
			for(difference_type i = 0; i < pointer_offset_p; ++i)
			{
				FE_ASSERT(this->m_iterator == nullptr, "${%s@0}: Unable to perform iterator -= ${%ld@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), &pointer_offset_p);
				this->m_iterator = this->m_iterator->m_lower_adjacent;
			}
		}


		_FORCE_INLINE_ _CONSTEXPR20_ difference_type operator-(const adjacent_node_iterator& value_p) const noexcept
		{
			FE_ASSERT(this->m_iterator == nullptr, "${%s@0}: The iterator was null.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
			difference_type l_count = 0;
			for(pointer lower = value_p.m_iterator; this->m_iterator != lower; lower = lower->m_upper_adjacent) 
			{
				FE_ASSERT(lower == nullptr, "${%s@0}: The iterator was null.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
				++l_count;
			}
			return l_count;
		}


		_FORCE_INLINE_ _CONSTEXPR20_ reference operator[](const difference_type index_p) const noexcept
		{	
			FE_ASSERT(this->m_iterator == nullptr, "${%s@0}: The iterator was null.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));

			if(index_p >= 0)
			{
				return *(this->operator+(index_p));
			}
			
			return *(this->operator-(index_p));
		}


		_FORCE_INLINE_ _CONSTEXPR20_ adjacent_node_iterator& operator=(const adjacent_node_iterator& other_p) noexcept
		{
			this->m_iterator = other_p.m_iterator;
			return *this;
		}

		_FORCE_INLINE_ _CONSTEXPR20_ adjacent_node_iterator& operator=(adjacent_node_iterator&& rvalue_p) noexcept
		{
			this->m_iterator = rvalue_p.m_iterator;
			return *this;
		}

		_FORCE_INLINE_ _CONSTEXPR20_ boolean operator<(const adjacent_node_iterator& other_p) const noexcept
		{
			return this->m_iterator < other_p.m_iterator;
		}

		_FORCE_INLINE_ _CONSTEXPR20_ boolean operator<=(const adjacent_node_iterator& other_p) const noexcept
		{
			return this->m_iterator <= other_p.m_iterator;
		}
	
		_FORCE_INLINE_ _CONSTEXPR20_ boolean operator>(const adjacent_node_iterator& other_p) const noexcept
		{
			return this->m_iterator > other_p.m_iterator;
		}

		_FORCE_INLINE_ _CONSTEXPR20_ boolean operator>=(const adjacent_node_iterator& other_p) const noexcept
		{
			return this->m_iterator >= other_p.m_iterator;
		}

		_FORCE_INLINE_ _CONSTEXPR20_ boolean operator==(const adjacent_node_iterator& other_p) const noexcept
		{
			return this->m_iterator == other_p.m_iterator;
		}
	
		_FORCE_INLINE_ _CONSTEXPR20_ boolean operator!=(const adjacent_node_iterator& other_p) const noexcept
		{
			return this->m_iterator != other_p.m_iterator;
		}
	};
	
	using iterator = FE::iterator<adjacent_node_iterator>;
	using const_iterator = FE::const_iterator<adjacent_node_iterator>;
	using reverse_iterator = FE::reverse_iterator<adjacent_node_iterator>;
	using const_reverse_iterator = FE::const_reverse_iterator<adjacent_node_iterator>;

private:
	underlying_container m_set;

public:
	_FORCE_INLINE_ adjacency_graph() noexcept : m_set() {}
	_FORCE_INLINE_ adjacency_graph(const allocator_type& allocator_p) noexcept : m_set(allocator_p) {}
	_FORCE_INLINE_ adjacency_graph(std::initializer_list<node_type>&& initializer_list_p, const allocator_type& allocator_p = allocator_type()) noexcept : m_set(allocator_p) 
	{
		auto l_input_data = const_cast<node_type*>(initializer_list_p.begin());
		auto l_input_end = initializer_list_p.end();

		while(l_input_data != l_input_end)
		{
			this->insert(l_input_data->m_key, l_input_data->_value);
			++l_input_data;
		}
	}

	_FORCE_INLINE_ ~adjacency_graph() noexcept {}

	_FORCE_INLINE_ adjacency_graph(const adjacency_graph& other_p) noexcept : m_set(other_p.m_set) {}
	_FORCE_INLINE_ adjacency_graph(adjacency_graph&& rvalue_p) noexcept : m_set(std::move(rvalue_p.m_set)) {}

	_FORCE_INLINE_ adjacency_graph& operator=(const adjacency_graph& other_p) noexcept
	{
		this->m_set = other_p.m_set;
		return *this;
	}

	_FORCE_INLINE_ adjacency_graph& operator=(adjacency_graph&& rvalue_p) noexcept 
	{
		this->m_set = std::move(rvalue_p.m_set);
		return *this;
	}

	iterator insert(const Key& key_p, const T& value_p) noexcept // Logarithmic time complexity: O(3 * log N)
	{
		node_type l_value;
		l_value.m_key = key_p;
		l_value._value = value_p;
		typename underlying_container::iterator l_result = this->m_set.insert(std::move(l_value)).first;

		auto l_upper_adjacent = l_result;
		++l_upper_adjacent;

		auto l_lower_adjacent = l_result;
		--l_lower_adjacent;
		
		edge_type l_type_casted_result = (l_result != this->m_set.end()) ? iterator_cast<edge_type>(l_result) : nullptr;
		if(l_upper_adjacent != this->m_set.end())
		{
			edge_type l_upper_adjacent_node = iterator_cast<edge_type>(l_upper_adjacent); 
			l_upper_adjacent_node->m_lower_adjacent = l_type_casted_result;
			l_type_casted_result->m_upper_adjacent = l_upper_adjacent_node;
		}

		if(l_lower_adjacent != this->m_set.end())
		{
			edge_type l_lower_adjacent_node = iterator_cast<edge_type>(l_lower_adjacent); 
			l_lower_adjacent_node->m_upper_adjacent = l_type_casted_result;
			l_type_casted_result->m_lower_adjacent = l_lower_adjacent_node;
		}
		return iterator{ l_type_casted_result };
	}

	_FORCE_INLINE_ void erase(iterator position_p) noexcept // Constant time complexity
	{
		FE_ASSERT(position_p == nullptr, "Assertion failure: failed to assert that the iterator must not be null.");

		// restructure adjacent node links
		edge_type l_upper_adjacent = position_p->m_upper_adjacent;
		edge_type l_lower_adjacent = position_p->m_lower_adjacent;

		if(l_lower_adjacent != nullptr)
		{
			l_lower_adjacent->m_upper_adjacent = l_upper_adjacent;
		}

		if(l_upper_adjacent != nullptr)
		{
			l_upper_adjacent->m_lower_adjacent = l_lower_adjacent;
		}

		node_type l_target_to_erase;
		l_target_to_erase.m_key = position_p->get_key();
		this->m_set.erase(l_target_to_erase);
	}

	_FORCE_INLINE_ iterator find(const Key& key_p) noexcept // Logarithmic time complexity
	{
		node_type l_target_to_find;
		l_target_to_find.m_key = key_p;
		return this->m_set.find(l_target_to_find);
	}

	/* Iterating adjacent nodes from begin to end takes linear time complexity of N amount of nodes. */
	_FORCE_INLINE_ iterator begin() const noexcept { return iterator{this->m_set.begin().operator->()}; } 
	_FORCE_INLINE_ const_iterator cbegin() const noexcept { return const_iterator{this->m_set.cbegin().operator->()}; }

	_FORCE_INLINE_ _CONSTEXPR17_ iterator end() const noexcept { return iterator{nullptr}; }
	_FORCE_INLINE_ _CONSTEXPR17_ const_iterator cend() const noexcept { return const_iterator{nullptr}; }

	_FORCE_INLINE_ reverse_iterator rbegin() const noexcept { return reverse_iterator{this->m_set.rbegin().operator->()}; }
	_FORCE_INLINE_ const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator{this->m_set.crbegin().operator->()}; }

	_FORCE_INLINE_ _CONSTEXPR17_ reverse_iterator rend() const noexcept { return reverse_iterator{nullptr}; }
	_FORCE_INLINE_ _CONSTEXPR17_ const_reverse_iterator crend() const noexcept { return const_reverse_iterator{nullptr}; }

	_FORCE_INLINE_ size_type size() const noexcept { return this->m_set.size(); }
	_FORCE_INLINE_ boolean is_empty() const noexcept { return this->m_set.empty(); }
};

END_NAMESPACE
#endif