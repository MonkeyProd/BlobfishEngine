//
// Created by plasm on 14.07.2022.
//

#ifndef COMPOUND_BLOBPCH_H
#define COMPOUND_BLOBPCH_H

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <utility>
#include <unordered_map>
#include "Logger.h"
#include "KeyCodes.h"

#define BIT(x) (1 << x)
#define BF_ASSERT(predicate, ...) if(not predicate){BF_LOG_CRITICAL(__VA_ARGS__); std::terminate();}

#endif //COMPOUND_BLOBPCH_H
