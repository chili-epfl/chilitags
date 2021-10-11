#pragma once
/*
**  Copyright (C) 2012 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QI_BUFFER_HPP_
#define _QI_BUFFER_HPP_

# include <qi/api.hpp>
# include <qi/types.hpp>
# include <boost/shared_ptr.hpp>
# include <vector>
# include <cstddef>

#ifdef _MSC_VER
#  pragma warning( push )
#  pragma warning( disable: 4251 )
#endif

namespace qi
{
  class BufferPrivate;

  /// Class to store buffer.
  class QI_API Buffer
  {
  public:
    /// Default constructor.
    Buffer();
    ///  Copy constructor.
    Buffer(const Buffer& b);
    /// Assignment operator.
    Buffer& operator = (const Buffer& b);

    /// Write data in the buffer.
    bool write(const void *data, size_t size);

    /// Add a sub-buffer to the main buffer.
    size_t addSubBuffer(const Buffer& buffer);
    /// Check if there is a sub-buffer at given offset.
    bool   hasSubBuffer(size_t offset) const;
    /// Return the sub-buffer at given offset.
    const  Buffer& subBuffer(size_t offset) const;

    /// Return the content size of this buffer not counting sub-buffers.
    size_t size() const;
    /// Return the content size of this buffer and of all its sub-buffers.
    size_t totalSize() const;

    /// Return a vector of sub-buffers of the current buffer.
    const std::vector<std::pair<size_t, Buffer> >& subBuffers() const;

    /// Reserve bytes at the end of current buffer.
    void* reserve(size_t size);
    /// Erase content of buffer and remove sub-buffers whithout clearing them.
    void  clear();

    /// Return a pointer to the raw data storage of this buffer.
    void* data();
    /// Return a const pointer to the raw data in this buffer.
    const void* data() const;

    /// Read some data from the buffer.
    const void* read(size_t offset = 0, size_t length = 0) const;
    /// Read some data in the buffer and store it in a new pre-allocated buffer.
    size_t read(void* buffer, size_t offset = 0, size_t length = 0) const;

  private:
    friend class BufferReader;
    // CS4251
    boost::shared_ptr<BufferPrivate> _p;
  };

  namespace details {
    QI_API void printBuffer(std::ostream& stream, const Buffer& buffer);
  }
}

#ifdef _MSC_VER
#  pragma warning( pop )
#endif

#endif  // _QI_BUFFER_HPP_
