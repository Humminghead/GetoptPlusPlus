#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace GetOptPlusPlus {

struct Option;

class ConsoleOptionsHandler {
public:
  using HandlerT = typename std::function<void(const char *)>;
  using HandlerKeyStoreT =
      typename std::unordered_map<Option, HandlerT>;

  ConsoleOptionsHandler(int argc, char **argv);
  ConsoleOptionsHandler(int argc, char **argv, const HandlerKeyStoreT &store);
  ConsoleOptionsHandler(int argc, char **argv, HandlerKeyStoreT &&store);

  void ProcessCmdLine() noexcept;
  bool ProcessCmdLine(size_t toBeProcCnt) noexcept;
  bool AddKey(const Option &key, HandlerT &&value) noexcept;
  size_t HandlersCount() noexcept;

private:
  bool ProcessArgument(size_t &pos, Option &opt) noexcept;
  void FillLine(int argc, char **argv) noexcept;

  struct Impl;
  std::unique_ptr<Impl, void (*)(Impl *)> m_Impl;
};
} // namespace GetOptPlusPlus
