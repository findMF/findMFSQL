// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#include "findmf/sql/parsesql.h"
#include "findmf/sql/createtables.h"
#include "findmf/sql/writesampleparams.h"
#include "findmf/sql/writemapinfo.h"

#include <vector>
#include <algorithm>
//#include <QtSql>


void testCreateDB()
{
  std::string testfile("../sql/dbschema.sql");
  std::string bla = "heresql3.sqlite";
  {
    ralab::findmf::fileio::CreateTables(bla,testfile);
  }
  std::vector<std::string> lines = ralab::findmf::utils::sqlparse(testfile);
}

/// test insterting samples
int testSampleInsterts()
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

  uint32_t tmp;
  try{
    ralab::findmf::fileio::WriteSampleParams wsp("heresqlSI.sqlite");

    for(int i = 0 ; i < 10 ; ++i){
      params.minmass +=1;
      tmp = wsp.write(samp,inst,params);
      std::cout << "bla : " << tmp << std::endl;
    }

  }catch(std::exception & e)
  {
    std::cout << e.what() << std::endl;
  }
  return tmp;
}


/// test insterting mapinfo
void testMapInfoInsterts(int sampleid)
{
  std::string testfile("../sql/dbschema.sql");
  std::string bla = "heresqlSI.sqlite";
  {
    ralab::findmf::fileio::CreateTables(bla,testfile);
  }

  ralab::findmf::dto::MapInfo mapinfo;

  mapinfo.sampleid = sampleid;
  mapinfo.scancount = 2000;
  mapinfo.mslevel = 2;
  mapinfo.mzmaxext = 100;
  mapinfo.mzminext = 99;
  mapinfo.mzmax = 1000.;
  mapinfo.mzmin = 100.;
  mapinfo.rtmax = 3000.;
  mapinfo.rtmin = 1000.;

  ralab::findmf::dto::MapInfoAxis mapinfoaxis;
  double mz[] = {100.,101.,102.1,103.1,104.1,105.2,106.2};
  mapinfoaxis.mzaxis.assign(mz,mz+sizeof(mz)/sizeof(double));
  mapinfoaxis.rtaxis.assign(mz,mz+sizeof(mz)/sizeof(double));

  try{
    //
    ralab::findmf::fileio::WriteMapInfo wmpi("heresqlSI.sqlite");
    for(int i = 0 ; i < 10 ; ++i){
      uint32_t tmp = wmpi.write(mapinfo,mapinfoaxis);
      std::cout << "blax : " << tmp << std::endl;
    }

  }catch(std::exception & e)
  {
    std::cout << e.what() << std::endl;
  }
}


int main(int argc, char **argv) {
  testCreateDB();
  int lastid = testSampleInsterts();
  testMapInfoInsterts(lastid);
}





