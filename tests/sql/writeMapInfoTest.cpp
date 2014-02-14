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
#include "findmf/sql/writemapinfo.h"


int main(int argc, char **argv) {
  testCreateDB();
  testSampleInsterts();
}






