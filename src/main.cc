/*

This main function provides an example for unpacking a midas event
using the BasicEventUnpacker. The reader a GetCollection method to
access the unpacked data

*/

//Standard
#include <iostream>
#include <memory>
#include <fstream>

//ROOT
#include <TFile.h>
#include <TTree.h>
#include <TBufferJSON.h>

//Custom
#include "unpackers/BasicEventUnpacker.hh"
#include "unpackers/UnpackerHelpers.hh"
#include "dataProducts/Waveform.hh"
#include "unpackers/utils/Logger.hh"
#include "serializer/Serializer.hh"

int main(int argc, char* argv[]) {

    TFile* outfile = new TFile("unpacked.root","RECREATE");
    TTree* tree = new TTree("tree","tree");
    dataProducts::WaveformCollection waveforms;
    tree->Branch("waveforms",&waveforms);

    std::ofstream unpackedFile;
    unpackedFile.open ("unpacked_data.txt");

    // We need three arguments (program, file name, verbosity) detector mapping is optional
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [file_name] [verbosity] [detector_mapping]" << std::endl;
        return 1;
    }

    // The first command-line argument (argv[1]) is the file name
    std::string file_name = argv[1];
    // Set verbosity
    int verbosity = std::stoi(argv[2]);
    utils::LoggerHolder::getInstance()->SetVerbosity(verbosity);
    //detector mapping
    std::string detectorMappingFile = "/Users/sbfoster/docker/mount/pioneer/unpacking/python/detector_mapping.json";
    if (argc == 4) { detectorMappingFile = argv[3]; }


    // Set up the serializer for packaging up the event
    auto serializer = std::make_unique<unpackers::Serializer>(detectorMappingFile,0,0,0);
    // serializer->SetRun(0);
    // serializer->SetSubRun(0);
    // serializer->SetEvent(0);

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
            break;
        }

        std::cout << "event_id: " << thisEvent->event_id << ", serial number: " << thisEvent->serial_number << std::endl;
        serializer->SetEvent(thisEvent->serial_number);

        // Skip event if it is an internal midas event
        if (unpackers::IsHeaderEvent(thisEvent)) {
            // std::cout << std::hex << thisEvent->event_id << std::dec << std::endl;

            // We can get the ODB here:
            // std::string charString(thisEvent->data.begin()+thisEvent->event_header_size, thisEvent->data.end());
            // const char* filename = "output.txt";

            // // Open a file for writing
            // std::ofstream outputFile(filename);

            // if (outputFile.is_open()) {
            //     outputFile << charString;

            //     // Close the file
            //     outputFile.close();
            //     std::cout << "Data written to " << filename << std::endl;
            // } else {
            //     std::cerr << "Failed to open " << filename << " for writing." << std::endl;
            // }

            // exit(1);

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

            // //We can get the collections
            // auto cols = basicEventUnpacker->GetCollections();
            // for (const auto & col : cols) {
            //     std::cout << "  Collection " << col.first << " has size = " << col.second->size() << std::endl;
            // }

            // We can also get particular collections (this makes a copy)
            waveforms = basicEventUnpacker->GetCollection<dataProducts::Waveform>("WaveformCollection");

            // TBufferJSON serializer;
            // TString json = serializer.ToJSON(&waveformCollection,3);

            //Serialize
            //serializer->SetWaveforms(waveformCollection);
            //std::cout <<serializer->GetString() << std::endl;
            //unpackedFile << json.Data() << "\n";

        }

        tree->Fill();

        //clean up
        delete thisEvent;
    }

    //clean up
    delete basicEventUnpacker;
    delete mReader;

    tree->Write();
    outfile->Close();

    unpackedFile.close();

    return 0;
}