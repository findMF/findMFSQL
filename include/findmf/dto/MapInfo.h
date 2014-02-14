#ifndef MAPINFO_H
#define MAPINFO_H

#include <string>
#include <vector>

namespace ralab{
  namespace findmf{
    namespace dto{
      //dto to tansfer instrument information.
      struct MapInfo{
        uint32_t sampleid;//!< foreign key to sample id
        uint32_t scancount;//!< number of spectra in map
        uint32_t mslevel; //!< ms level of map
        double mzminext;  //!< min extraction mass
        double mzmaxext; //!< max extraction mass
        double mzmin; //!< mz min of map
        double mzmax;
        double rtmin; //!< rt min of map
        double rtmax;
      };

      /// dto to tansfer instrument information.
      struct MapInfoAxis{
        uint32_t mapinfoid;//!< foreign key to mapinfo
        std::vector<double> mzaxis; //!< the mz axis
        std::vector<double> rtaxis; //!< the rt axis

        /// used to get pointer to the data and size of mzaxis in bytes
        char * getmzaxis(std::size_t & size) override {
          //char * res = boost::lexical_cast<char *>(feature_.getProjectionMZ());
          char * res = reinterpret_cast<char *>( &(mzaxis)[0] );
          size = mzaxis.size() * (sizeof(double)/sizeof(char));
          return res;
        }

        /// used to get pointer to the data and size of rtaxis in bytes
        char * getrtaxis(std::size_t & size) override {
          //char * res = boost::lexical_cast<char *>(feature_.getProjectionMZ());
          char * res = reinterpret_cast<char *>( &(rtaxis)[0] );
          size = rtaxis.size() * (sizeof(double)/sizeof(char));
          return res;
        }

      };
    }//end namespace dto
  }//end namespace findmf
}//end namespace ralab

#endif // MAPINFO_H
