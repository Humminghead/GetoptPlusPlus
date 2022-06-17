#pragma once

#include <functional>

namespace GetOptPlusPlus {

struct Option {
  const char *name{nullptr};
  const char *flag{nullptr};
  int has_arg{0};

  void reset();
};

bool operator==(const Option &o0, const Option &o1);
} // namespace GetOptPlusPlus

template<>
struct std::hash<GetOptPlusPlus::Option>
{
    std::size_t operator()(GetOptPlusPlus::Option const& s) const noexcept;
};

