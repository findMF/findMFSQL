#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <string>

namespace ralab{
  namespace findmf{
    namespace dto{
      //dto to tansfer instrument information.

      /// transfers sample properties such as
      struct SampleDescript{
        std::string  name;
        std::string description;
        std::string file;
      };

      struct Instrument{
        std::string manufacturer;
        std::string model;
        std::string ionisation;
        std::string analyser;
        std::string detector;
      };

      struct Params{
        uint32_t nrthreads;
        double ppm; // with of mz bins in ppms
        double resolution;
        double mzscale;
        double rtscale;
        uint32_t rtpixelwidth; // in pixel
        uint32_t mzpixelwidth; // in pixel
        double minmass; // minimal mass to consider
        double maxmass; // maximum mass to consider
        double minintensity;
        uint32_t rt2sum; //how many spectra to sum (downsampling)
      };


    }

  }
}
#endif
