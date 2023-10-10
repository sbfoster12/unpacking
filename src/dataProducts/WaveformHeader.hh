#ifndef WAVEFORMHEADER_HH   
#define WAVEFORMHEADER_HH

#include "DataProduct.hh"

namespace dataProducts {

    class WaveformHeader : public DataProduct {

        public:
            WaveformHeader();

            WaveformHeader(unsigned int crateNumArg
                ,unsigned int amcNumArg
                ,unsigned int waveformCountArg
                ,unsigned int waveformGapArg
                ,unsigned int channelTagArg
                ,unsigned int waveformIndexArg
                ,unsigned int fillTypeArg
                ,unsigned int waveformLengthArg
                ,unsigned int DDR3AddressArg
            );

            //Destructor
            ~WaveformHeader();

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

            // 12 bit Waveform Index
            unsigned int waveformIndex;

            // 3 bit Fill Type
            unsigned int fillType;

            // 23 bit Waveform Length
            unsigned int waveformLength;

            // 25 bit DDR3 start address
            unsigned int DDR3Address;

            void Show() const override;

            ClassDefOverride(WaveformHeader,1)

    };

    typedef std::vector<WaveformHeader> WaveformHeaderCollection;

}

#endif // WAVEFORMHEADER_HH