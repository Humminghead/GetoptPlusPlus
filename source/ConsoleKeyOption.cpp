#include "GetOptPP/ConsoleKeyOption.h"
#include <string_view>
#include <string>

namespace GetOptPlusPlus {
void Option::reset() {
  this->name = nullptr;
  this->flag = nullptr;
  this->has_arg = 0;
}

bool operator==(const Option &o0, const Option &o1)
{
    bool flagsEq = (o0.flag && o1.flag) ? *o0.flag == *o1.flag : true;
    bool namesEq = (o0.name && o1.name) ? std::string_view(o0.name)==std::string_view(o1.name) : true;
    return flagsEq && namesEq;
}

} // namespace GetOptPlusPlus

std::size_t std::hash<GetOptPlusPlus::Option>::operator()(const GetOptPlusPlus::Option &s) const noexcept {
    if (s.name == nullptr)
        return std::hash<int>{}(*s.flag);

    if (s.flag == nullptr)
        return std::hash<std::string>{}(s.name);

    std::size_t h1 = std::hash<std::string>{}(s.name);
    std::size_t h2 = std::hash<int>{}(*s.flag);
    return h1 ^ (h2 << 1);
}
