#include "GetOptPP/ConsoleKeyOption.h"
#include "GetOptPP/ConsoleOptionsHandler.h"

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

  return processedArgs == toBeProcCnt;
}

bool ConsoleOptionsHandler::AddKey(const Option &key,
                                   HandlerT &&value) noexcept {

  bool nAdd{false}, kAdd{false};
  if (key.flag) {
    kAdd = m_Impl->keys_.try_emplace(Option{nullptr, key.flag, key.has_arg}, value)
        .second;
  }
  if (key.name) {
    nAdd = m_Impl->keys_.try_emplace(Option{key.name, nullptr, key.has_arg}, value)
        .second;
  }

  return kAdd || nAdd;
}

size_t ConsoleOptionsHandler::HandlersCount() noexcept {
    return (m_Impl->keys_.size() > 0) ? (m_Impl->keys_.size() / 2) : 0;
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
    if (auto flag = std::string_view(&m_Impl->line_[pos]);
        flag.front() != '-') {
      return false;
    } else {
      opt.flag = flag.substr(1, flag.size()).data();
      pos += 3;
    }
  }

  if (auto it = m_Impl->keys_.find(opt); std::end(m_Impl->keys_) != it) {
    if (auto handler = it->second; it->first.has_arg) {
      if (handler) {
        std::string_view value(&m_Impl->line_[pos]);
        if(value.empty()) return false;
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
  for (int n = 1; n < argc; n++) {//Skip execution path
    m_Impl->line_.append(argv[n]).append(" ");
    m_Impl->line_.back() = 0x00;
  }
}
} // namespace GetOptPlusPlus
