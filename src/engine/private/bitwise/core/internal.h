#if !defined(BW_DOXYPRESS)
#pragma once

namespace bw
{
namespace core
{
    // -------------------------------------------------------------------------
    //  Internal functions
    // -------------------------------------------------------------------------
    void initialize(int argc, char** argv);
    void shutdown();

}   // namespace core

struct StackFrame;

namespace internal
{
    // -------------------------------------------------------------------------
    //  Internal functions
    // -------------------------------------------------------------------------
    void default_assert_handler(const char* expression, const char* message, const char* file, int line, bool callstack, bool halt);
    size_t default_stack_frame_formatter(StackFrame& stackFrame, char* buffer, size_t bufferSize);

}   // namespace internal
}   // namespace bw

#endif