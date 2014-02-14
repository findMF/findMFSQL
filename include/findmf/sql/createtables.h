#ifndef CREATETABLES_H
#define CREATETABLES_H

#include <boost/filesystem.hpp>

#include "findmf/sql/parsesql.h"
#include "findmf/dto/Instrument.h"

#include <QtSql>
#include <QtDebug>

namespace ralab
{
  namespace findmf
  {
    namespace fileio
    {
      /// creates the database

      struct CreateTables{

        QSqlDatabase sql_;

      private:
        void open(const std::string & fileloc){

          //check if file location is valid
          boost::filesystem3::path path = boost::filesystem3::path(fileloc).parent_path();
          bool fpath = boost::filesystem3::exists( boost::filesystem3::path(fileloc).parent_path()) || path.empty();

          if(fpath){
            sql_ = QSqlDatabase::addDatabase("QSQLITE");
            QString dbloc(fileloc.c_str());
            sql_.setDatabaseName(dbloc);
            if (!sql_.open())
            {
              throw std::runtime_error("can't open db");
            }
          }
        }

      public:
        CreateTables(const std::string & fileloc, const std::string & schemafile):sql_()
        {

          //open/create the database the database
          open(fileloc);
          //check if schema file exists;
          bool eschem = boost::filesystem3::exists( schemafile );

          if(eschem )
          {

            std::vector<std::string> creatstatements = ralab::findmf::utils::sqlparse(schemafile);


            for(int i = 0 ; i < creatstatements.size(); ++i )
            {
              try{
                sql_.exec(QString(creatstatements[i].c_str()));
              }
              catch( std::exception const &e )
              {
                qDebug()  <<  creatstatements[i].c_str();
                qDebug()  <<  e.what() << "\n";
                throw;
              }
            }

          }
        }

        ~CreateTables(){
          sql_.close();
        }

      };
    }//end fileio
  }//end findmf
}//end ralab

#endif
