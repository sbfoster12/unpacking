#ifndef WAVEFORM_HH 
#define WAVEFORM_HH

#include "DataProduct.hh"

namespace dataProducts {

    class Waveform : public DataProduct {

        public:
            Waveform();

            Waveform(int crateNum
                ,int amcNum
                ,int channelTag
                ,int eventNum
                ,unsigned int length
                ,int pedestalLevel
                ,std::vector<short> trace
            );

            //Destructor
            ~Waveform();

            // Crate number
            int crateNum;

            // AMC slot number
            int amcNum;

            // Channel tag
            int channelTag;

            // Event number
            int eventNum;

            // Number of samples in the waveform
            unsigned int length;

            // ADC count of pedestal level
            int pedestalLevel;

            // ADC count of each sample
            std::vector<short> trace;

            void Show() const override;

            ClassDefOverride(Waveform,1)

    };

    typedef std::vector<Waveform> WaveformCollection;

}

#endif // WAVEFORM_HH