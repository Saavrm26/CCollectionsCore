#ifndef CC_COMMON
#define CC_COMMON
enum CC_status {
	CC_ok                       = 0,
	CC_err_alloc                = 1,
	CC_err_max_capacity         = 2,
	CC_invalid_capacity         = 3,
	CC_invalid_expansion_factor = 4,
	CC_out_of_bounds            = 5,
	CC_underflow                = 6,
	CC_overflow                 = 7,
	CC_not_implemented          = 100
};

#define CC_MAX_ELEMENTS ((size_t)-2)
#endif // ! CC_COMMON
