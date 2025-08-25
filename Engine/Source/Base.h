#pragma once

#define CE_PLATFORM_NONE 0
#define CE_PLATFORM_LINUX 1
#define CE_PLATFORM_WIN 2
#define CE_PLATFORM_MAC 3
#define CE_PLATFORM_ANDROID 4

// ───── Detect platform ─────
#if defined(_WIN32) || defined(_WIN64)
#define CE_PLATFORM CE_PLATFORM_WIN
#elif defined(__linux__)
#define CE_PLATFORM CE_PLATFORM_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
#define CE_PLATFORM CE_PLATFORM_MAC
#elif defined(__ANDROID__)
#define CE_PLATFORM CE_PLATFORM_ANDROID
#else
#define CE_PLATFORM CE_PLATFORM_NONE
#endif

#if CE_PLATFORM == CE_PLATFORM_WIN
#define CE_API __declspec(dllexport)
#elif CE_PLATFORM == CE_PLATFORM_LINUX
#define CE_API __attribute__((visibility("default")))
#endif
