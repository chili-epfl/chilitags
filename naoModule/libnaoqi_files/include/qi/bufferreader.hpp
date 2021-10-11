#pragma once
/*
**  Copyright (C) 2012 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QI_BUFFERREADER_HPP_
#define _QI_BUFFERREADER_HPP_

#include <qi/buffer.hpp>

namespace qi {

  /// Class to read const buffer.
  class QI_API BufferReader
  {
  public:
    /// Constructor.
    explicit BufferReader(const Buffer& buf);
    /// Default destructor.
    ~BufferReader();
    /// read and store data from the buffer.
    size_t read(void *data, size_t length);

    /// read data from buffer.
    void  *read(size_t offset);
    /// Move forward the buffer cursor by the given offset.
    bool   seek(size_t offset);
    /// Check if we can read from the actual position toward \a offset bytes.
    void  *peek(size_t offset) const;

    /// Check if there is sub-buffer at the actual position.
    bool hasSubBuffer() const;
    /// return the sub-buffer at the actual position.
    const Buffer& subBuffer();
    /// return the actual position in the buffer.
    size_t position() const;

  private:
    Buffer _buffer;
    size_t _cursor;
    size_t _subCursor; // position in sub-buffers
  };
}

#endif  // _QI_BUFFERREADER_HPP_
