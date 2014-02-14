#ifndef ISOTOPEFEATURE_H
#define ISOTOPEFEATURE_H

#include <string>
#include <vector>

namespace ralab{
  namespace findmf{
    namespace dto{
      //dto to tansfer instrument information.
      struct Isofeatureboundingbox{
        double minmzext; //!< MS2 selection window in mz
        double maxmzext;
        double minrt; //!< rt start
        double maxrt; //!<
        double minmz;
        double maxmz;

      };

      /// dto to tansfer instrument information.
      struct MapInfoAxis{


      };
    }//end namespace dto
  }//end namespace findmf
}//end namespace ralab

#endif // MAPINFO_H
