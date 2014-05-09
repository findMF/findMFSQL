#ifndef WRITEFEATURE_H
#define WRITEFEATURE_H

#include "findmf/interfaces/ifeatureallaccess.h"

namespace ralab
{
  namespace findmf
  {
    namespace fileio
    {
      struct WriteFeature{
        QSqlDatabase sql_; //!< sql database
        std::string fileloc_; //!< sql file location
      private:
        /// open the database
        void openDB(std::string & fileloc, QSqlDatabase db){
          db = QSqlDatabase::addDatabase("QSQLITE");
          QString dbloc(fileloc.c_str());
          db.setDatabaseName(dbloc);
          if (!db.open())
          {
            throw std::runtime_error("can't open db");
          }
        }

        WriteFeature(const std::string & fileloc//!< database file location
                     ):fileloc_(fileloc)
        {
          openDB( fileloc_ , sql_ );
        }

        uint32_t write(){

        }
      private:

        // write feature range access
        // not clear here at all how you manage multiple samples?
        // therefore not implemented
        uint32_t write(ralab::IFeatureRangeAccess & fra){

          QString queryString ("INSERT INTO feature_index  "
                               " ( minMZsw, maxMZsw, minRT, maxRT, minMZ, maxMZ) "
                               " VALUES(  :minMZsw, :maxMZsw, :minRT, :maxRT, :minMZ, :maxMZ)");
          QSqlQuery query(db_);
          query.prepare(queryString);

          float minmzsw = fra.getMinMZsw();
          float maxmzsw = fra.getMaxMZsw();
          float minrt = fra.getMinRT();
          float maxrt = fra.getMaxRT();
          float minmz = fra.getMinMZ();
          float maxmz = fra.getMaxMZ();

          //insertRTreeQuery_.bindValue(":id", runid );
          query.bindValue(":minMZsw", minmzsw );
          query.bindValue(":maxMZsw", maxmzsw );
          query.bindValue(":minRT", minrt );
          query.bindValue(":maxRT", maxrt );
          query.bindValue(":minMZ", minmz );
          query.bindValue(":maxMZ", maxmz );
          if(!query.exec()){
              QSqlError err = query.lastError();
              std::cerr <<  "can't insert into RTREE with id : " << err.text().toStdString() << std::endl;
            }else{

          }
        }
        //
        uint32_t write(ralab::IFeatureAllAccess & faall
                       ){
          std::string query1 = "INSERT INTO features "
              "(id, idmap, idswath,  max, count,volume,"
              "MZ,RT,centerOfMassMZ,centerOfMassRT,maximumLocationMZ,maximumLocationRT, "
              "MZSD, RTSD, MZSKEW, RTSKEW, MZKURT, RTKURT,"
              "minMZIndex,mzExtend,minRTIndex,rtExtend)";

          std::string query2 =
              " VALUES (:id, :idmap, :idswath,  :max, :count,:volume,"
              ":mz,:rt,:commz,:commrt,:maxlocmz,:maxlocrt,"
              " :mzsd, :rtsd, :mzskew, :rtskew, :mzkurt, :rtkurt,"
              " :mzminidx, :extmz, :rtminidx, :extrt)";


        }



        // write projection
        uint32_t write(ralab::IFeatureProjection & fp){

        }


      };
    }
  }
}

#endif // WRITEFEATURE_H
