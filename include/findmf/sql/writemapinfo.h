#ifndef WRITEMAPINFO_H
#define WRITEMAPINFO_H

#include <QtSql>
#include "findmf/dto/MapInfo.h"
///

namespace ralab
{
  namespace findmf
  {
    namespace fileio
    {
      // writes map information
      struct WriteMapInfo{
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
        WriteMapInfo(const std::string & fileloc):fileloc_(fileloc){
          openDB();
        }
        ~WriteMapInfo(){
          sql_.close();
        }

        /// write map information
        /// @return mapinfoid
        uint32_t write(findmf::dto::MapInfo & mapinfo, findmf::dto::MapInfoAxis & mapaxis){
          uint32_t mapinfoid = write(mapinfo);
          mapaxis.mapinfoid = mapinfoid;
          write(mapaxis);
          return mapinfoid;
        }
      private:
        /// @return last inserted id
        uint32_t write(findmf::dto::MapInfo & mapinfo){
          sql_.transaction();
          //using namespace soci;
          QString queryString ("INSERT INTO mapinfo "
                               "( sampleid, scancount, mslevel, mzminext, mzmaxext, mzmin, mzmax, rtmin, rtmax) "
                               " VALUES (:sampleid, :scancount, :mslevel, :mzminext,:mzmaxext,:mzmin,:mzmax,:rtmin,:rtmax);");

          QSqlQuery insertMapQuery_(sql_);
          insertMapQuery_.prepare(queryString);

          insertMapQuery_.bindValue(":sampleid",mapinfo.scancount);
          insertMapQuery_.bindValue(":scancount",mapinfo.scancount);
          insertMapQuery_.bindValue(":mslevel",mapinfo.mslevel);
          insertMapQuery_.bindValue(":mzminext",mapinfo.mzminext);
          insertMapQuery_.bindValue(":mzmaxext",mapinfo.mzmaxext);
          insertMapQuery_.bindValue(":mzmin",mapinfo.mzmin);
          insertMapQuery_.bindValue(":mzmax",mapinfo.mzmax);
          insertMapQuery_.bindValue(":rtmin",mapinfo.rtmin);
          insertMapQuery_.bindValue(":rtmax",mapinfo.rtmax);

          if(insertMapQuery_.exec()){
            int cdID = insertMapQuery_.lastInsertId().toInt();
            sql_.commit();
            return cdID;
          }else{
            QSqlError err = insertMapQuery_.lastError();
            std::cerr <<  "can't insert into mapinfo: " << err.text().toStdString() <<std::endl;
          }
          sql_.rollback();
          return -1;
        }

        /// @return last insterted id
        uint32_t write(findmf::dto::MapInfoAxis & mapinfoaxis){
          sql_.transaction();
          //using namespace soci;
          QString queryString ("INSERT INTO mapinfoaxis "
                               "( idmapinfo, mzaxis, rtaxis) "
                               " VALUES (:idmapinfo, :mzaxis, :rtaxis);");

          QSqlQuery insertMapQuery_(sql_);
          insertMapQuery_.prepare(queryString);

          insertMapQuery_.bindValue(":idmapinfo",mapinfoaxis.mapinfoid);

          // QT compatibility code (sorry).
          char * charp;
          std::size_t size;
          charp =  mapinfoaxis.getmzaxis(size);
          QByteArray baa(charp, size);
          insertMapQuery_.bindValue(":mzaxis",baa);

          charp = mapinfoaxis.getrtaxis(size);
          QByteArray bab(charp, size);
          insertMapQuery_.bindValue(":rtaxis",bab);

          if(insertMapQuery_.exec()){
            int cdID = insertMapQuery_.lastInsertId().toInt();
            sql_.commit();
            return cdID;
          }else{
            QSqlError err = insertMapQuery_.lastError();
            std::cerr <<  "can't insert into mapinfoaxis: " << err.text().toStdString() <<std::endl;
          }
          sql_.rollback();
          return -1;
        }

      };
    }
  }
}//end
#endif // WRITEMAPINFO_H
