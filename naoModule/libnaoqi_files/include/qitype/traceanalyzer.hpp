#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_TRACEANALYZER_HPP_
#define _QITYPE_TRACEANALYZER_HPP_

#include <boost/utility.hpp>

#include <qitype/manageable.hpp>


namespace qi
{
  class TraceAnalyzerImpl;

  class QITYPE_API TraceAnalyzer: public boost::noncopyable
  {
  public:
    TraceAnalyzer();
    ~TraceAnalyzer();
    /// Clear all traces
    void clear();
    /// Clear traces older than limit. Can loose dataflow informations.
    void clear(const qi::os::timeval& limit);
    /// Add a new trace to the system. There is no order requirement between traces.
    void addTrace(const qi::EventTrace& e, unsigned int objectId);
    struct FlowLink
    {
      FlowLink(unsigned int srcObj, unsigned int srcFun, unsigned int dstObj, unsigned int dstFun, bool sync)
      : srcObj(srcObj), srcFun(srcFun), dstObj(dstObj), dstFun(dstFun), sync(sync) {}
      unsigned int srcObj, srcFun, dstObj, dstFun;
      bool sync;
    };
    /// Append the set of discovered links between traces to \p links
    void analyze(std::set<FlowLink>& links);
    /// Debug-dump the internal structures to given ostream
    void dumpTraces(std::ostream& o);
    std::string dumpTraces();
  protected:
    TraceAnalyzerImpl* _p;
  };
}


namespace qi
{
  inline bool operator < (const TraceAnalyzer::FlowLink& a, const TraceAnalyzer::FlowLink& b)
  {
    #define _qi_FIELD(f) if (a.f != b.f) return a.f < b.f
    _qi_FIELD(srcObj);
    _qi_FIELD(srcFun);
    _qi_FIELD(dstObj);
    _qi_FIELD(dstFun);
    _qi_FIELD(sync);
    return false;
    #undef _qi_FIELD
  }
}

#endif
