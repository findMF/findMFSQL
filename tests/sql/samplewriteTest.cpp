// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT


#include "findmf/sql/createtables.h"

#include "findmf/sql/writesampleparams.h"


#include <vector>
#include <algorithm>
//#include <QtSql>

#include "findmf/sql/parsesql.h"


void testCreateDB()
{
  std::string testfile("../sql/dbschema.sql");
  std::string bla = "heresql3.sqlite";
  {
   ralab::findmf::fileio::CreateTables(bla,testfile);
  }
  std::vector<std::string> lines = ralab::findmf::utils::sqlparse(testfile);
}


void testSampleInsterts()
{
  std::string testfile("../sql/dbschema.sql");
  std::string bla = "heresqlSI.sqlite";
  {
    ralab::findmf::fileio::CreateTables(bla,testfile);
  }

  ralab::findmf::dto::Instrument inst;
  inst.analyser = "bla";
  inst.detector = "detect";
  inst.ionisation = "ionize";
  inst.manufacturer = "flying horse";
  inst.model = "newest bit of s...";
  ralab::findmf::dto::SampleDescript samp;
  samp.description = "very complex and important sample";
  samp.file = "/some/filelocation";
  samp.name = "test";

  ralab::findmf::dto::Params params;
  params.maxmass = 1000;
  params.minintensity = 100;
  params.minmass = 10;


  try{
    ralab::findmf::fileio::WriteSampleParams wsp("heresqlSI.sqlite");

    for(int i = 0 ; i < 1000 ; ++i){
      params.minmass +=1;
      uint32_t tmp = wsp.write(samp,inst,params);
      //std::cout << tmp << std::endl;
    }
    wsp.commit();
  }catch(std::exception & e)
  {
    std::cout << e.what() << std::endl;
  }
}


int main(int argc, char **argv) {
  testCreateDB();
  testSampleInsterts();
}





