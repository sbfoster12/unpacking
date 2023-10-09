#ifndef CHANNELHEADER_HH    
#define CHANNELHEADER_HH

#include "DataProduct.hh"

namespace dataProducts {

    class ChannelHeader : public DataProduct {

        public:
            ChannelHeader();

            //Destructor
            ~ChannelHeader();

            //member variables

            // associated crate
            unsigned int crateNum;

            // associated slot
            unsigned int amcNum;

            // 12 bit Waveform Count
            unsigned int waveformCount;

            // 22 bit Waveform Gap
            unsigned int waveformGap;

            // 16 bit Channel Tag
            unsigned int channelTag;

            // 24 bit Trigger Number
            unsigned int triggerNum;

            // 3 bit Fill Type
            unsigned int fillType;

            // 23 bit Waveform Length
            unsigned int waveformLength;

            // 25 bit DDR3 start address
            unsigned int DDR3Address;

            // whether data integrity check passed
            bool passedIntegrityCheck;

            void Show() const override;

            ClassDefOverride(ChannelHeader,1)
    };

    typedef std::vector<ChannelHeader> ChannelHeaderCollection;

}

#endif // CHANNELHEADER_HH