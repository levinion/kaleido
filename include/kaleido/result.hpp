#pragma once
#include <cstdlib>
#include <expected>
#include <string>

namespace kaleido {

template<typename T>
using KaleidoResult = std::expected<T, std::string>;

#define kaleido_err(x) std::unexpected(x)

#define kaleido_check(x) \
  if (auto r = x; !r) \
    return kaleido_err(r.error());

} // namespace kaleido
