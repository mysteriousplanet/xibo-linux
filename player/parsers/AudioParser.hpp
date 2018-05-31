#include "constants.hpp"
#include "parsers/MediaParser.hpp"
#include <memory>

class Media;

class AudioParser : public MediaParser
{
public:
    AudioParser(const xlf_node& attrs, const xlf_node& options);
    std::unique_ptr<Media> parse() override;

private:
    const xlf_node& m_attrs;
    const xlf_node& m_options;

};
