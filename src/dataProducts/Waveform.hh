#ifndef WAVEFORM_HH 
#define WAVEFORM_HH

#include "DataProduct.hh"

namespace dataProducts {

    class Waveform : public DataProduct {

        public:
            Waveform();

            //Destructor
            ~Waveform();

            // Crate number
            int crateNum;

            // AMC slot number
            int amcSlot;

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

            void PrintMembers() const override;

            ClassDefOverride(Waveform,1)

    };

    typedef std::vector<Waveform> WaveformCollection;

}

#endif // WAVEFORM_HH