// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#ifndef WRITESAMPLEPARAMS_H
#define WRITESAMPLEPARAMS_H

#include <boost/filesystem.hpp>
#include <QtSql>
#include "findmf/dto/Instrument.h"

namespace ralab
{
  namespace findmf
  {
    namespace fileio
    {


      /// writing sample information
      struct WriteSampleParams{
        QSqlDatabase sql_; //!< sql database
        std::string fileloc_; //!< sql file location
        //QSqlQuery iQuery_; //!< database

      private:
        /// open the database
        void openDB(){
          sql_ = QSqlDatabase::addDatabase("QSQLITE");
          QString dbloc(fileloc_.c_str());
          sql_.setDatabaseName(dbloc);
          if (!sql_.open())
          {
            throw std::runtime_error("can't open db");
          }
        }
      public:
        WriteSampleParams(const std::string & fileloc):fileloc_(fileloc){
          openDB();
        }

        ~WriteSampleParams(){
          sql_.close();
        }



      private:

        /// @return sample id
        int insertSample(ralab::findmf::dto::SampleDescript & sample)
        {
          sql_.transaction();
          //using namespace soci;
          std::string p1 =  "insert into sample(name, file, description )";
          p1 +=  " values(:name,:file, :description)";
          QSqlQuery iQuery_(sql_);
          QString queryString(p1.c_str());
          iQuery_.prepare(queryString);
          iQuery_.bindValue(":name",sample.name.c_str());
          iQuery_.bindValue(":file",sample.file.c_str());
          iQuery_.bindValue(":description",sample.description.c_str());

          if(iQuery_.exec()){
            int cdID = iQuery_.lastInsertId().toInt();
            sql_.commit();
            return cdID;
          }else{
            QSqlError err = iQuery_.lastError();
            std::cerr <<  "can't insert into sample: " << err.text().toStdString() <<std::endl;
          }
          sql_.rollback();
          return -1;
        }

        /// store instrument information
        /// @return last inserted id
        int insertInstrumentInfo(int sampleid, ralab::findmf::dto::Instrument & inst){
          sql_.transaction();
          std::string p1 = "insert into instrumentinfo(id,manufacturer,model,ionisation,analyser,detector)";
          p1 += " values(:id, :manufacturer, :model, :ionisation, :analyser, :detector)";
          QSqlQuery iQuery_(sql_);
          iQuery_.prepare(p1.c_str());
          iQuery_.bindValue(":id",sampleid);
          iQuery_.bindValue(":manufacturer",inst.manufacturer.c_str());
          iQuery_.bindValue(":model",inst.model.c_str());
          iQuery_.bindValue(":analyser",inst.analyser.c_str());
          iQuery_.bindValue(":detector",inst.detector.c_str());
          if(iQuery_.exec()){
            int id = iQuery_.lastInsertId().toInt();
            sql_.commit();
            return id;
          }else{
            QSqlError err = iQuery_.lastError();
            std::cerr <<  "can't insert into instrumentinfo: " << err.text().toStdString() <<std::endl;
          }
          sql_.rollback();
          return -1;

        }

        /// store processing parameters
        /// @return last insterted id
        int insertProcessParameters(int sampleid, ralab::findmf::dto::Params & params){
          std::string p1 = "insert into softwareparam(id, resolution,nrthreads,mzpixelwidth,";
          p1 += "rtpixelwidth,scalemz,scalert,minintensity,minmass,maxmass,rt2sum)";
          p1 += " values(:id, :resolution,:nrthreads,:mzpixelwidth,:rtpixelwidth,:scalemz,:scalert,";
          p1 +=  ":minintensity,:minmass,:maxmass,:rt2sum)";
          QSqlQuery iQuery_(sql_);
          iQuery_.prepare(p1.c_str());

          iQuery_.bindValue(":id",sampleid);
          iQuery_.bindValue(":resolution",params.resolution);
          iQuery_.bindValue(":nrthreads",params.nrthreads);
          iQuery_.bindValue(":mzpixelwidth",params.mzpixelwidth);
          iQuery_.bindValue(":rtpixelwidth",params.rtpixelwidth);
          iQuery_.bindValue(":scalemz",params.mzscale);
          iQuery_.bindValue(":scalert",params.rtscale);
          iQuery_.bindValue(":minintensity",params.minintensity);
          iQuery_.bindValue(":minmass",params.minmass);
          iQuery_.bindValue(":maxmass",params.maxmass);
          iQuery_.bindValue(":rt2sum",params.rt2sum);

          if(iQuery_.exec()){
            int id = iQuery_.lastInsertId().toInt();
            sql_.commit();
            return id;
          }else{
            QSqlError err = iQuery_.lastError();
            std::cerr <<  "can't insert into softwareparam: " << err.text().toStdString() <<std::endl;
          }
          sql_.rollback();
          return -1;
      }

      public:

        /// write sample description
        /// consists of sample description, instrument and processing parameters description
        /// @return sample id
        uint32_t write(
            ralab::findmf::dto::SampleDescript & sampledescription,
            ralab::findmf::dto::Instrument & instrument,
            ralab::findmf::dto::Params & params
            ){
          uint32_t sampleid = insertSample(sampledescription);
          insertInstrumentInfo(sampleid,instrument);
          insertProcessParameters(sampleid,params);
          return sampleid;
        }

      };
    }//end fileio
  }//end findmf
}//end ralab



#endif // WRITESAMPLEPARAMS_H
