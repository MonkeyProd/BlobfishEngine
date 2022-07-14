//
// Created by plasm on 14.07.2022.
//

#ifndef COMPOUND_LOGGER_H
#define COMPOUND_LOGGER_H

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#ifndef NDEBUG
#define BLOB_LOG_TRACE(...) spdlog::trace(__VA_ARGS__)
#define BLOB_LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define BLOB_LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define BLOB_LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define BLOB_LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define BLOB_LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)
#else
#define BLOB_LOG_TRACE(...)
#define BLOB_LOG_DEBUG(...)
#define BLOB_LOG_INFO(...)
#define BLOB_LOG_WARN(...)
#define BLOB_LOG_ERROR(...)
#define BLOB_LOG_CRITICAL(...)
#endif

#endif //COMPOUND_LOGGER_H
