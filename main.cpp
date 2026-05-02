#include "bigint.hpp"

// 修正前(stoull使用時)にオーバーフロー/例外が発生するケースを検証する関数
// ULLONG_MAX = 18446744073709551615 (20桁) を超える演算はstoullで壊れる
void	test_overflow_cases(void)
{
	std::cout << "=== Large number tests (would overflow with old stoull) ===" << std::endl;

	// operator+: ULLONG_MAX + 1 → 18446744073709551616 (stoullでオーバーフロー)
	bigint	a(18446744073709551615ULL);
	bigint	b(1ULL);
	std::cout << "ULLONG_MAX         = " << a << std::endl;
	std::cout << "ULLONG_MAX + 1     = " << (a + b) << std::endl; // 期待値: 18446744073709551616

	// operator+: 巨大数同士の加算
	std::cout << "ULLONG_MAX * 2     = " << (a + a) << std::endl; // 期待値: 36893488147419103230

	// operator<<: 1を25桁シフト → 26桁の数 (stoullでオーバーフロー)
	bigint	c(1ULL);
	std::cout << "1 << 25 (digits)   = " << (c << 25) << std::endl; // 期待値: 1 + 25個の0

	// operator>>: 巨大数に右シフト (stoullに渡す前段階で大きい文字列が生まれる)
	bigint	d = a + a; // 36893488147419103230
	std::cout << "(ULLONG_MAX*2) >> 5 = " << (d >> 5) << std::endl; // 期待値: 368934881474191
}

// clear && c++ -g main.cpp bigint.cpp bigint.hpp && valgrind --leak-check=full --show-leak-kinds=all ./a.out
int	main(void)
{
	{
		const bigint	a(42);
		bigint			b(21), c, d(1337), e(d);
		
		//All are in base10
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
		std::cout << d << std::endl;
		std::cout << e << std::endl;
		std::cout << "a + b = " << a + b << std::endl; // a + b = 63
		std::cout << "(c += a) = " << (c += a) << std::endl; // c = 42, donc (c += a) = 42
		
		std::cout << "\n\n" << std::endl;
		std::cout << "b = " << b << std::endl;
		std::cout << "++b = " << ++b << std::endl;
		std::cout << "b++ = " << b++ << std::endl;
		std::cout << "b = " << b << std::endl;
		int	i = 0;//checking**
		std::cout << "i = " << i << std::endl;
		std::cout << "++i = " << ++i << std::endl;
		std::cout << "i++ = " << i++ << std::endl;
		std::cout << "i = " << i << std::endl;

		std::cout << "\n\n" << std::endl;
		std::cout << "\"((b << 10) + 42)\" = " << ((b << 10) + 42) << std::endl;
		std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
		std::cout << "(d >>= 2) = " << (d >>= 2) << std::endl;
		std::cout << "a = " << a << std::endl;
		std::cout << "d = " << d << std::endl;
		std::cout << "(d < a) = " << (d < a) << std::endl;
		std::cout << "(d > a) = " << (d > a) << std::endl;
		std::cout << "(d == a) = " << (d == a) << std::endl;
		std::cout << "(d != a) = " << (d != a) << std::endl;
		std::cout << "(d == a) = " << (d == d) << std::endl;
		std::cout << "(d <= a) = " << (d <= a) << std::endl;
		std::cout << "(d >= a) = " << (d >= a) << std::endl;

		bigint x(1234);
		std::cout << std::endl;
		std::cout << "\"(x << 2)\"--> " << (x << 2) << "\n";   // prints 123400
		std::cout << "\"(x >>= 2)\"--> " << (x >>= 2) << "\n";   // prints   12}
	}
	std::cout << "\n\n" << std::endl;
	test_overflow_cases();
	return (0);
} 