#include <bit>
#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <vector>

#include <benchmark/benchmark.h>

class Pool_Allocator // note: used with deallocations at any position for blocks of fixed sizes
{
private:

	struct Block { Block * next = nullptr; };
	
public:

	explicit Pool_Allocator(std::size_t size, std::size_t size_block) : m_size(size)
	{
		m_size_block = std::max(size_block, sizeof(Block));

		if (m_size % m_size_block != 0)
		{
			throw std::runtime_error("invalid size");
		}

		make_chain(); m_begin = m_head;
	}

	~Pool_Allocator() noexcept
	{
		for (std::size_t i = 0; i < std::size(m_chains); ++i)
		{
			::operator delete(m_chains[i]);
		}
	}

	[[nodiscard]] void * allocate()
	{
		if (m_head == nullptr) // note: current chain has ended
		{
			if (m_offset == std::size(m_chains))
			{
				make_chain();
			}
			else m_head = get_block(m_chains[++m_offset - 1]); // note: switch to next chain
		}

		auto block = m_head;

		if (!block->next) // note: try switch to next block in current chain
		{
			if (auto next  = get_byte(  block               ) + m_size_block; 
				     next != get_byte(m_chains[m_offset - 1]) + m_size)
			{
				m_head = get_block(next); m_head->next = nullptr;
			}
			else m_head = m_head->next; // note: current chain has ended
		}
		else m_head = m_head->next; // note: next after deallocation

		return block;
	}

	void deallocate(void * ptr) noexcept
	{
		auto block = get_block(ptr); 
		
		block->next = m_head; m_head = block; // note: link freed block to previous head
	}

	void print() const
	{
		std::cout << m_head << std::endl;
	}

private:

	std::byte * get_byte(void * ptr) const noexcept
	{
		return std::bit_cast < std::byte * > (ptr);
	}

	Block * get_block(void * ptr) const 
	{ 
		return std::bit_cast < Block * > (ptr); 
	}

	Block * allocate_blocks() const
	{
		auto block = get_block(::operator new(m_size)); 
		
		block->next = nullptr; return block;
	}

	void make_chain()
	{
		m_head = allocate_blocks(); ++m_offset; m_chains.push_back(m_head);
	}

private:

	std::size_t m_size       = 0;
	std::size_t m_size_block = 0;
		
	Block * m_head = nullptr;

	std::size_t m_offset = 0;

	std::vector < void * > m_chains;

	void * m_begin = nullptr;

}; // class Pool_Allocator

void test_1(benchmark::State & state) // note: very fast
{
	const std::size_t kb = 1024;
	const std::size_t mb = 1024 * 1024;
	const std::size_t gb = 1024 * 1024 * 1024;

	std::vector < void * > pointers(kb, nullptr);

	benchmark::DoNotOptimize(pointers);

	for (auto _ : state)
	{
		Pool_Allocator allocator(gb, mb);

		for (std::size_t i = 0; i < kb; i += 1) pointers[i] = allocator.  allocate();
		for (std::size_t i = 0; i < kb; i += 2)               allocator.deallocate(pointers[i]);
		for (std::size_t i = 0; i < kb; i += 2) pointers[i] = allocator.  allocate();
		for (std::size_t i = 0; i < kb; i += 1)               allocator.deallocate(pointers[i]);
	}
}

void test_2(benchmark::State & state) // note: very slow
{
	const std::size_t kb = 1024;
	const std::size_t mb = 1024 * 1024;

	std::vector < void * > pointers(kb, nullptr);

	benchmark::DoNotOptimize(pointers);

	for (auto _ : state)
	{
		for (std::size_t i = 0; i < kb; i += 1) pointers[i] = ::operator new(mb);
		for (std::size_t i = 0; i < kb; i += 2)               ::operator delete(pointers[i]);
		for (std::size_t i = 0; i < kb; i += 2) pointers[i] = ::operator new(mb);
		for (std::size_t i = 0; i < kb; i += 1)               ::operator delete(pointers[i]);
	}
}

BENCHMARK(test_1);
BENCHMARK(test_2);

int main(int argc, char ** argv) // note: arguments for benchmark
{
	Pool_Allocator allocator(32, 8);                    allocator.print(); // note: initial

	[[maybe_unused]] auto ptr_0 = allocator.allocate(); allocator.print(); // note: head X
	[[maybe_unused]] auto ptr_1 = allocator.allocate(); allocator.print(); // note: head Y
	[[maybe_unused]] auto ptr_2 = allocator.allocate(); allocator.print();
	[[maybe_unused]] auto ptr_3 = allocator.allocate(); allocator.print(); // note: nullptr

	[[maybe_unused]] auto ptr_4 = allocator.allocate(); allocator.print(); // note: head Z

	allocator.deallocate(ptr_1);                        allocator.print(); // note: head X
	allocator.deallocate(ptr_2);                        allocator.print(); // note: head Y

	[[maybe_unused]] auto ptr_5 = allocator.allocate(); allocator.print(); // note: head X
	[[maybe_unused]] auto ptr_6 = allocator.allocate(); allocator.print(); // note: head Z

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}