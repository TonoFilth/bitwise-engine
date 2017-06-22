#if !defined(BW_DOXYPRESS)
#pragma once

namespace bw
{
// -------------------------------------------------------------------------
//  Forward declarations
// -------------------------------------------------------------------------
struct StackFrame;

// -------------------------------------------------------------------------
//  Internal namespace
// -------------------------------------------------------------------------
namespace internal
{
namespace assert
{
    // Defined in "bitwise/core/platform/<platform>_assert.cpp"
    void default_handler(const char* expression, const char* message, const char* file, int line, bool callstack, bool halt);
}
namespace callstack
{
    // Defined in "bitwise/core/callstack.cpp"
    size_t default_formatter(StackFrame& stackFrame, char* buffer, size_t bufferSize);
}
namespace core
{
    // Defined in "bitwise/core.cpp"
    void initialize(int argc, char** argv);
    void shutdown();
}
namespace system
{
    // Defined in "bitwise/core/platform/<platform>_system.cpp"
    void initialize(int argc, char** argv);
    void shutdown();

    #if defined(BW_PLATFORM_WINDOWS)
    // Defined in "bitwise/core/windows/system.cpp"
    const char* get_last_error_message();
    #endif
}
}   // namespace internal
}   // namespace bw

#endif