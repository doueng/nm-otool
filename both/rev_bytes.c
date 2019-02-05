#include "nm_otool.h"


uint32_t			rev_bytes32(uint32_t bytes)
{
	return ((bytes << 24)
	| ((bytes << 8) & 0x00ff0000)
	| ((bytes >> 8) & 0x0000ff00)
	| (bytes >> 24));
}

uint64_t			rev_bytes64(uint64_t bytes)
{
	uint64_t res;

	res = 0;
	return ((res | rev_bytes32(bytes >> 32))
		| ((res | rev_bytes32((bytes << 32) >> 32)) << 32));
}

uint64_t			rev_bytes(t_env *env, uint64_t bytes)
{
	if (env->rev_bytes && !env->is_64)
		return (rev_bytes32(bytes));
	else if (env->rev_bytes && env->is_64)
		return (rev_bytes64(bytes));
	return (bytes);
}

