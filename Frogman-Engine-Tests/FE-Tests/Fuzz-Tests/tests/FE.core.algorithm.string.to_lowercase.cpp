// std
#include <string>
#include <cstring>

// test target
#include <FE/core/algorithm/string.hxx>


extern "C" int LLVMFuzzerTestOneInput(const char* data_p, _MAYBE_UNUSED_ long long size_p)
{
    std::string l_buffer = data_p;

    FE::algorithm::string::to_lowercase(l_buffer.data());

    return 0;
}