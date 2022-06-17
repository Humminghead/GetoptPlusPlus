#include "ConsoleKeyOption.h"
#include <ConsoleOptionsHandler.h>

namespace GetOptPlusPlus {

struct ConsoleOptionsHandler::Impl {
  ConsoleOptionsHandler::HandlerKeyStoreT keys_;
  std::string line_;
};

ConsoleOptionsHandler::ConsoleOptionsHandler(int argc, char **argv)
    : m_Impl(new Impl(), [](Impl *p) { delete p; }) {
  FillLine(argc, argv);
}

ConsoleOptionsHandler::ConsoleOptionsHandler(
    int argc, char **argv, const HandlerKeyStoreT &keyHandlerMap)
    : m_Impl(new Impl(), [](Impl *p) { delete p; }) {
  m_Impl->keys_ = keyHandlerMap;
  FillLine(argc, argv);
}

ConsoleOptionsHandler::ConsoleOptionsHandler(int argc, char **argv,
                                             HandlerKeyStoreT &&keyHandlerMap)
    : m_Impl(new Impl(), [](Impl *p) { delete p; }) {
  m_Impl->keys_ = std::move(keyHandlerMap);
  FillLine(argc, argv);
}

void ConsoleOptionsHandler::ProcessCmdLine() noexcept {
  this->ProcessCmdLine(0);
}

bool ConsoleOptionsHandler::ProcessCmdLine(size_t toBeProcCnt) noexcept {
  size_t processedArgs{0};

  if (auto pos = m_Impl->line_.find_first_of("-"); std::string::npos != pos) {
    for (Option opt; this->ProcessArgument(pos, opt);) {
      processedArgs++;
      opt.reset();
    }
  }

  return processedArgs;
}

bool ConsoleOptionsHandler::AddKey(const Option &key,
                                   HandlerT &&value) noexcept {
  Option tOpt;

  tOpt.flag = key.flag;
  tOpt.has_arg = key.has_arg;
  tOpt.name = nullptr;

  auto res0 = m_Impl->keys_.emplace(tOpt, value);

  tOpt.flag = nullptr;
  tOpt.has_arg = key.has_arg;
  tOpt.name = key.name;

  auto res1 = m_Impl->keys_.emplace(tOpt, value);

  return res0.second && res1.second;
}

size_t ConsoleOptionsHandler::HandlersCount() noexcept {
  return m_Impl->keys_.size();
}

bool ConsoleOptionsHandler::ProcessArgument(size_t &pos, Option &opt) noexcept {
  if (m_Impl->line_.length() <= pos)
    return false;

  if ('-' == m_Impl->line_[pos + 1]) {
    pos += 2;
    auto optName = std::string_view(&m_Impl->line_[pos]);
    opt.name = optName.data();
    pos += optName.length();
    pos++;
  } else {
    opt.flag = std::string_view(&m_Impl->line_[++pos]).data();
    pos += 2;
  }

  if (auto it = m_Impl->keys_.find(opt); std::end(m_Impl->keys_) != it) {
    if (auto handler = it->second; it->first.has_arg) {
      if (handler) {
        std::string_view value(&m_Impl->line_[pos]);
        handler(value.data());
        pos += value.length();
        pos++;
        return true;
      }
    } else {
      if (handler) {
        handler(nullptr);
        return true;
      }
    }
  }

  return false;
}

void ConsoleOptionsHandler::FillLine(int argc, char **argv) noexcept {
  for (int n = 0; n < argc; n++) {
    m_Impl->line_.append(argv[n]).append(" ");
    m_Impl->line_.back() = 0x00;
  }
}
} // namespace GetOptPlusPlus
