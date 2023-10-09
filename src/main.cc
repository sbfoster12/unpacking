/*

This main function provides an example for unpacking a midas event
using the BasicEventUnpacker. The reader a GetCollection method to
access the unpacked data

*/

//Standard
#include <iostream>
#include <memory>

//ROOT
#include <TFile.h>
#include <TTree.h>

//Custom
#include "unpackers/BasicEventUnpacker.hh"
#include "unpackers/UnpackerHelpers.hh"
#include "dataProducts/Waveform.hh"

int main(int argc, char* argv[]) {

    // Get the input file

    // We need two arguments (program and file name)
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [file_name]" << std::endl;
        return 1;
    }

    // The first command-line argument (argv[1]) is the file name
    std::string file_name = argv[1];


    // Set up an event unpacker object
    // This object contains the methods for
    // doing the unpacking of a TMEvent

    auto basicEventUnpacker = new unpackers::BasicEventUnpacker();

    // We need to get a midas event
    TMReaderInterface* mReader = TMNewReader(file_name.c_str());

    //loop over the events
    while (true) {
        TMEvent* thisEvent = TMReadEvent(mReader);
        if (!thisEvent) {
            //Reached end of the file. Clean up and break
            delete thisEvent;
            thisEvent = NULL;
            break;
        }

        std::cout << "event_id: " << thisEvent->event_id << ", serial number: " << thisEvent->serial_number << std::endl;

        // Skip event if it is an internal midas event
        if (unpackers::IsHeaderEvent(thisEvent)) {
            //clean up
            delete thisEvent;
            continue;
        }

        int event_id = thisEvent->event_id;

        //only unpack events with id 1
        if (event_id == 1) {
            // Unpack the event
            // This will fill the dataproduct collections 
            basicEventUnpacker->UnpackEvent(thisEvent);

            //We can get the collections
            auto cols = basicEventUnpacker->GetCollections();
            for (const auto & col : cols) { 
                std::cout << "  Collection " << col.first << " has size = " << col.second->size() << std::endl;
            }

            // We can also get particular collections (this makes a copy)
            auto wavefromCollection = basicEventUnpacker->GetCollection<dataProducts::Waveform>("WaveformCollection");

            //Now do can something with these waveforms
            if (wavefromCollection.size() != 0) {
                for (const auto& waveform : wavefromCollection) {
                    std::cout << "      This waveform has a trace length = " << waveform.trace.size() << std::endl;
                    // for (const auto& sample : waveform.trace) {
                    //     std::cout << sample << ",";
                    // }
                    // std::cout << std::endl;
                }
            }
        }

        //clean up
        delete thisEvent;
    }

    //clean up
    delete basicEventUnpacker;
    delete mReader;

    return 0;
}