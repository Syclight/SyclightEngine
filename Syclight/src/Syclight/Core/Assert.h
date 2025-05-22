#pragma once

#include "Syclight/core/base.h"
#include "Syclight/core/log.h"
#include <filesystem>

#ifdef SYC_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define SYC_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { SYC##type##ERROR(msg, __VA_ARGS__); SYC_DEBUGBREAK(); } }
#define SYC_INTERNAL_ASSERT_WITH_MSG(type, check, ...) SYC_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define SYC_INTERNAL_ASSERT_NO_MSG(type, check) SYC_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", SYC_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define SYC_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define SYC_INTERNAL_ASSERT_GET_MACRO(...) SYC_EXPAND_MACRO( SYC_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, SYC_INTERNAL_ASSERT_WITH_MSG, SYC_INTERNAL_ASSERT_NO_MSG) )

// 至少接受该条件和一个可选的附加参数（消息）
#define SYC_ASSERT(...) SYC_EXPAND_MACRO( SYC_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define SYC_CORE_ASSERT(...) SYC_EXPAND_MACRO( SYC_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define SYC_ASSERT(...)
#define SYC_CORE_ASSERT(...)
#endif