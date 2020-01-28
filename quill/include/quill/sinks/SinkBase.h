#pragma once

#include "fmt/format.h"
#include "quill/detail/PatternFormatter.h"
#include "quill/detail/record/RecordBase.h"
#include "quill/detail/record/StaticLogRecordInfo.h"

namespace quill
{

/**
 * Base class for sinks
 */
class SinkBase
{
public:
  /**
   * Constructor
   * Uses the default pattern formatter
   */
  SinkBase() = default;

  /**
   * Clone
   * @return
   */
  [[nodiscard]] virtual SinkBase* clone() const = 0;

  /**
   * Constructor
   * Uses a custom formatter
   * @tparam TConstantString
   * @param format_pattern
   */
  template <typename TConstantString>
  explicit SinkBase(TConstantString format_pattern) : _formatter(format_pattern){};

  /**
   * Copy Constructor
   */
  SinkBase(SinkBase const& other) = default;

  /**
   * Move Constructor
   */
  SinkBase(SinkBase&& other) noexcept = default;

  /**
   * Copy Assignment
   * @return
   */
  SinkBase& operator=(SinkBase const& other) = default;

  /**
   * Move Assignment
   * @return
   */
  SinkBase& operator=(SinkBase&& other) noexcept = default;

  /**
   * Destructor
   */
  virtual ~SinkBase() = default;

  /**
   * Returns the owned formatter by the sink
   * @note: Accessor for backend processing
   * @return
   */
  detail::PatternFormatter const& formatter() { return _formatter; }

  /**
   * Logs a formatted log record to the sink
   * @note: Accessor for backend processing
   * @param formatted_log_record
   */
  virtual void log(fmt::memory_buffer const& formatted_log_record) = 0;

  /**
   * Flush the sink synchronising the associated sink with its controlled output sequence.
   */
  virtual void flush() = 0;

private:
  detail::PatternFormatter _formatter; /**< Owned formatter for this sink */
};

} // namespace quill