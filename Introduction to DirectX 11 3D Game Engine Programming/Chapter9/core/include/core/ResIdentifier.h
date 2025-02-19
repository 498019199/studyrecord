#pragma once

#include <istream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <vector>
#include <core/Util.h>

namespace RenderWorker
{


class ResIdentifier final
{
public:
    ResIdentifier(std::string_view name, uint64_t timestamp,
            std::shared_ptr<std::istream> const & is)
        : ResIdentifier(std::move(name), timestamp, is, std::shared_ptr<std::streambuf>())
    {
    }
    ResIdentifier(std::string_view name, uint64_t timestamp,
            std::shared_ptr<std::istream> const & is, std::shared_ptr<std::streambuf> const & streambuf)
        : res_name_(std::move(name)), timestamp_(timestamp), istream_(is), streambuf_(streambuf)
    {
        COMMON_ASSERT(istream_);
    }

    void ResName(std::string_view name)
    {
        res_name_ = std::string(name);
    }
    std::string const & ResName() const
    {
        return res_name_;
    }

    void Timestamp(uint64_t ts)
    {
        timestamp_ = ts;
    }
    uint64_t Timestamp() const
    {
        return timestamp_;
    }

    void read(void* p, size_t size)
    {
        istream_->read(static_cast<char*>(p), static_cast<std::streamsize>(size));
    }

    int64_t gcount() const
    {
        return static_cast<int64_t>(istream_->gcount());
    }

    void seekg(int64_t offset, std::ios_base::seekdir way)
    {
        istream_->seekg(static_cast<std::istream::off_type>(offset), way);
    }

    int64_t tellg()
    {
        return static_cast<int64_t>(istream_->tellg());
    }

    void clear()
    {
        istream_->clear();
    }

    operator bool() const
    {
        return !istream_->fail();
    }

    bool operator!() const
    {
        return istream_->operator!();
    }

    std::istream& input_stream()
    {
        return *istream_;
    }

private:
    std::string res_name_;
    uint64_t timestamp_;
    std::shared_ptr<std::istream> istream_;
    std::shared_ptr<std::streambuf> streambuf_;
};

using ResIdentifierPtr = std::shared_ptr<ResIdentifier>;


std::string ReadShortString(ResIdentifier& res)
{
    uint8_t len = 0;
    res.read(&len, sizeof(len));

    std::string tmp;
    if (len > 0)
    {
        tmp.resize(len);
        res.read(&tmp[0], len * sizeof(tmp[0]));
    }

    return tmp;
}

void WriteShortString(std::ostream& os, std::string_view str)
{
    uint8_t len = static_cast<uint8_t>(std::min(str.size(), static_cast<size_t>(255)));
    os.write(reinterpret_cast<char*>(&len), sizeof(len));

    if (len > 0)
    {
        os.write(str.data(), len * sizeof(str[0]));
    }
}
}