#ifndef BLOBPCH_H
#define BLOBPCH_H

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <utility>
#include <unordered_map>
#include "Logger.h"
#include "KeyCodes.h"
#include <Tracy.hpp>

#define BIT(x) (1 << x)
#define BF_ASSERT(predicate, ...) if(not (predicate)){BF_LOG_CRITICAL(__VA_ARGS__); std::terminate();}

#define BLOB_BIND(cls, func) std::bind(& cls::func, this, std::placeholders::_1)

#endif //BLOBPCH_H
