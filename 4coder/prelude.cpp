//
// rosorio's prelude for all C++ shenanigans
//

#ifndef INCLUDED_PRELUDE
#define INCLUDED_PRELUDE





// # CONFIG FOR PRELUDE
//
#ifndef PRELUDE_USE_BLOCKS
#define PRELUDE_USE_BLOCKS (false)
#endif





// # FIND OUT WHERE WE ARE
//
// This should give us at least one of
//
// - WINDOWS
// - MAC
// - LINUX
// - Others I don't care about yet :)
//
#ifdef _WIN32
#    define WINDOWS 1
#    ifdef _WIN64
#        define WINDOWS_64 1
#    else
#        define WINDOWS_32 1
#    endif
#elif __APPLE__
#    include "TargetConditionals.h"
#    if TARGET_IPHONE_SIMULATOR
#        define IPHONE 1
#    elif TARGET_OS_IPHONE
#        define IPHONE 1
#    elif TARGET_OS_MAC
#        define MAC 1
#    else
#        error "Unknown Apple platform"
#    endif
#elif __linux__ && !__ANDROID__
#    define LINUX 1
#elif __unix__
#    define UNIX 1
#elif defined(_POSIX_VERSION)
#    define POSIX 1
#else
#    error "Unknown compiler"
#endif

// And what compiler are we using?
//
#ifdef __clang__
#    define CLANG 1
#elif __GNUC__
#    define GCC 1
#elif _MSC_VER
#    define MSVC 1
#endif





// # ATTRIBUTES

// force_inline
#if CLANG || GCC
#    define force_inline __attribute__((always_inline))
#else
#    define force_inline __forceinline
#endif





// # RENAMING KEYWORDS
#define procedure auto
#define internal static
#define global_variable static
#define persistent static





// # DEFER

#if __has_extension(blocks) && USE_BLOCKS

// Runs the block we pass in
force_inline
procedure _run_defer(void (^*b)()) -> void { (*b)(); }

// Dumb paste operator cause preprocessor :(
#define _defer_merge(a,b) a##b

// Makes a unique name for the variable holding the block
#define _defer_variable_name(a) \
_defer_merge(_defer_variable, a)

// Creates a block variable that will execute _run_defer at cleanup
#define defer __attribute__((cleanup(_run_defer))) \
void (^_defer_variable_name(__COUNTER__)) () = ^

#else // If we don't have block support we just use lambdas

#include <functional>

// Runs the lambda we pass in
force_inline
procedure _run_defer(std::function<void()>* proc) -> void { (*proc)(); }

// Dumb paste operator cause preprocessor :(
#define _defer_merge(a,b) a##b

// Makes a unique name for the variable holding the block
#define _defer_variable_name(a) \
_defer_merge(_defer_variable, a)

// Creates a lambda variable that will get executed
// through _run_defer at cleanup
#define defer __attribute__((cleanup(_run_defer))) \
std::function<void()> _defer_variable_name(__COUNTER__) = [&]()

#endif // Different defer implementations





// # MATH

typedef float float32 __attribute__((ext_vector_type(32)));
typedef float float16 __attribute__((ext_vector_type(16)));
typedef float float4 __attribute__((ext_vector_type(4)));
typedef float float3 __attribute__((ext_vector_type(3)));
typedef float float2 __attribute__((ext_vector_type(2)));





#endif // INCLUDED_PRELUDE