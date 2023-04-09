#include <cstddef>

namespace math
{
long Fibo(int n);
double Sin(double d);
double Cos(double d);
} // namespace math

namespace fibonacci
{
long lookuptable[0x100];
long Fibo(int n);

namespace altversion
{
long Fibo(size_t n);
} // namespace altversion

} // namespace fibonacci

namespace math
{
double Tan(double d);
}

void A()
{
	size_t n = 3;
	// Fibo(n);
	math::Sin(3.14);
	math::Cos(3.14);
}

using namespace math;
using namespace fibonacci;
namespace alt = fibonacci::altversion;

void B()
{
	size_t n = 3;
	alt::Fibo(n);
	// Fibo(n);
	Cos(n);
}
