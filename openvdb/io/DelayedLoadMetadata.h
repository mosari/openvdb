//
// TM & (c) Lucasfilm Entertainment Company Ltd. and Lucasfilm Ltd.
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
//

#ifndef OPENVDB_DELAYED_LOAD_METADATA_HAS_BEEN_INCLUDED
#define OPENVDB_DELAYED_LOAD_METADATA_HAS_BEEN_INCLUDED

#include <openvdb/Metadata.h>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>


namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
namespace io {

/// @brief Store a buffer of data that can be optionally used
/// during reading for faster delayed-load I/O performance
class DelayedLoadMetadata: public Metadata
{
public:
    using Ptr = SharedPtr<DelayedLoadMetadata>;
    using ConstPtr = SharedPtr<const DelayedLoadMetadata>;
    using MaskType = int8_t;
    using CompressedSizeType = int64_t;

    DelayedLoadMetadata() = default;
    DelayedLoadMetadata(const DelayedLoadMetadata& other);
    ~DelayedLoadMetadata() override = default;

    Name typeName() const override;
    Metadata::Ptr copy() const override;
    void copy(const Metadata&) override;
    std::string str() const override;
    bool asBool() const override;
    Index32 size() const override;

    static Name staticTypeName() { return "delayedload"; }

    static Metadata::Ptr createMetadata()
    {
        Metadata::Ptr ret(new DelayedLoadMetadata);
        return ret;
    }

    static void registerType()
    {
        Metadata::registerType(DelayedLoadMetadata::staticTypeName(),
                               DelayedLoadMetadata::createMetadata);
    }

    static void unregisterType()
    {
        Metadata::unregisterType(DelayedLoadMetadata::staticTypeName());
    }

    static bool isRegisteredType()
    {
        return Metadata::isRegisteredType(DelayedLoadMetadata::staticTypeName());
    }

    void clear();
    bool empty() const;

    void resizeMask(size_t size);
    void resizeCompressedSize(size_t size);

    MaskType getMask(size_t index) const;
    void setMask(size_t index, const MaskType& value);

    CompressedSizeType getCompressedSize(size_t index) const;
    void setCompressedSize(size_t index, const CompressedSizeType& value);

protected:
    void readValue(std::istream&, Index32 numBytes) override;
    void writeValue(std::ostream&) const override;

private:
    std::vector<MaskType> mMask;
    std::vector<CompressedSizeType> mCompressedSize;
};


} // namespace io
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_DELAYED_LOAD_METADATA_HAS_BEEN_INCLUDED
