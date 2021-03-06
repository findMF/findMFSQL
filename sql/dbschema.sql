-- all information is stored in pixel coordinates.
-- use information in mzaxis and rtaxis to map to rt and mz and back.

-- database version
PRAGMA user_version = 0.1;
-- database end
PRAGMA foreign_keys = ON;

-- code to kill all the tables --
PRAGMA writable_schema = 1;
delete from sqlite_master where type = 'table';
PRAGMA writable_schema = 0;
VACUUM;
PRAGMA INTEGRITY_CHECK;

-- basic sample information
drop table if exists sample;
CREATE TABLE sample (
id integer primary key,
name text,
file text,
description text
);

-- table containing processing parameters
drop table if exists softwareparam;
CREATE TABLE softwareparam (
id integer primary key,
resolution real,
nrthreads int,
mzpixelwidth int,
rtpixelwidth int,
scalemz real,
scalert real,
minintensity real,
minmass real,
maxmass real,
rt2sum int,
FOREIGN KEY(id) REFERENCES sample(id)
);

-- instrument info table
drop table if exists instrumentinfo;
CREATE TABLE instrumentinfo(
id integer primary key,
manufacturer text,
model text,
ionisation text,
analyser text,
detector text,
FOREIGN KEY(id) REFERENCES sample(id)
);

-- one sample can have many maps 1:N
drop table if exists mapinfo;
CREATE TABLE mapinfo(
id integer primary key,  -- id of map
sampleid int not null, -- sample id // many maps per sample
scancount int not null, --  -- number of spectra in map
mslevel int not null,  --  -- ms level of map
mzminext real,  -- min extraction mass
mzmaxext real, -- max extraction mass
mzmin real not null, -- mz min of map
mzmax real not null, --
rtmin real not null, -- rt min of map
rtmax real not null, --
FOREIGN KEY(sampleid) REFERENCES sample(id)
);

-- mappings mass and rt
drop table if exists mapinfoaxis;
CREATE TABLE mapinfoaxis (
id integer primary key,
idmapinfo int not null,  --  links to map info
mzaxis blob, -- mass axis
rtaxis blob,
FOREIGN KEY(id) REFERENCES mapinfo(id)
);

-- these tables are bound to each other
-- all rt and mz position information is stored in pixel coordinates
-- mapping can be achieved using the file above

-- drop table if exists isofeatureboundingbox;
-- CREATE VIRTUAL TABLE isotopefeaturesbox USING rtree(
-- id,
-- minMZsw,
-- maxMZsw,
-- minRT, maxRT,
-- minMZ, maxMZ
-- );

-- not used
-- drop table if exists isofeatureboundingbox;
-- CREATE TABLE isofeatureboundingbox USING rtree(
-- id integer primary key,
-- minmzext real,  --  id in the current map
-- maxmzext real,
-- minrt int, -- min RT pixel location
-- maxrt int, --
-- minmz int, -- start RT pixel location
-- maxmz int
-- );

-- drop table if exists isofeatureboundingbox;
-- CREATE VIRTUAL TABLE isofeatureboundingbox USING rtree(
-- id,
-- minmzext,  --  id in the current map
-- maxmzext,
-- minrt, -- id
-- maxrt,
-- minmz,
-- maxmz
-- );

-- feature statistics table
drop table if exists isotopefeatures;
CREATE TABLE isotopefeatures (
id integer primary key,  -- id in table
idmap int not null,  --  id in the current map # todo check if needed
idmapinfo int not null, --  id of the map - links to map info
mzcom real,  -- com - center of mass (pixel)
rtcom real,
mz real,  --  picked mass
rt real ,
mzmaxloc int,  --  location of peak maximum (pixel)
rtmaxloc int,
mzsd real, --  sd of peak
rtsd real,
mzskew real, --  skewness
rtskew real,
mzkurt real, -- mz
rtkurt real,
maxint real, --  maximum value
count integer, -- number of pixels
volume real,  -- volume of feature
FOREIGN KEY(id) REFERENCES isotopefeaturesbox(id),
FOREIGN KEY(idmapinfo) REFERENCES mapinfo(id)
);

-- projection data blobs
drop table if exists isotopefeaturesprojection;
CREATE TABLE isotopefeaturesprojection (
id integer primary key,  -- id in table
-- bounding box information
mzstart int,  --  mz start pixel
mzextend int,  --  pixel extend
rtstart int,
rtextend int,
mzproj blob,  --  mz projection
rtproj blob,
FOREIGN KEY(id) REFERENCES isotopefeaturesbox(id)
);

-- stores deisotoping information
drop table if exists features;
CREATE TABLE features (
id integer primary key,
idmapinfo int not null, -- id of mapp
monomass real, --
monort real, --
volume real, --
maxint real, --
mzstart int,
mzextend int,
rtstart int,
rtextend int,
FOREIGN KEY(idmapinfo) REFERENCES mapinfo(id)
);

-- to permit for confilicting assignments of feature 2 and isofeature
drop table if exists featurs2isofeatures;
CREATE TABLE featurs2isofeatures(
id integer primary key,
featureid int not null,
isofeatureid int not null,
FOREIGN KEY(featureid) REFERENCES features(id),
FOREIGN KEY(isofeatureid) REFERENCES isotopefeatures(id)
);


