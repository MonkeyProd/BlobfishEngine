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
#include "Logger.h"
#include "KeyCodes.h"

#define BIT(x) (1 << x)
#define BLOB_ASSERT(predicate, ...) if(not predicate){BLOB_LOG_CRITICAL(__VA_ARGS__); std::terminate();}

#endif //COMPOUND_BLOBPCH_H
